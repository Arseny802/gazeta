#pragma once
#include <string>

namespace gazeta::common {
  struct source {
    int id;
    std::string name;
    std::string url;
    int source_type_id;
    std::string filter;
    std::string filter_startes_with;
  };
} // namespace gazeta::common
