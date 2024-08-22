#pragma once
#include "common/source.h"
#include <string>

namespace gazeta::info_controller::info_sources {
  class reader {
public:
    std::string read_source(common::source& src);
  };
} // namespace gazeta::info_controller::info_sources
