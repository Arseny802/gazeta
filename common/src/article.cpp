#include "common/article.h"
#include "common/pch.h"
#include <ctime>
namespace gazeta::common {
  bool article::is_reply() const noexcept {
    return !reply_to.empty();
  }

  std::string article::format() const noexcept {
    std::string base = "Article";
    if (id > 0) {
      base += " " + std::to_string(id);
    }
    if (!link.empty()) {
      base += " [" + link + "]";
    }

    std::string dt = get_datetime();
    if (!time.empty()) {
      dt = fmt::format("DT {0} (friendly '{1}'), ", dt, time);
    }

    std::string reply_main_info{};
    for (auto& r: reply_to) {
      reply_main_info = fmt::format("{0}Reply to {1}\n", reply_main_info, r.format());
    }

    std::string images_links{};
    for (auto& img: images) {
      images_links = fmt::format("{0}\n\tImage [URL {1}]", images_links, img.url);
    }

    return fmt::format("{0}{1}, {2}message: '{3}'{4}", reply_main_info, base, dt, text, images_links);
  }

  bool article::operator==(const article& other) const noexcept {
    return this->id == other.id && this->source_id == other.source_id;
  }

  void article::set_datetime(const std::string& datetime) {
    //"2024-08-23T15:54:39+00:00"
    std::string format{"%Y-%m-%dT%H:%M:%S"};

    tm tmStruct = {};
    std::istringstream ss(datetime);
    ss >> std::get_time(&tmStruct, format.c_str());
    time_t time_t_format = mktime(&tmStruct);
    datetime_occurred = std::chrono::system_clock::from_time_t(time_t_format);
  }

  std::string article::get_datetime() const {
    constexpr std::string_view dt_format = "%Y-%m-%d %H:%M:%S";

    time_t time = std::chrono::system_clock::to_time_t(datetime_occurred);
    tm* timeinfo = localtime(&time);
    char buffer[70];
    strftime(buffer, sizeof(buffer), dt_format.data(), timeinfo);
    return buffer;

    return std::format(dt_format, datetime_occurred);
  }
} // namespace gazeta::common
