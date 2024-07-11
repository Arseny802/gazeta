#pragma once
#include "article.h"
#include <string>
#include <fmt/format.h>

namespace gazeta::info_sources {
  std::string article::format() {
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
}  // namespace gazeta::info_sources
