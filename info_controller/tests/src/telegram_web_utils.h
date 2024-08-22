#pragma once
#include "telegram_web.h"
#include <gtest/gtest.h>

namespace gazeta::info_controller {

  enum TestTelegramWebDataSets {
    empty,
    var1,
    var2,
    var3,
  };

  class TestTelegramWeb: public ::testing::Test {
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

    std::vector<common::article> parse_all();
    bool parse_element_message_time(common::article& new_article);
    bool parse_element_message_link(common::article& new_article);
    bool parse_element_message_text(common::article& new_article);
    bool parse_element_message_image(common::article& new_article);
    bool parse_element_message_video(common::article& new_article);
    bool parse_element_message_reply(common::article& new_article);

private:
    info_sources::telegram_http* parser;

    TestTelegramWebDataSets dataset_number;
    std::string httpdoc;
  };
} // namespace gazeta::info_controller
