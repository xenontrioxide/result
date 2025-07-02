#include <result/result.hpp>
#include <string>
#include <gtest/gtest.h>
TEST(success, ConstructFromSuccessWrapperType)
{
    const xt::success_t<std::string> success{ "success!" };
    const xt::result<std::string, int> result(success);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, "success!");
}

TEST(success, ConstructFromSuccessWrapperFunction)
{
    const xt::result<std::string, int> result(xt::success("success!"));
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, "success!");
}

TEST(success, AssignFromSuccessWrapperType)
{
    const xt::result<std::string, int> result = xt::success_t{ "success!" };
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, "success!");
}

TEST(success, AssignFromSuccessWrapperFunction)
{
    const xt::result<std::string, int> result = xt::success("success!");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, "success!");
}