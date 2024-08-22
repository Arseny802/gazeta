#include "common/article.h"
#include "common/pch.h"

namespace gazeta::common {
  bool article::is_reply() const noexcept {
    return !reply_to.empty();
  }

  /**
   * Returns a formatted string representation of the article.
   *
   * The format includes the article's base name, ID if available, link if provided,
   * datetime and time information, main reply information, message text, and
   * image links. If this article is a reply to another article, the main reply
   * information includes the formatted string representation of each replied-to
   * article.
   *
   * @return A formatted string representing the article.
   */
  std::string article::format() const noexcept {
    std::string base = "Article";
    if (id > 0) {
      base += " " + std::to_string(id);
    }
    if (!link.empty()) {
      base += " [" + link + "]";
    }

    std::string dt = datetime;
    if (!time.empty()) {
      dt = fmt::format("DT {0} (friendly '{1}'), ", datetime, time);
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
} // namespace gazeta::common
