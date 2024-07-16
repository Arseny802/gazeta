#include "telegram_web.h"
#include "pch.h"

#include <fmt/format.h>
#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/HTMLtree.h>
#include <libxml2/libxml/xpath.h>

namespace gazeta::info_sources {

bool parse_element_message_time(article &new_article,
                                xmlXPathContextPtr context) {
  xmlNodePtr element_message_time =
      xmlXPathEvalExpression((xmlChar *)".//time[contains(@class, 'time')]",
                             context)
          ->nodesetval->nodeTab[0];
  if (!element_message_time) {
    hare::warn("element_message_time not exists!");
    return false;
  }

  std::string message_time = std::string(
      reinterpret_cast<char *>(xmlNodeGetContent(element_message_time)));
  std::string message_time2 = std::string(reinterpret_cast<char *>(
      xmlGetProp(element_message_time, (xmlChar *)"datetime")));

  new_article.time = message_time;
  new_article.datetime = message_time2;
  return true;
}

bool parse_element_message_link(article &new_article,
                                xmlXPathContextPtr context) {
  xmlNodePtr element_message_link =
      xmlXPathEvalExpression(
          (xmlChar *)".//a[contains(@class, 'tgme_widget_message_date')]",
          context)
          ->nodesetval->nodeTab[0];
  if (!element_message_link) {
    hare::warn("element_message_link not exists!");
    return false;
  }

  std::string link = std::string(reinterpret_cast<char *>(
      xmlGetProp(element_message_link, (xmlChar *)"href")));

  new_article.link = link;

  new_article.id = std::stoi(link.substr(link.rfind('/') + 1));
  return true;
}

bool parse_element_message_text(article &new_article,
                                xmlXPathContextPtr context) {
  xmlXPathObjectPtr element_message_text_set = xmlXPathEvalExpression(
      (xmlChar *)".//div[contains(@class, 'tgme_widget_message_text')]",
      context);
  if (!element_message_text_set->nodesetval->nodeNr) {
    element_message_text_set = xmlXPathEvalExpression(
        (xmlChar *)".//div[contains(@class, 'tgme_widget_message_metatext')]",
        context);
    if (!element_message_text_set->nodesetval->nodeNr) {
      hare::warn("element_message_text not exists!");
      return false;
    }
  }

  int last_index = element_message_text_set->nodesetval->nodeNr - 1;
  new_article.text = std::string(reinterpret_cast<char *>(xmlNodeGetContent(
      element_message_text_set->nodesetval->nodeTab[last_index])));
  return true;
}

bool parse_element_message_image(article &new_article,
                                 xmlXPathContextPtr context) {
  xmlXPathObjectPtr element_message_photo_set = xmlXPathEvalExpression(
      (xmlChar *)".//a[contains(@class, 'tgme_widget_message_photo_wrap')]",
      context);
  if (!element_message_photo_set->nodesetval->nodeNr) {
    return false;
  }

  for (int photo_wrap_id = 0;
       photo_wrap_id < element_message_photo_set->nodesetval->nodeNr;
       ++photo_wrap_id) {
    article::image_t image;
    xmlNodePtr element_message_photo =
        element_message_photo_set->nodesetval->nodeTab[photo_wrap_id];

    image.url = std::string(reinterpret_cast<char *>(
        xmlGetProp(element_message_photo, (xmlChar *)"href")));
    image.style = std::string(reinterpret_cast<char *>(
        xmlGetProp(element_message_photo, (xmlChar *)"style")));
    new_article.images.push_back(image);
  }
  return true;
}

bool parse_element_message_video(article &new_article,
                                 xmlXPathContextPtr context) {
  xmlNodePtr element_message_video =
      xmlXPathEvalExpression(
          (xmlChar
               *)".//a[contains(@class, 'tgme_widget_message_video_player')]",
          context)
          ->nodesetval->nodeTab[0];
  if (!element_message_video) {
    return false;
  }

  article::image_t image;

  image.url = std::string(reinterpret_cast<char *>(
      xmlGetProp(element_message_video, (xmlChar *)"style")));
  new_article.images.push_back(image);
  return true;
}

bool parse_element_message_reply(article &new_article,
                                 xmlXPathContextPtr context,
                                 xmlNodePtr base_element = nullptr) {
  xmlXPathObjectPtr widget_message_reply_set = xmlXPathEvalExpression(
      (xmlChar *)".//a[contains(@class, 'tgme_widget_message_reply')]",
      context);
  for (int widget_reply_id = 0;
       widget_reply_id < widget_message_reply_set->nodesetval->nodeNr;
       ++widget_reply_id) {
    article reply_article;
    xmlNodePtr reply_element =
        widget_message_reply_set->nodesetval->nodeTab[widget_reply_id];

    reply_article.link = std::string(
        reinterpret_cast<char *>(xmlGetProp(reply_element, (xmlChar *)"href")));
    reply_article.id =
        std::stoi(reply_article.link.substr(reply_article.link.rfind('/') + 1));

    xmlXPathSetContextNode(reply_element, context);
    parse_element_message_text(reply_article, context);
    if (base_element) {
      xmlXPathSetContextNode(base_element, context);
    }

    new_article.reply_to.emplace_back(reply_article);
  }

  return true;
}

std::vector<article> telegram_http::parse_doc(const std::string &httpdoc) {
  AUTOLOG

  std::vector<article> result;
  htmlDocPtr doc;

  // doc = htmlReadFile("ololo.dat", "UTF-8", 0);
  doc = htmlReadMemory(httpdoc.c_str(), httpdoc.size(), nullptr, "UTF-8", 0);

  xmlXPathContextPtr context = xmlXPathNewContext(doc);
  xmlXPathObjectPtr tgme_widget_message_html_elements = xmlXPathEvalExpression(
      (xmlChar *)"//div[contains(@class, 'tgme_widget_message_bubble')]",
      context);

  for (int bubble_id = 0;
       bubble_id < tgme_widget_message_html_elements->nodesetval->nodeNr;
       ++bubble_id) {
    article new_article;
    xmlNodePtr tgme_widget_message_html_element =
        tgme_widget_message_html_elements->nodesetval->nodeTab[bubble_id];
    xmlXPathSetContextNode(tgme_widget_message_html_element, context);

    if (xmlXPathEvalExpression(
            (xmlChar
                 *)".//div[contains(@class, 'message_media_not_supported')]",
            context)
            ->nodesetval->nodeTab[0]) {
      new_article.is_supported = false;
    } else {
      parse_element_message_image(new_article, context);
      parse_element_message_video(new_article, context);
      parse_element_message_text(new_article, context);
    }

    parse_element_message_time(new_article, context);
    parse_element_message_link(new_article, context);
    parse_element_message_reply(new_article, context);
    result.emplace_back(new_article);
  }

  xmlXPathFreeContext(context);
  xmlFreeDoc(doc);
  return result;
}
} // namespace gazeta::info_sources
