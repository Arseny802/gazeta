#include "pch.h"
#include "telegram_web.h"

#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/HTMLtree.h>
#include <libxml2/libxml/xpath.h>

namespace gazeta::info_sources {

std::vector<article> telegram_http::parse_doc(const std::string &httpdoc) {
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
      std::string message_text = std::string
      (reinterpret_cast<char *>(xmlNodeGetContent(element_message_text)));
      new_article.text = message_text;
    } else {
      hare::warn("element_message_text not exists!");
      std::string product_html = std::string(
        reinterpret_cast<char *>(xmlNodeGetContent(product_html_element)));
      //hare::warn(product_html);
    }

    xmlNodePtr element_message_time = xmlXPathEvalExpression(
        (xmlChar *) ".//time[contains(@class, 'time')]",
        context)->nodesetval->nodeTab[0];
    if (element_message_time) {
      std::string message_time = std::string(
        reinterpret_cast<char *>(xmlNodeGetContent(element_message_time)));
      std::string message_time2 = std::string(
        reinterpret_cast<char *>(xmlGetProp(element_message_time, (xmlChar *) "datetime")));

      new_article.time = message_time;
      new_article.datetime = message_time2;
    } else {
      hare::warn("element_message_time not exists!");
      std::string product_html = std::string(
        reinterpret_cast<char *>(xmlNodeGetContent(product_html_element)));
      //hare::warn(product_html);
    }

    xmlNodePtr element_message_link = xmlXPathEvalExpression(
        (xmlChar *) ".//a[contains(@class, 'tgme_widget_message_date')]",
        context)->nodesetval->nodeTab[0];
    if (element_message_link) {
      std::string link = std::string(
        reinterpret_cast<char *>(xmlGetProp(element_message_link, (xmlChar *) "href")));

      new_article.link = link;

      new_article.id = std::stoi(link.substr(link.rfind('/') + 1));
    } else {
      hare::warn("element_message_link not exists!");
      std::string product_html = std::string(
        reinterpret_cast<char *>(xmlNodeGetContent(product_html_element)));
      //hare::warn(product_html);
    }

    //hare::info(new_article.format());
    result.emplace_back(new_article);
  }

  xmlXPathFreeContext(context);
  xmlFreeDoc(doc);
  return result;
}
}  // namespace gazeta::info_sources
