#include "reader.h"
#include "pch.h"

#include "curl/curl.h"

namespace gazeta::info_controller::info_sources
{
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              void *userp)
  {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
  }

  std::string reader::read_source(source &src)
  {
    AUTOLOG;
    std::string result;

    try
    {
      CURL *curl;
      CURLcode res;

      curl = curl_easy_init();
      if (curl)
      {
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
    }
    catch (std::exception &exception)
    {
      hare::error("Error occurred: {}", exception.what());
    }
    catch (...)
    {
      hare::error("Error occurred");
    }

    return result;
  }

#ifdef BOOST_FOUND

#include <boost/asio.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

  int boost_test()
  {
    AUTOLOG;

    const std::string host = "t.me";
    const std::string target = "/s/rian_ru/";
    const std::string port = "443";

    // I/O контекст, необходимый для всех I/O операций
    // boost::asio::io_context ioc;
    // Resolver для определения endpoint'ов
    // boost::asio::ip::tcp::resolver resolver(ioc);
    // Tcp сокет, использующейся для соединения
    // boost::asio::ip::tcp::socket socket(ioc);
    // Резолвим адрес и устанавливаем соединение
    // boost::asio::connect(socket, resolver.resolve(host, "80"));

    boost::asio::io_service svc;
    boost::asio::ssl::context ctx(
        boost::asio::ssl::context::method::sslv23_client);
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

      boost::beast::http::response_parser<boost::beast::http::dynamic_body>
          response_parser;

      // std::cout << res << std::endl;
      // hare::info(res.body().cdata());

      // auto data = res.body().data();
      // res.find("main");

      try
      {
        std::stringstream stream(buffers_to_string(res.body().data()).data());
        boost::property_tree::ptree propertyTree;
        boost::property_tree::read_xml(stream, propertyTree);
      }
      catch (std::exception ex)
      {
        hare::error(ex.what());
      }
    }
    // socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    // socket.shutdown();

    return 0;
  }

#endif

} // namespace gazeta::info_controller::info_sources
