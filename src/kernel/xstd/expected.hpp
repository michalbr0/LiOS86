#pragma once

#include <type_traits>

#include "../xstd/utility.hpp"

// The following is a partial implementation of std::expected.
// It is NOT fully compliant with the C++23 standard.
// It does not include all the features required by the standard, 
// some specifics are also implemented differently than required.
//
// In particular, for std::expected<T, E> types T and E must be
// sufficiently trivial (see below), T also cannot be (cv-qualified) void.
// Not all member and non-member functions are implemented.
// In particular, the implementation lacks some constructors
// (mainly argument forwarding constructors), monadic operations 
// member functions, as well as emplace and swap (member and non-member).
// Since this implementation is meant to be used with no exception support,
// std::bad_expected_access is not implemented. For this reason member
// function value() is also not implemented (operator* should be used).
// All noexcept specifiers are also dropped.

namespace LiOS86::xstd {

    namespace {
        // helper type traits

        // true if T is a valid type argument of std::unexpected
        template<typename T>
        constexpr bool is_valid_unexpected_argument_v = std::is_object_v<T> &&
                                                        !std::is_array_v<T> &&
                                                        !std::is_const_v<T> &&
                                                        !std::is_volatile_v<T>;
        
        // true if T is a valid type argument of std::expected
        template<typename T>
        constexpr bool is_valid_expected_argument_v = std::is_destructible_v<T> &&
                                                        !std::is_array_v<T> &&
                                                        !std::is_reference_v<T>;

        // Used in the implementation of std::unexpected and std::expected.
        // These limitations are not imposed by the standard; 
        // introduced only to simplify the implementation.
        template<typename T>
        constexpr bool is_sufficiently_trivial_v = std::is_trivially_copy_constructible_v<T> &&
                                                        std::is_trivially_move_constructible_v<T> &&
                                                        std::is_trivially_copy_assignable_v<T> &&
                                                        std::is_trivially_move_assignable_v<T> &&
                                                        std::is_trivially_destructible_v<T>;
    }

    template<typename E>
    requires is_valid_unexpected_argument_v<E> && is_sufficiently_trivial_v<E>
    class unexpected {
        public:
            constexpr unexpected(const unexpected&) = default;
            constexpr unexpected(unexpected&&) = default;

            template<typename Err = E>
            constexpr explicit unexpected(Err&& e) : val_e{xstd::forward<Err>(e)} { }

            constexpr auto error() const& -> const E& {
                return val_e;
            }
            constexpr auto error() & -> E& {
                return val_e;
            }
            constexpr auto error() const&& -> const E&& {
                return val_e;
            }
            constexpr auto error() && -> E&& {
                return val_e;
            }

            template<class E2>
            friend constexpr auto operator==(unexpected& lhs, xstd::unexpected<E2>& rhs) -> bool {
                return lhs.error() == rhs.error();
            }

        private:
            E val_e;
    };

    template<typename E>
    unexpected(E) -> unexpected<E>;

    template<typename T, typename E>
    requires is_valid_expected_argument_v<T> &&
                (!std::is_void_v<T>) && 
                is_sufficiently_trivial_v<T> &&
                is_valid_expected_argument_v<E> &&
                is_valid_unexpected_argument_v<E> &&
                is_sufficiently_trivial_v<E>
    class expected {
        public:
            using value_type = T;
            using error_type = E;
            using unexpected_type = xstd::unexpected<E>;

            constexpr expected() : val_t{}, has_val{true} { }
            constexpr expected(const expected& other) = default;
            constexpr expected(expected&& other) = default;
            constexpr expected& operator=(const expected& other) = default;
            constexpr expected& operator=(expected&& other) = default;

            template<typename U = T>
            constexpr explicit(!std::is_convertible_v<U, T>) expected(U&& v) 
                : val_t{xstd::forward<U>(v)}, has_val{true} { }

            template<typename G>
            constexpr explicit(!std::is_convertible_v<const G&, E>) expected(const xstd::unexpected<G>& e)
                : val_e{e}, has_val{false} { }

            template<typename G>
            constexpr explicit(!std::is_convertible_v<G,E>) expected(xstd::unexpected<G>&& e)
                : val_e{xstd::move(e)}, has_val{false} { }

            template<typename G>
            constexpr expected& operator=(const unexpected<G>& e) {
                val_e = e;
                has_val = false;
            }

            template<typename G>
            constexpr expected& operator=(unexpected<G>&& e) {
                val_e = xstd::move(e);
                has_val = false;
            }

            constexpr ~expected() = default;

            constexpr auto operator->() const -> const T* {
                return &val_t;
            }
            constexpr auto operator->() -> T* {
                return &val_t;
            }
            constexpr auto operator*() const& -> const T& {
                return val_t;
            }
            constexpr auto operator*() & -> T& {
                return val_t;
            }
            constexpr auto operator*() const&& -> const T&& {
                return val_t;
            }
            constexpr auto operator*() && -> T&& {
                return val_t;
            }

            constexpr explicit operator bool() const {
                return has_val;
            }
            constexpr auto has_value() const -> bool {
                return has_val;
            }

            constexpr auto error() const& -> const E& {
                return val_e.error();
            }
            constexpr auto error() & -> E& {
                return val_e.error();
            }
            constexpr auto error() const&& -> const E&& {
                return val_e.error();
            }
            constexpr auto error() && -> E&& {
                return val_e.error();
            }

            template<typename U>
            constexpr auto value_or(U&& default_value) const& -> T {
                return bool(*this) ? **this : static_cast<T>(xstd::forward<U>(default_value));
            }

            template<typename U>
            constexpr auto value_or(U&& default_value) && -> T {
                return bool(*this) ? xstd::move(**this) : static_cast<T>(xstd::forward<U>(default_value));
            }

            template<typename T2, typename E2>
            friend constexpr auto operator==(const expected& lhs, const xstd::expected<T2, E2>& rhs) -> bool {
                if(lhs.has_value() != rhs.has_value()) return false;
                if(lhs.has_value()) return *lhs == *rhs;
                else return lhs.error() == rhs.error();
            }

            template<typename T2>
            friend constexpr auto operator==(const expected& x, const T2& val) -> bool {
                if(!x.has_value()) return false;
                return *x == val;
            }

            template<typename E2>
            friend constexpr auto operator==(const expected& x, const unexpected<E2>& e) -> bool {
                if(x.has_value()) return false;
                return x.error() == e.error();
            }

        private:
            union {
                T val_t;
                xstd::unexpected<E> val_e;
            };
            bool has_val;
    };

}
