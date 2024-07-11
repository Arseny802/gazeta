#include "pch.h"
#include "info_sources/article.h"
#include "info_sources/reader.h"
#include "info_sources/source.h"
#include "info_sources/telegram_web.h"


using namespace gazeta::info_sources;

std::vector<article> read_n_articles(int to_read) {
  AUTOLOG

  std::vector<article> result;
  std::string base_url = "https://t.me/s/rian_ru/";
  std::string url = base_url;
  telegram_http parser;
  reader reader;
  do {
    source src;
    src.url = url;

    hare::info("Gettings articles by URL '{0}'.", src.url);
    std::vector<article> articles = parser.parse_doc(reader.read_source(src));
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

int main() {
  gazeta::initialize_logging();
  AUTOLOG

  std::vector<article> articles = read_n_articles(100);
  for (auto& art : articles) {
    hare::info(art.format());
  }

  return 0;
}