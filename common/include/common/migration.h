#pragma once
#include <string>

namespace gazeta::common {
  struct migration {
    std::string name;
    int datetime_passed;
  };
} // namespace gazeta::common
