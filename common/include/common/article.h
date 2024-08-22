#pragma once
#include <list>
#include <string>

namespace gazeta::common {
  struct article {
    size_t id = 0;
    size_t source_id = 0;

    std::string text;
    std::string time;
    std::string datetime;
    std::string link;
    void* image = nullptr;
    bool is_supported = true;

    struct image_t {
      std::string url;
      std::string style;
    };

    bool images_attached = false;
    std::list<image_t> images;

    size_t reply_to_id = 0;
    std::list<article> reply_to;

    bool is_reply() const noexcept;
    std::string format() const noexcept;

    bool operator==(const article& other) const noexcept;
  };
} // namespace gazeta::common
