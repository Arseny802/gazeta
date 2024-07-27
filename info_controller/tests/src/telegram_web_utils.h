#pragma once
#include <gtest/gtest.h>
#include "telegram_web.h"

namespace gazeta::info_controller
{

  enum TestTelegramWebDataSets
  {
    empty,
    var1,
    var2,
    var3,
  };

  class TestTelegramWeb : public ::testing::Test
  {
  public:
    TestTelegramWeb();
    ~TestTelegramWeb();

    static std::string author_name;
    static std::string channel_name;

  protected:
    void SetUp() override;
    void TearDown() override;

    void set_dataset_number(TestTelegramWebDataSets dataset_number);
    TestTelegramWebDataSets get_dataset_number() const;

    std::vector<article> parse_all();
    bool parse_element_message_time(article &new_article);
    bool parse_element_message_link(article &new_article);
    bool parse_element_message_text(article &new_article);
    bool parse_element_message_image(article &new_article);
    bool parse_element_message_video(article &new_article);
    bool parse_element_message_reply(article &new_article);

  private:
    info_sources::telegram_http *parser;

    TestTelegramWebDataSets dataset_number;
    std::string httpdoc;
  };
} // namespace gazeta::info_controller
