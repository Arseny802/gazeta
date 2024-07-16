#pragma once
#include "article.h"
#include <string>
#include <vector>


namespace gazeta::info_sources {
class telegram_http {
public:
  std::vector<article> parse_doc(const std::string &httpdoc);
};

} // namespace gazeta::info_sources
