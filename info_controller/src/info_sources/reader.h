#pragma once
#include "info_controller/source.h"
#include <string>

namespace gazeta::info_controller::info_sources
{
  class reader
  {
  public:
    std::string read_source(source &src);
  };
} // namespace gazeta::info_controller::info_sources
