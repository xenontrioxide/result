# xt::result
A lightweight, header-only C++23 implementation of a `result` type for safe and expressive error handling. Inspired by `std::expected`, `Rust's Result<T, E>` and `Go`-style return values, this library provides a minimal and modern approach to representing either a successful result or an error without relying on exceptions.

## Features
- `xt::result<T, E>`: Holds either a value T or an error E
- `xt::error<E>`: Wraps the error type, providing intuitive access and conversion
- Lightweight `success()` and `failure()` helpers
- Structured binding support
- Explicit construction control and type-safe conversions
- No exceptions required
- Fully header-only and dependency-free

## Design Choices
- Supports structured bindings for easy unwrapping of the value and error.
- The error type remains wrapped in `xt::error<E>` when using structured bindings. This allows checking for the presence of an error via `if(error)` without immediately acecssing the underlying value. To access the actual error object, you must explicitly unwrap it using `*error` or `error->`.
- To support structured bindings the `xt::result<T, E>` class stores both `T and xt::error<E>` making it's size larger than `std::expected<T, E>`.

## Example
```cpp
#include <result/result.hpp>
#include <print>

xt::result<int, std::string> divide(const int numerator, const int denominator)
{
  if(denominator == 0)
    return xt::error("Denominator was 0."); // return xt::failure("Denominator was 0.); if you prefer

  return numerator / denominator; // return xt::success(numerator / denominator); if you prefer
}

int main()
{
  const auto& [value, error] = divide(10, 5);
  if(error)
  {
    std::print(std::cout, "Error was: {}\n", *error);
    return 1;
  }

  std::print(std::cout, "Value is: {}\n", value);
  return 0;
}
```

## Requirements
C++23

## Installation
Copy the header into your project and include it
`#include <result/result.hpp>`
