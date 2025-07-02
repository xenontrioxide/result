#include <result/result.hpp>
#include <string>
#include <gtest/gtest.h>
TEST(result, DefaultConstructor)
{
    xt::result<int, std::string> result{ };
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0); // default-constructed int
}

TEST(result, CopyConstructor)
{
    const xt::result<std::string, std::string> orig_result{ "hello" };
    const xt::result<std::string, std::string> copied_result{ orig_result };
    EXPECT_TRUE(copied_result.has_value());
    EXPECT_EQ(*copied_result, "hello");
}

TEST(result, MoveConstructor)
{
    xt::result<std::string, std::string> orig_result{ "hello" };
    const xt::result<std::string, std::string> moved_into_result{ std::move(orig_result) };
    EXPECT_TRUE(moved_into_result.has_value());
    EXPECT_EQ(*moved_into_result, "hello");
}

TEST(result, TemplatedCopyConstructor)
{
    const xt::result<const char*, const char*> orig_result{ "hello" };
    const xt::result<std::string, std::string> copied_result{ orig_result };
    EXPECT_TRUE(copied_result.has_value());
    EXPECT_EQ(*copied_result, "hello");
}

TEST(result, TemplatedMoveConstructor)
{
    xt::result<const char*, const char*> orig_result{ "hello" };
    const xt::result<std::string, std::string> moved_into_result{ std::move(orig_result) };
    EXPECT_TRUE(moved_into_result.has_value());
    EXPECT_EQ(*moved_into_result, "hello");
}

TEST(result, GenericValueConstructor)
{
    const xt::result<std::string, std::string> result{ "value" };
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(*result, "value");
}

TEST(result, FromErrorLValue)
{
    const xt::error<std::string> error{ "failure" };
    const xt::result<int, std::string> result{ error };
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.get_error(), "failure");
}

TEST(result, FromErrorRValue)
{
    const xt::result<int, std::string> result{ xt::error<std::string>{ "failure" } };
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.get_error(), "failure");
}

struct custom_result
{
    int code;
    std::string message;

    custom_result(int c, const std::string& m) : code(c), message(m)
    {
    }
};

TEST(result, InPlaceConstruction)
{
    xt::result<custom_result, std::string> result{ std::in_place, 200, "Success!" };

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ((*result).code, 200);
    EXPECT_EQ((*result).message, "Success!");
}

struct list_result
{
    std::vector<int> codes;
    std::string info;

    list_result(std::initializer_list<int> c, const std::string& i)
        : codes(c), info(i)
    {
    }
};

TEST(result, ConstructsWithInitializerList)
{
    xt::result<list_result, std::string> result{ std::in_place, { 1, 2, 3 }, "Valid" };

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ((*result).codes.size(), 3);
    EXPECT_EQ((*result).codes[1], 2);
    EXPECT_EQ((*result).info, "Valid");
}

TEST(result, HasValue)
{
    const auto result = xt::result<int, std::string>{ 10 };
    EXPECT_TRUE(result.has_value());
}

TEST(result, DoesNotHaveValue)
{
    const auto result = xt::result<int, std::string>{ xt::error<std::string>{ "failure" } };
    EXPECT_FALSE(result.has_value());
}

TEST(result, GetValue)
{
    const auto result = xt::result<int, std::string>{ 10 };
    EXPECT_EQ(result.get_value(), 10);
}

TEST(result, GetError)
{
    const auto result = xt::result<int, std::string>{ xt::error<std::string>{ "failure" } };
    EXPECT_EQ(result.get_error(), "failure");
}

TEST(result, ArrowOperator)
{
    const std::string value{ "value!" };
    auto result = xt::result<std::string, std::string>{ value };
    EXPECT_EQ(result->size(), value.size());
}

TEST(result, ConstArrowOperator)
{
    const std::string value{ "value!" };
    const auto result = xt::result<std::string, std::string>{ value };
    EXPECT_EQ(result->size(), value.size());
}

TEST(result, DereferenceNonConstLValue)
{
    const std::string value{ "value!" };
    auto result = xt::result<std::string, std::string>{ value };
    std::string& ref = *result;
    EXPECT_EQ(ref, value);
    ref = "changed";
    EXPECT_EQ(ref, "changed");
}

TEST(result, DereferenceConstLValue)
{
    const std::string value{ "value!" };
    const auto result = xt::result<std::string, std::string>{ value };
    const std::string& ref = *result;
    EXPECT_EQ(ref, value);
}

TEST(result, DereferenceNonConstRValue)
{
    const std::string value{ "value!" };
    auto result = xt::result<std::string, std::string>{ value };
    std::string moved = *std::move(result);
    EXPECT_EQ(moved, value);
}

TEST(result, DereferenceConstRValue)
{
    const std::string value{ "value!" };
    auto result = xt::result<std::string, std::string>{ value };
    const std::string moved = *std::move(result);
    EXPECT_EQ(moved, value);
}

TEST(result, StructuredBinding)
{
    const auto result = xt::result<int, std::string>{ 10 };
    const auto& [value, error] = result;
    EXPECT_FALSE(error);
    EXPECT_EQ(value, 10);
}
