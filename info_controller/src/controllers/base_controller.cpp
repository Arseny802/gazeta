#include "pch.h"
#include "base_controller.h"
#include "common/article.h"
#include "common/source.h"
#include "info_sources/reader.h"
#include "info_sources/telegram_web.h"

namespace gazeta::info_controller::controllers {
  base_controller::~base_controller() = default;

  std::vector<common::article> base_controller::read_n_articles_from_tweb(const common::source& src, size_t to_read) {
    AUTOLOG_IC;

    signed long long to_read_signed = to_read;
    std::vector<common::article> result;
    common::source src_parsing = src;
    info_sources::telegram_http parser;
    info_sources::reader reader;
    do {
      log()->debug("Gettings articles by URL '{0}'.", src.url);
      std::vector<common::article> articles = parser.parse_doc(reader.read_source(src_parsing));
      if (articles.empty()) {
        break;
      }

      src_parsing.url = src.url + "?before=" + std::to_string(articles.begin()->id);
      to_read_signed -= articles.size();
      result.insert(result.cend(), articles.begin(), articles.end());
    }
    while (to_read_signed > 0);

    std::sort(result.begin(), result.end(), [](const common::article& a1, const common::article& a2) {
      return a1.id < a2.id;
    });

    return result;
  }

  std::vector<common::article> base_controller::read_n_articles_from_tweb(const common::source& src,
                                                                          const size_t to_read,
                                                                          size_t before_id) {
    AUTOLOG_IC;

    signed long long to_read_signed = to_read;
    common::source src_parsing(src);
    std::vector<common::article> result;
    info_sources::telegram_http parser;
    info_sources::reader reader;
    do {
      src_parsing.url = src.url + "?before=" + std::to_string(before_id);
      log()->debug("Gettings articles by URL '{0}'.", src.url);

      std::vector<common::article> articles = parser.parse_doc(reader.read_source(src_parsing));
      if (articles.empty()) {
        break;
      }

      before_id = articles.begin()->id;
      to_read_signed -= articles.size();
      result.insert(result.cend(), articles.begin(), articles.end());
    }
    while (to_read_signed > 0);

    std::sort(result.begin(), result.end(), [](const common::article& a1, const common::article& a2) {
      return a1.id < a2.id;
    });

    return result;
  }
} // namespace gazeta::info_controller::controllers
