#pragma once
#include "source.h"
#include <string>

namespace gazeta::info_sources {
class reader {
  public:
  std::string read_source(source &src);
};

}  // namespace gazeta::info_sources
