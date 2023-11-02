#include <stdx/type_traits.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {
template <typename> struct unary_t {};
template <typename...> struct variadic_t {};
template <typename T> struct derived_t : unary_t<T> {};
} // namespace

TEST_CASE("detect specializations", "[type_traits]") {
    static_assert(stdx::is_specialization_of_v<unary_t<int>, unary_t>);
    static_assert(not stdx::is_specialization_of_v<int, unary_t>);

    static_assert(stdx::is_specialization_of_v<variadic_t<>, variadic_t>);
    static_assert(not stdx::is_specialization_of_v<int, variadic_t>);
}

TEST_CASE("derived types are not specializations", "[type_traits]") {
    static_assert(not stdx::is_specialization_of_v<derived_t<int>, unary_t>);
}

namespace {
enum E1 {};
enum struct E2 {};
} // namespace

TEST_CASE("is_scoped_enum", "[type_traits]") {
    static_assert(not stdx::is_scoped_enum_v<E1>);
    static_assert(stdx::is_scoped_enum_v<E2>);
}

TEST_CASE("type_identity", "[type_traits]") {
    static_assert(std::is_same_v<stdx::type_identity_t<void>, void>);
}
