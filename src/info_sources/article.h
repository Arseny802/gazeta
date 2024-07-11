#pragma once
#include <string>

namespace gazeta::info_sources {
struct article {
  size_t id = 0;
  std::string text;
  std::string time;
  std::string datetime;
  std::string link;
  void *image = nullptr;

  std::string format();
};
}  // namespace gazeta::info_sources
