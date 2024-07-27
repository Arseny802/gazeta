#include <gtest/gtest.h>
#include "info_controller/article.h"

class test_article : public ::testing::Test
{
protected:
	void SetUp()
	{
		article = new gazeta::info_controller::article;
	}
	void TearDown()
	{
		delete article;
	}
	gazeta::info_controller::article *article;
};

TEST_F(test_article, test1)
{
	ASSERT_EQ(article->id, 0);
}
