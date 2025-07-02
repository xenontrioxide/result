#include <result/result.hpp>
#include <string>
#include <gtest/gtest.h>

TEST(error, DefaultConstructor)
{
    const xt::error<int> error{ };
    EXPECT_FALSE(static_cast<bool>(error));
    EXPECT_EQ(*error, 0);
}

TEST(error, ConstructWithLValue)
{
    int value = 10;
    const xt::error<int> error{ value };
    EXPECT_TRUE(static_cast<bool>(error));
    EXPECT_EQ(*error, 10);
}

TEST(error, ConstructWithRValue)
{
    const xt::error<int> error{ 10 };
    EXPECT_TRUE(static_cast<bool>(error));
    EXPECT_EQ(*error, 10);
}

TEST(error, CopyErrorConstructor)
{
    const xt::error<int> orig_error{ 10 };
    const xt::error<int> copied_error{ orig_error };
    EXPECT_TRUE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, 10);
}

TEST(error, CopyNonErrorConstructor)
{
    const xt::error<int> orig_error{ };
    const xt::error<int> copied_error{ orig_error };
    EXPECT_FALSE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, 0);
}

TEST(error, MoveErrorConstructor)
{
    xt::error<int> orig_error{ 10 };
    const xt::error<int> copied_error{ std::move(orig_error) };
    EXPECT_TRUE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, 10);
}

TEST(error, MoveNonErrorConstructor)
{
    xt::error<int> orig_error{ };
    const xt::error<int> copied_error{ std::move(orig_error) };
    EXPECT_FALSE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, 0);
}

TEST(error, TemplatedCopyErrorConstructor)
{
    const xt::error<const char*> orig_error{ "error" };
    const xt::error<std::string> copied_error{ orig_error };
    EXPECT_TRUE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, "error");
}

TEST(error, TemplatedCopyNonErrorConstructor)
{
    const xt::error<const char*> orig_error{ };
    const xt::error<std::string> copied_error{ orig_error };
    EXPECT_FALSE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, "");
}

TEST(error, TemplatedMoveErrorConstructor)
{
    xt::error<const char*> orig_error{ "error" };
    const xt::error<std::string> copied_error{ std::move(orig_error) };
    EXPECT_TRUE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, "error");
}

TEST(error, TemplatedMoveNonErrorConstructor)
{
    xt::error<const char*> orig_error{ };
    const xt::error<std::string> copied_error{ std::move(orig_error) };
    EXPECT_FALSE(static_cast<bool>(copied_error));
    EXPECT_EQ(*copied_error, "");
}

struct custom_error
{
    int code;
    std::string message;

    custom_error(int c, const std::string& m) : code(c), message(m)
    {
    }
};

TEST(error, InPlaceConstruction)
{
    xt::error<custom_error> error(std::in_place, 404, "Not Found");

    EXPECT_TRUE(static_cast<bool>(error));
    EXPECT_EQ((*error).code, 404);
    EXPECT_EQ((*error).message, "Not Found");
}

struct list_error
{
    std::vector<int> codes;
    std::string info;

    list_error(std::initializer_list<int> c, const std::string& i)
        : codes(c), info(i)
    {
    }
};

TEST(error, ConstructsWithInitializerList)
{
    xt::error<list_error> error(std::in_place, { 1, 2, 3 }, "Critical");

    EXPECT_TRUE(static_cast<bool>(error));
    EXPECT_EQ((*error).codes.size(), 3);
    EXPECT_EQ((*error).codes[1], 2);
    EXPECT_EQ((*error).info, "Critical");
}

struct error_wrapper
{
    std::string msg;
    explicit error_wrapper(std::string m) : msg(std::move(m))
    {
    }
};

TEST(error, PerfectForwardsString)
{
    std::string input = "bad state";
    xt::error<error_wrapper> error(input);

    EXPECT_TRUE(static_cast<bool>(error));
    EXPECT_EQ((*error).msg, "bad state");
}

TEST(error, ArrowOperator)
{
    const std::string value{ "error" };
    xt::error<std::string> error(value);
    EXPECT_EQ(error->size(), value.size());
}

TEST(error, ConstArrowOperator)
{
    const std::string value{ "error" };
    const xt::error<std::string> error(value);
    EXPECT_EQ(error->size(), value.size());
}

TEST(error, DereferenceNonConstLValue)
{
    const std::string value{ "error" };
    xt::error<std::string> error(value);
    std::string& ref = *error;
    EXPECT_EQ(ref, value);
    ref = "world";
    EXPECT_EQ(ref, "world");
}

TEST(error, DereferenceConstLValue)
{
    const std::string value{ "error" };
    const xt::error<std::string> error(value);
    const std::string& ref = *error;
    EXPECT_EQ(ref, value);
}

TEST(error, DereferenceNonConstRValue)
{
    const std::string value{ "error" };
    xt::error<std::string> error(value);
    std::string moved = *std::move(error);
    EXPECT_EQ(moved, value);
}

TEST(error, DereferenceConstRValue)
{
    const std::string value{ "error" };
    xt::error<std::string> error(value);
    const std::string moved = *std::move(error);
    EXPECT_EQ(moved, value);
}