#include <result/result.hpp>
#include <print>

xt::result<int, std::string> divide(const int numerator, const int denominator)
{
    if (denominator == 0)
        return xt::error("Denominator was 0."); // return xt::failure("Denominator was 0.); if you prefer

    return numerator / denominator; // return xt::success(numerator / denominator); if you prefer
}

int main()
{
    const auto& [value, error] = divide(10, 5);
    if (error)
    {
        std::print("Error was: {}\n", *error);
        return 1;
    }

    std::print("Value is: {}\n", value);
    return 0;
}