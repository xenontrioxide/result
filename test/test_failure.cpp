#include <result/result.hpp>
#include <string>
#include <gtest/gtest.h>

TEST(failure, ConstructFromFailureWrapperType)
{
    const xt::failure_t<std::string> failure{ "failure!" };
    const xt::result<std::string, std::string> result{ failure };
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.get_error(), "failure!");
}

TEST(failure, ConstructFromFailureWrapperFunction)
{
    const xt::result<std::string, std::string> result{ xt::failure("failure!") };
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.get_error(), "failure!");
}

TEST(failure, AssignFromFailureWrapperType)
{
    const xt::result<std::string, std::string> result = xt::failure_t{ "failure!" };
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.get_error(), "failure!");
}

TEST(failure, AssignFromFailureWrapperFunction)
{
    const xt::result<std::string, std::string> result = xt::failure("failure!");
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.get_error(), "failure!");
}