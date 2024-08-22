#include "pch_tests.h"
#include "telegram_web_utils.h"

namespace gazeta::info_controller {

  TEST_F(TestTelegramWeb, ParseElementMessageTimeTest) {
    common::article new_article;

    set_dataset_number(TestTelegramWebDataSets::empty);
    EXPECT_FALSE(parse_element_message_time(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var1);
    EXPECT_TRUE(parse_element_message_time(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var2);
    EXPECT_TRUE(parse_element_message_time(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var3);
    EXPECT_TRUE(parse_element_message_time(new_article)) << "Expected parsing of HTTP file 2";
  }

  TEST_F(TestTelegramWeb, parse_element_message_link_test) {
    common::article new_article;

    set_dataset_number(TestTelegramWebDataSets::empty);
    EXPECT_FALSE(parse_element_message_link(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var1);
    EXPECT_TRUE(parse_element_message_link(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var2);
    EXPECT_TRUE(parse_element_message_link(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var3);
    EXPECT_TRUE(parse_element_message_link(new_article)) << "Expected parsing of HTTP file 2";
  }

  TEST_F(TestTelegramWeb, parse_element_message_text_test) {
    common::article new_article;

    set_dataset_number(TestTelegramWebDataSets::empty);
    EXPECT_FALSE(parse_element_message_text(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var1);
    EXPECT_TRUE(parse_element_message_text(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var2);
    EXPECT_TRUE(parse_element_message_text(new_article)) << "Expected parsing of HTTP file 2";

    set_dataset_number(TestTelegramWebDataSets::var3);
    EXPECT_TRUE(parse_element_message_text(new_article)) << "Expected parsing of HTTP file 2";
  }

  TEST_F(TestTelegramWeb, parse_element_message_image_test) {
    common::article new_article;

    set_dataset_number(TestTelegramWebDataSets::empty);
    EXPECT_FALSE(parse_element_message_image(new_article)) << "Expected parsing of HTTP file 2";
  }

  TEST_F(TestTelegramWeb, parse_element_message_video_test) {
    common::article new_article;

    set_dataset_number(TestTelegramWebDataSets::empty);
    EXPECT_FALSE(parse_element_message_video(new_article)) << "Expected parsing of HTTP file 2";
  }

  TEST_F(TestTelegramWeb, parse_element_message_reply_test) {
    common::article new_article;

    set_dataset_number(TestTelegramWebDataSets::empty);
    EXPECT_FALSE(parse_element_message_reply(new_article)) << "Expected parsing of HTTP file 2";
  }

  TEST_F(TestTelegramWeb, parse_all) {
    set_dataset_number(TestTelegramWebDataSets::empty);
    auto all_articles = parse_all();
    EXPECT_EQ(0u, all_articles.size()) << "Expected parsing of empty HTTP file will give no articles";
  }

} // namespace gazeta::info_controller