#pragma once
#include <cstddef>
#include <tuple>
#include <utility>
#include <type_traits>
#include <initializer_list>

namespace xt
{
    template <typename Err>
    class error
    {
        template <typename, typename>
        friend class result;
    public:
        template <class UErr = Err>
            requires(!std::is_same_v<std::remove_cvref_t<UErr>, error> &&
                     !std::is_same_v<std::remove_cvref_t<UErr>, std::in_place_t> &&
                      std::constructible_from<Err, UErr>)
        constexpr explicit error(UErr&& err) 
            : m_has_error(true), m_error(std::forward<UErr>(err))
        {

        }

        template <class... Args>
            requires(std::constructible_from<Err, Args...>)
        constexpr explicit error(std::in_place_t, Args&&... values)
            : m_has_error(true), m_error(std::forward<Args>(values)...)
        {

        }

        template <class UTy, class... Args>
            requires(std::constructible_from<Err, std::initializer_list<UTy>&, Args...>)
        constexpr explicit error(std::in_place_t, std::initializer_list<UTy> list, Args&&... values)
            : m_has_error(true), m_error(list, std::forward<Args>(values)...)
        {

        }

        template <typename UErr>
            requires(std::constructible_from<Err, const UErr&> &&
                     !std::is_same_v<std::remove_cvref_t<UErr>, error>)
        constexpr explicit(!std::is_convertible_v<const UErr&, Err>) error(const error<UErr>& other)
            : m_has_error(other)
        {
            if (m_has_error)
            {
                m_error = { (*other) };
            }
            else
            {
                m_error = {};
            }
        }

        template <typename UErr>
            requires(std::constructible_from<Err, UErr> &&
                     !std::is_same_v<std::remove_cvref_t<UErr>, error>)
        constexpr explicit(!std::is_convertible_v<UErr, Err>) error(error<UErr>&& other)
            : m_has_error(other)
        {
            if (m_has_error)
            {
                m_error = { (*other) };
            }
            else
            {
                m_error = {};
            }
        }

        error() : m_has_error(false), m_error()
        {
        }

        operator bool() const
        {
            return m_has_error;
        }

        const Err* operator->() const
        {
            return &m_error;
        }

        Err* operator->()
        {
            return &m_error;
        }

        Err& operator*() &
        {
            return m_error;
        }

        const Err& operator*() const&
        {
            return m_error;
        }

        Err&& operator*() &&
        {
            return std::move(m_error);
        }

        const Err&& operator*() const&&
        {
            return std::move(m_error);
        }

    private:
        Err m_error;
        bool m_has_error;
    };

    template <class Err>
    error(Err) -> error<Err>;

    template <typename T>
    struct success_t
    {
        T value;
    };

    template <typename T>
    struct failure_t
    {
        T error;
    };

    template <typename T>
    success_t<T> success(T&& val)
    {
        return { std::forward<T>(val) };
    }

    template <typename E>
    failure_t<E> failure(E&& err)
    {
        return { std::forward<E>(err) };
    }

    template <typename Ty, typename Err>
    class result
    {
        using value_type = Ty;
        using error_type = Err;

        template <typename>
        friend class error;

        template <typename, typename>
        friend class result;

    public:
        //Result-Start
        constexpr result()
            : m_value(), m_error()
        {

        }

        constexpr result(const result& other)
            : m_value(other.m_value), m_error()
        {

        }

        constexpr result(const result&& other) noexcept
            : m_value(std::move(other.m_value)), m_error()
        {

        }

        template <class UTy, class UErr>
            requires (!std::is_same_v<result<UTy, UErr>, result<Ty, Err>> &&
                       std::constructible_from<Ty, UTy> &&
                       std::constructible_from<Err, UErr>)
        constexpr explicit(!std::is_convertible_v<const UTy&, Ty> || !std::is_convertible_v<const UErr&, Err>) result(const result<UTy, UErr>& other)
            : m_value(other.m_value), m_error()
        {

        }

        template <class UTy, class UErr>
            requires (!std::is_same_v<result<UTy, UErr>, result<Ty, Err>> &&
                       std::constructible_from<Ty, UTy> &&
                       std::constructible_from<Err, UErr>)
        constexpr explicit(!std::is_convertible_v<const UTy&, Ty> || !std::is_convertible_v<const UErr&, Err>) result(result<UTy, UErr>&& other)
            : m_value(std::move(other.m_value)), m_error()
        {

        }

        template <typename UTy = Ty>
            requires (!std::is_same_v<std::remove_cvref_t<UTy>, result> &&
                      !std::is_same_v<std::remove_cvref_t<UTy>, std::in_place_t> &&
                      !std::is_same_v<std::remove_cvref_t<UTy>, error<Err>>&&
                      std::constructible_from<Ty, UTy>)
        constexpr explicit(!std::is_convertible_v<UTy, Ty>) result(UTy&& value) noexcept(std::is_nothrow_constructible_v<Ty, UTy>)
            : m_value(std::forward<UTy>(value)), m_error()
        {
        }

        template <class... Args>
            requires(std::constructible_from<Ty, Args...>)
        constexpr explicit result(std::in_place_t, Args&&... values)
            : m_value(std::forward<Args>(values)...), m_error()
        {

        }

        template <typename UTy, class... Args>
            requires(std::constructible_from<Ty, std::initializer_list<UTy>&, Args...>)
        constexpr explicit result(std::in_place_t, std::initializer_list<UTy> list, Args&&... values)
            : m_value(list, std::forward<Args>(values)...), m_error()
        {

        }
        //Result-End

        //Error-Start
        template <class UErr>
            requires (std::constructible_from<Err, const UErr&>)
        constexpr explicit(!std::is_convertible_v<const UErr&, Err>) result(const error<UErr>& err) 
            : m_value(), m_error(err.m_error)
        {

        }

        template <class UErr>
            requires (std::constructible_from<Err, const UErr>)
        constexpr explicit(!std::is_convertible_v<UErr, Err>) result(error<UErr>&& err) 
            : m_value(), m_error(std::forward<UErr>(err.m_error))
        {

        }
        //Error-End

        //Success-Start
        template <class UTy>
            requires (std::constructible_from<Ty, const UTy>)
        constexpr explicit(!std::is_convertible_v<UTy, Ty>) result(const success_t<UTy>& success) 
            : m_value(success.value), m_error()
        {

        }
        //Success-End

        //Failure-Start
        template <typename UErr>
            requires std::constructible_from<Err, UErr>
        constexpr explicit(!std::is_convertible_v<UErr, Err>) result(const failure_t<UErr>& failure)
            : m_value(), m_error(static_cast<UErr>(failure.error))
        {

        }
        //Failure-End

        operator bool() const
        {
            return !(m_error);
        }

        bool has_value() const
        {
            return !(m_error);
        }

        value_type get_value() const
        {
            return m_value;
        }

        error_type get_error() const
        {
            return *m_error;
        }

        const value_type* operator->() const
        {
            return &m_value;
        }

        value_type* operator->()
        {
            return &m_value;
        }

        value_type& operator*()&
        {
            return m_value;
        }

        const value_type& operator*() const&
        {
            return m_value;
        }

        value_type&& operator*()&&
        {
            return std::move(m_value);
        }

        const value_type&& operator*() const&&
        {
            return std::move(m_value);
        }

        //Structured Binding
        template <std::size_t index>
        std::tuple_element_t<index, result<value_type, error_type>>& get()&
        {
            if constexpr (index == 0) return m_value;
            if constexpr (index == 1) return m_error;
        }

        template <std::size_t index>
        std::tuple_element_t<index, result<value_type, error_type>>&& get()&&
        {
            if constexpr (index == 0) return std::move(m_value);
            if constexpr (index == 1) return std::move(m_error);
        }

        template <std::size_t index>
        const std::tuple_element_t<index, result<value_type, error_type>>& get() const&
        {
            if constexpr (index == 0) return m_value;
            if constexpr (index == 1) return m_error;
        }

        template <std::size_t index>
        const std::tuple_element_t<index, result<value_type, error_type>>&& get() const&&
        {
            if constexpr (index == 0) return std::move(m_value);
            if constexpr (index == 1) return std::move(m_error);
        }

    private:
        value_type m_value;
        error<error_type> m_error;
    };
}  // namespace xt

namespace std
{
    template <typename T, typename E>
    struct tuple_size<xt::result<T, E>> : integral_constant<size_t, 2>
    {
    };

    template <typename T, typename E>
    struct tuple_element<0, xt::result<T, E>>
    {
        using type = T;
    };

    template <typename T, typename E>
    struct tuple_element<1, xt::result<T, E>>
    {
        using type = xt::error<E>;
    };
}