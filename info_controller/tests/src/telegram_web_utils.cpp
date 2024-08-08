#include "pch_tests.h"
#include "telegram_web_utils.h"
#include "telegram_web.cpp"
#include <sstream>

namespace gazeta::info_controller
{
  namespace
  {
    static size_t article_id = 1;

    void httpdoc_set_head(std::stringstream &httpdoc)
    {
      httpdoc << "<!DOCTYPE html>";
      httpdoc << "<html>";
      httpdoc << "  <head>";
      httpdoc << "    <meta charset=\"utf-8\">";
      httpdoc << "    <title>Test title with unexpected symbols </title>";
      httpdoc << "    <meta name=\"format-detection\" content=\"telephone=no\" />";
      httpdoc << "  </head>";
      httpdoc << "  <body>";
    }

    void httpdoc_set_tail(std::stringstream &httpdoc)
    {
      httpdoc << "  </body>";
      httpdoc << "</html>";
    }

    void httpdoc_set_bubble_head(std::stringstream &httpdoc)
    {
      httpdoc << "<div class=\"tgme_widget_message_bubble\">";

      httpdoc << "<i class=\"tgme_widget_message_bubble_tail\">";
      httpdoc << "<svg class=\"bubble_icon\" width=\"9px\" height=\"20px\" viewBox=\"0 0 9 20\">";
      httpdoc << "<g fill=\"none\">";
      httpdoc << "<path class=\"background\" d=\"M8,1 L9,1 L9,20\" fill=\"#ffffff\"></path>";
      httpdoc << "<path class=\"border_1x\" d=\"M8,1 L9,1 L9,20\" fill=\"#d7e3ec\"></path>";
      httpdoc << "<path class=\"border_2x\" d=\"M8,1 L9,1 L9,20\"></path>";
      httpdoc << "<path class=\"border_3x\" d=\"M8,1 L9,1 L9,20\"></path>";
      httpdoc << "</g>" << "</svg>" << "</i>";

      httpdoc << "<div class=\"tgme_widget_message_author accent_color\">";
      httpdoc << "<a class=\"tgme_widget_message_owner_name\" href=\"https://t.me/" << TestTelegramWeb::channel_name << "\">";
      httpdoc << "<span dir=\"auto\">" << TestTelegramWeb::author_name << "</span></a></div>";
    }

    void httpdoc_set_bubble_tail(std::stringstream &httpdoc)
    {
      httpdoc << "<div class=\"tgme_widget_message_footer compact js-message_footer\">";
      httpdoc << "<div class=\"tgme_widget_message_info short js-message_info\">";
      httpdoc << "<span class=\"tgme_widget_message_views\">379.1K</span><span class=\"copyonly\"> views</span>";
      httpdoc << "<span class=\"tgme_widget_message_meta\"><a class=\"tgme_widget_message_date\" ";
      httpdoc << " href=\"https://t.me/" << TestTelegramWeb::channel_name << "/" << article_id++;
      httpdoc << "\"><time datetime=\"2024-07-10T22:18:36+00:00\" class=\"time\">";
      httpdoc << "22:18</time></a></span>";
      httpdoc << "</div>" << "</div>";

      httpdoc << "</div>";
    }

    void httpdoc_set_bubble(std::stringstream &httpdoc,
                            int photos = 1,
                            bool text_with_link = true)
    {
      httpdoc_set_bubble_head(httpdoc);

      if (photos == 1)
      {
        httpdoc << "<a class=\"tgme_widget_message_photo_wrap 5222027401658227669 1215848001_456252373 \"";
        httpdoc << " href=\"https://t.me/" << TestTelegramWeb::channel_name << "/" << article_id++ << "\" ";
        httpdoc << "style=\"width:800px;background-image:url('https://cdn4.cdn-telegram.org/file/link_example.jpg')\">";
        httpdoc << "<div class=\"tgme_widget_message_photo\" style=\"padding-top:60.5%\"></div>";
        httpdoc << "</a>";
      }

      httpdoc << "<div class=\"tgme_widget_message_text js-message_text\" dir=\"auto\">";
      httpdoc << "Exmample text begin, ";
      if (text_with_link)
      {
        httpdoc << "<a href=\"https://t.me/" << TestTelegramWeb::channel_name << "/" << article_id++;
        httpdoc << "\" target=\"_blank\" rel=\"noopener\" ";
        httpdoc << "onclick=\"return confirm('Open this link?\n\n'+this.href);\">link in message</a>.";
      }
      httpdoc << "<br/><br/>Text continue 1.";
      httpdoc << "<br/><br/>Text continue 2";
      httpdoc << "<br/><br/>Text continue 3";
      httpdoc << "</div>";

      httpdoc_set_bubble_tail(httpdoc);
    }

    void httpdoc_set_bubble_unsupported(std::stringstream &httpdoc)
    {
      httpdoc_set_bubble_head(httpdoc);

      httpdoc << "<div class=\"message_media_not_supported_wrap\">";
      httpdoc << "<div class=\"message_media_not_supported\">";
      httpdoc << "<div class=\"message_media_not_supported_label\">Please open Telegram to view this post</div>";
      httpdoc << "<a href=\"https://t.me/)" << TestTelegramWeb::channel_name << "/" << article_id++ << "\" ";
      httpdoc << "class=\"message_media_view_in_telegram\">VIEW IN TELEGRAM</a>";
      httpdoc << "</div>" << "</div>";

      httpdoc_set_bubble_tail(httpdoc);
    }

    std::string get_httpdoc_empty()
    {
      static std::string _cash;
      if (_cash.empty())
      {
        std::stringstream httpdoc;
        httpdoc_set_head(httpdoc);
        httpdoc_set_tail(httpdoc);
        _cash = httpdoc.str();
      }
      return _cash;
    }

    std::string get_httpdoc_var1()
    {
      static std::string _cash;
      if (_cash.empty())
      {
        std::stringstream httpdoc;
        httpdoc_set_head(httpdoc);
        httpdoc_set_bubble(httpdoc);
        httpdoc_set_bubble_unsupported(httpdoc);
        httpdoc_set_bubble(httpdoc, 0);
        httpdoc_set_bubble(httpdoc, 0, false);
        httpdoc_set_tail(httpdoc);
        _cash = httpdoc.str();
      }
      return _cash;
    }

    std::string get_httpdoc_var2()
    {
      static std::string _cash;
      if (_cash.empty())
      {
        std::stringstream httpdoc;
        httpdoc_set_head(httpdoc);
        httpdoc_set_bubble(httpdoc);

        httpdoc_set_tail(httpdoc);
        _cash = httpdoc.str();
      }
      return _cash;
    }

    std::string get_httpdoc_var3()
    {
      static std::string _cash;
      if (_cash.empty())
      {
        std::stringstream httpdoc;
        httpdoc_set_head(httpdoc);
        httpdoc_set_bubble(httpdoc, 0);

        httpdoc_set_tail(httpdoc);
        _cash = httpdoc.str();
      }
      return _cash;
    }

    bool parse_with_context(
        const std::string &httpdoc,
        std::function<bool(xmlXPathContextPtr context)> parse_method)
    {
      htmlDocPtr doc = htmlReadMemory(httpdoc.c_str(), httpdoc.size(), nullptr, "UTF-8", 0);
      xmlXPathContextPtr context = xmlXPathNewContext(doc);
      bool to_return = false;

      // If exist any element with tgme_widget_message_bubble, use this context
      xmlXPathObjectPtr tgme_widget_message_html_elements;
      const bool inner_context_exists = info_sources::message_widgets_exists(
          context, tgme_widget_message_html_elements);

      if (inner_context_exists)
      {
        const auto nodeNr = tgme_widget_message_html_elements->nodesetval->nodeNr;
        for (int bubble_id = 0; bubble_id < nodeNr; ++bubble_id)
        {
          xmlNodePtr tgme_widget_message_html_element =
              tgme_widget_message_html_elements->nodesetval->nodeTab[bubble_id];
          xmlXPathSetContextNode(tgme_widget_message_html_element, context);

          const bool parsed = parse_method(context);
          to_return |= parsed;
        }
      }

      // If not exist any element with tgme_widget_message_bubble, use all document
      if (!inner_context_exists)
      {
        context = xmlXPathNewContext(doc);
        to_return = parse_method(context);
      }

      xmlXPathFreeContext(context);
      xmlFreeDoc(doc);
      return to_return;
    }
  } // namespace

  TestTelegramWeb::TestTelegramWeb() = default;
  TestTelegramWeb::~TestTelegramWeb() = default;

  std::string TestTelegramWeb::author_name = "Example author";
  std::string TestTelegramWeb::channel_name = "Example";

  void TestTelegramWeb::SetUp()
  {
    parser = new info_sources::telegram_http;
  }

  void TestTelegramWeb::TearDown()
  {
    delete parser;
  }

  void TestTelegramWeb::set_dataset_number(TestTelegramWebDataSets dataset_number)
  {
    this->dataset_number = dataset_number;
    switch (this->dataset_number)
    {
    case TestTelegramWebDataSets::var1:
      httpdoc = get_httpdoc_var1();
      break;
    case TestTelegramWebDataSets::var2:
      httpdoc = get_httpdoc_var2();
      break;
    case TestTelegramWebDataSets::var3:
      httpdoc = get_httpdoc_var3();
      break;
    case TestTelegramWebDataSets::empty:
    default:
      httpdoc = get_httpdoc_empty();
      break;
    }
  }

  TestTelegramWebDataSets TestTelegramWeb::get_dataset_number() const
  {
    return dataset_number;
  }

  std::vector<article> TestTelegramWeb::parse_all()
  {
    return parser->parse_doc(httpdoc);
  }

  bool TestTelegramWeb::parse_element_message_time(article &new_article)
  {
    return parse_with_context(httpdoc, [&new_article](xmlXPathContextPtr context)
                              { return info_sources::parse_element_message_time(new_article, context); });
  }

  bool TestTelegramWeb::parse_element_message_link(article &new_article)
  {
    return parse_with_context(httpdoc, [&new_article](xmlXPathContextPtr context)
                              { return info_sources::parse_element_message_link(new_article, context); });
  }

  bool TestTelegramWeb::parse_element_message_text(article &new_article)
  {
    return parse_with_context(httpdoc, [&new_article](xmlXPathContextPtr context)
                              { return info_sources::parse_element_message_text(new_article, context); });
  }

  bool TestTelegramWeb::parse_element_message_image(article &new_article)
  {
    return parse_with_context(httpdoc, [&new_article](xmlXPathContextPtr context)
                              { return info_sources::parse_element_message_image(new_article, context); });
  }

  bool TestTelegramWeb::parse_element_message_video(article &new_article)
  {
    return parse_with_context(httpdoc, [&new_article](xmlXPathContextPtr context)
                              { return info_sources::parse_element_message_video(new_article, context); });
  }

  bool TestTelegramWeb::parse_element_message_reply(article &new_article)
  {
    return parse_with_context(httpdoc, [&new_article](xmlXPathContextPtr context)
                              { return info_sources::parse_element_message_reply(new_article, context); });
  }

} // namespace gazeta::info_controller