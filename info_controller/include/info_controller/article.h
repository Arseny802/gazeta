#pragma once
#include <list>
#include <string>

namespace gazeta::info_controller
{
  struct article
  {
    size_t id = 0;
    std::string text;
    std::string time;
    std::string datetime;
    std::string link;
    void *image = nullptr;
    bool is_supported = true;

    struct image_t
    {
      std::string url;
      std::string style;
    };

    std::list<image_t> images;

    std::list<article> reply_to;

    bool is_reply() const noexcept;
    std::string format() const noexcept;
  };
} // namespace gazeta::info_controller
