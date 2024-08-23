#pragma once

namespace gazeta::common {
  /// @brief Date and time of the article.
  // using article_dt_t = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
  using article_dt_t = std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration>;

  struct article {
    size_t id = 0;
    size_t source_id = 0;

    std::string text;
    std::string time;
    // std::string datetime;
    article_dt_t datetime_occurred;
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
    std::string format() const noexcept;

    /// @brief Convert string to article_dt_t and save it to datetime_occurred.
    /// @param datetime - string in any format
    void set_datetime(const std::string& datetime);
    std::string get_datetime() const;

    bool operator==(const article& other) const noexcept;
  };
} // namespace gazeta::common
