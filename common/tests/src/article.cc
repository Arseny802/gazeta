#include "pch_tests.h"
#include "common/article.h"

namespace gazeta::info_controller {
  using ::testing::HasSubstr;
  using ::testing::MatchesRegex;

  class TestArticle: public ::testing::Test {
protected:
    void SetUp() { article = new common::article; }
    void TearDown() { delete article; }
    common::article* article;
  };

  TEST_F(TestArticle, TestArticleText) {
    std::string message_content = "6e192d74-2b11-457d-8eec-02e1d3a889d3";
    article->text = message_content;
    ASSERT_THAT(article->format(), HasSubstr(message_content));
  }

  TEST(articleTest, TestArticleFormat) {
    common::article a;

    // Set up some sample data
    a.id = 123;
    a.link = "https://example.com";
    a.datetime = "2022-01-01 12:00:00";
    a.time = "afternoon";
    a.text = "This is my text";

    std::string expectedFormat =
        "Reply to Article\n"
        "Article 123 [https://example.com], DT 2022-01-01 12:00:00 (friendly 'afternoon'), message: 'This is my text'"
        "\n\tImage [URL ]";

    // Call the format method and compare the result
    std::string actualFormat = a.format();
    EXPECT_STREQ(actualFormat.c_str(), expectedFormat.c_str());
  }

  TEST(articleTest, TestArticleFormatWithoutId) {
    common::article a;

    // Set up some sample data
    a.link = "https://example.com";
    a.datetime = "2022-01-01 12:00:00";
    a.time = "afternoon";
    a.text = "This is my text";

    std::string expectedFormat =
        "Article [https://example.com], DT 2022-01-01 12:00:00 (friendly 'afternoon'), message: 'This is my text'"
        "\n\tImage [URL ]";

    // Call the format method and compare the result
    std::string actualFormat = a.format();
    EXPECT_STREQ(actualFormat.c_str(), expectedFormat.c_str());
  }

  TEST(articleTest, TestArticleFormatWithoutLink) {
    common::article a;

    // Set up some sample data
    a.id = 123;
    a.datetime = "2022-01-01 12:00:00";
    a.time = "afternoon";
    a.text = "This is my text";

    std::string expectedFormat =
        "Reply to Article 123, DT 2022-01-01 12:00:00 (friendly 'afternoon'), message: 'This is my text'"
        "\n\tImage [URL ]";

    // Call the format method and compare the result
    std::string actualFormat = a.format();
    EXPECT_STREQ(actualFormat.c_str(), expectedFormat.c_str());
  }

  TEST(articleTest, TestArticleFormatWithoutReply) {
    common::article a;

    // Set up some sample data
    a.id = 123;
    a.link = "https://example.com";
    a.datetime = "2022-01-01 12:00:00";
    a.time = "afternoon";
    a.text = "This is my text";

    std::string expectedFormat =
        "Article 123 [https://example.com], DT 2022-01-01 12:00:00 (friendly 'afternoon'), message: 'This is my text'"
        "\n\tImage [URL ]";

    // Call the format method and compare the result
    std::string actualFormat = a.format();
    EXPECT_STREQ(actualFormat.c_str(), expectedFormat.c_str());
  }

  TEST(articleTest, TestArticleFormatWithoutImages) {
    common::article a;

    // Set up some sample data
    a.id = 123;
    a.link = "https://example.com";
    a.datetime = "2022-01-01 12:00:00";
    a.time = "afternoon";
    a.text = "This is my text";

    std::string expectedFormat =
        "Reply to Article 123, DT 2022-01-01 12:00:00 (friendly 'afternoon'), message: 'This is my text'"
        "";

    // Call the format method and compare the result
    std::string actualFormat = a.format();
    EXPECT_STREQ(actualFormat.c_str(), expectedFormat.c_str());
  }
} // namespace gazeta::info_controller
