#include "base_controller.h"
#include "info_controller/article.h"
#include "info_controller/source.h"
#include "info_sources/reader.h"
#include "info_sources/telegram_web.h"
#include "pch.h"

namespace gazeta::info_controller::controllers {

base_controller::~base_controller() = default;

std::vector<article> base_controller::read_n_articles_from_tweb(const source& src, int to_read) {
  AUTOLOG

  std::vector<article> result;
  source src_parsing = src;
  info_sources::telegram_http parser;
  info_sources::reader reader;
  do {
    hare::debug("Gettings articles by URL '{0}'.", src.url);
    std::vector<article> articles =
        parser.parse_doc(reader.read_source(src_parsing));
    if (articles.empty()) {
      break;
    }

    src_parsing.url = src.url + "?before=" + std::to_string(articles.begin()->id);
    to_read -= static_cast<int>(articles.size());
    result.insert(result.cend(), articles.begin(), articles.end());
  } while (to_read > 0);

  std::sort(result.begin(), result.end(),
            [](const article &a1,
               const article &a2) { return a1.id < a2.id; });

  return result;
}
} // namespace gazeta::info_controller::controllers
