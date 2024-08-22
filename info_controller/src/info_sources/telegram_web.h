#pragma once
#include "common/article.h"
#include <string>
#include <vector>

namespace gazeta::info_controller::info_sources {
  class telegram_http {
public:
    std::vector<common::article> parse_doc(const std::string& httpdoc);
  };
} // namespace gazeta::info_controller::info_sources
