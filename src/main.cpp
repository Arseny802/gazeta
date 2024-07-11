#include "pch.h"
#include "curl/curl.h"
#include "pugixml.hpp"
#include "fmt/format.h"

#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/HTMLtree.h>
#include <libxml2/libxml/xpath.h>

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *) userp)->append((char *) contents, size * nmemb);
  return size * nmemb;
}

struct source {
  std::string url;
};

struct article {
  size_t id = 0;
  std::string text;
  std::string time;
  std::string datetime;
  std::string link;
  void *image = nullptr;

  std::string format() {
    std::string base = "Article";
    if (id > 0) {
      base += " " + std::to_string(id);
    }
    if (!link.empty()) {
      base += " [" + link + "]";
    }

    std::string dt = datetime;
    if (!time.empty()) {
      dt = fmt::format("{0} (friendly '{1}')", datetime, time);
    }

    return fmt::format("{0}, DT {1}, message: '{2}'", base, dt, text);
  }
};

std::string read_source(source &src) {
  AUTOLOG
  std::string result;

  try {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, src.url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
      struct curl_slist *headers = NULL;
      headers = curl_slist_append(headers, "Content-Type: application/json");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

      res = curl_easy_perform(curl);

      curl_slist_free_all(headers);
      curl_easy_cleanup(curl);
    }

  } catch (std::exception &exception) {
    hare::error("Error occurred: {}", exception.what());
  } catch (...) {
    hare::error("Error occurred");
  }

  return result;
}

void parse_httpdoc(const std::string &httpdoc) {
  AUTOLOG

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_string(httpdoc.c_str(), pugi::parse_full);
  if (!result) {
    hare::error("Could not load html document! Status: {0}, desc: {1}",
                static_cast<int>(result.status), result.description());

    return;
  }

  // class="tgme_widget_message_text js-message_text"
  for (pugi::xml_node tool : doc.child("html").child("body").child("main").children("div")) {
    std::string div_class = tool.attribute("class").as_string();

    hare::info(div_class);
  }
}

std::vector<article> parse_httpdoc2(const std::string &httpdoc) {
  AUTOLOG

  std::vector<article> result;
  htmlDocPtr doc;

  //doc = htmlReadFile("ololo.dat", "UTF-8", 0);
  doc = htmlReadMemory(httpdoc.c_str(), httpdoc.size(), nullptr, "UTF-8", 0);

  xmlXPathContextPtr context = xmlXPathNewContext(doc);
  xmlXPathObjectPtr product_html_elements = xmlXPathEvalExpression(
      (xmlChar *) "//div[contains(@class, 'tgme_widget_message_bubble')]", context);

  for (int i = 0; i < product_html_elements->nodesetval->nodeNr; ++i) {
    article new_article;
    xmlNodePtr product_html_element = product_html_elements->nodesetval->nodeTab[i];
    xmlXPathSetContextNode(product_html_element, context);

    xmlNodePtr element_message_text = xmlXPathEvalExpression(
        (xmlChar *) ".//div[contains(@class, 'tgme_widget_message_text')]",
        context)->nodesetval->nodeTab[0];
    if (element_message_text) {
      std::string message_text = std::string(reinterpret_cast<char *>(
                                                 xmlNodeGetContent(element_message_text)));
      new_article.text = message_text;
    } else {
      hare::warn("element_message_text not exists!");
      std::string product_html = std::string(reinterpret_cast<char *>(
                                                 xmlNodeGetContent(product_html_element)));
      //hare::warn(product_html);
    }

    xmlNodePtr element_message_time = xmlXPathEvalExpression(
        (xmlChar *) ".//time[contains(@class, 'time')]",
        context)->nodesetval->nodeTab[0];
    if (element_message_time) {
      std::string message_time = std::string(reinterpret_cast<char *>(
                                                 xmlNodeGetContent(element_message_time)));
      std::string message_time2 = std::string(reinterpret_cast<char *>(
                                                  xmlGetProp(element_message_time, (xmlChar *) "datetime")));

      new_article.time = message_time;
      new_article.datetime = message_time2;
    } else {
      hare::warn("element_message_time not exists!");
      std::string product_html = std::string(reinterpret_cast<char *>(
                                                 xmlNodeGetContent(product_html_element)));
      //hare::warn(product_html);
    }

    xmlNodePtr element_message_link = xmlXPathEvalExpression(
        (xmlChar *) ".//a[contains(@class, 'tgme_widget_message_date')]",
        context)->nodesetval->nodeTab[0];
    if (element_message_link) {
      std::string link = std::string(reinterpret_cast<char *>(
                                         xmlGetProp(element_message_link, (xmlChar *) "href")));

      new_article.link = link;

      new_article.id = std::stoi(link.substr(link.rfind('/') + 1));
    } else {
      hare::warn("element_message_link not exists!");
      std::string product_html = std::string(reinterpret_cast<char *>(
                                                 xmlNodeGetContent(product_html_element)));
      //hare::warn(product_html);
    }

    //hare::info(new_article.format());
    result.emplace_back(new_article);
  }

  xmlXPathFreeContext(context);
  xmlFreeDoc(doc);
  return result;
}

std::vector<article> read_n_articles(int to_read) {
  AUTOLOG

  std::vector<article> result;
  std::string base_url = "https://t.me/s/rian_ru/";
  std::string url = base_url;
  do {
    source src;
    src.url = url;

    hare::info("Gettings articles by URL '{0}'.", src.url);
    std::vector<article> articles = parse_httpdoc2(read_source(src));
    if (articles.empty()) {
      break;
    }

    url = base_url + "?before=" + std::to_string(articles.begin()->id);
    to_read -= static_cast<int>(articles.size());
    result.insert(result.cend(), articles.begin(), articles.end());
  } while (to_read > 0);

  std::sort(result.begin(), result.end(), [](const article& a1, const article& a2){
    return a1.id < a2.id;
  });

  return result;
}

int boost_test() {
  AUTOLOG

  const std::string host = "t.me";
  const std::string target = "/s/rian_ru/";
  const std::string port = "443";

  // I/O контекст, необходимый для всех I/O операций
  //boost::asio::io_context ioc;
  // Resolver для определения endpoint'ов
  //boost::asio::ip::tcp::resolver resolver(ioc);
  // Tcp сокет, использующейся для соединения
  //boost::asio::ip::tcp::socket socket(ioc);
  // Резолвим адрес и устанавливаем соединение
  //boost::asio::connect(socket, resolver.resolve(host, "80"));


  boost::asio::io_service svc;
  boost::asio::ssl::context ctx(boost::asio::ssl::context::method::sslv23_client);
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(svc, ctx);

  boost::asio::ip::tcp::resolver resolver(svc);
  auto it = resolver.resolve({host, port});
  boost::asio::connect(socket.lowest_layer(), it);
  socket.handshake(boost::asio::ssl::stream_base::handshake_type::client);

  boost::beast::http::request<boost::beast::http::string_body> req(
      boost::beast::http::verb::get, target, 11);

  req.set(boost::beast::http::field::host, host);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(boost::beast::http::field::content_type, "application/json");

  size_t bytes_wrote = boost::beast::http::write(socket, req);

  {
    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::dynamic_body> res;
    boost::beast::http::read(socket, buffer, res);

    boost::beast::http::response_parser<boost::beast::http::dynamic_body> response_parser;

    //std::cout << res << std::endl;
    //hare::info(res.body().cdata());

    //auto data = res.body().data();
    //res.find("main");

    try {
      std::stringstream stream(buffers_to_string(res.body().data()).data());
      boost::property_tree::ptree propertyTree;
      boost::property_tree::read_xml(stream, propertyTree);
    }
    catch (std::exception ex) {
      hare::error(ex.what());
    }
  }
  //socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
  //socket.shutdown();

  return 0;
}

int main() {
  gazeta::initialize_logging();
  AUTOLOG

  std::vector<article> articles = read_n_articles(100);
  for (auto& art : articles) {
    hare::info(art.format());
  }

  return 0;
}
