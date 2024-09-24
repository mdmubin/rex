#include <gtest/gtest.h>
#include <rex/type_traits.hpp>

// clang-format off
using namespace rex;

namespace {

void TestFunction() {}

union TestEmptyUnion {};

union TestUnion { f32 f; i32 i; };

struct TestStruct {
    int MemberVariable = 0;
    enum  NestedEnum {};
    union NestedUnion{ f32 f; i32 i; };
    void MemberFunction() {}
    static void StaticFunction() {}
};

auto TestLambda = [](){};

struct TestInvocable {
    void operator()() {}
};

enum TestEnumType {};

enum class TestEnumClassType {};

} // namespace

// is same
static_assert(
        is_same_v<int, int>
    &&  is_same_v<i32, int32_t>
    &&  is_same_v<const int*, int const*>
    && !is_same_v<const int, const volatile int>
);
// is const-volatile
static_assert(
        is_const_v<const int>
    &&  is_const_v<const volatile int>
    &&  is_const_v<int const>
    && !is_const_v<int>
    && !is_const_v<volatile int>
    &&  is_volatile_v<volatile int>
    &&  is_volatile_v<const volatile int>
    &&  is_volatile_v<int volatile>
    && !is_volatile_v<int>
    && !is_volatile_v<const int>
);
// remove const volatile
static_assert(
       is_same_v<int, remove_const_t<int>>
    && is_same_v<int, remove_const_t<const int>>
    && is_same_v<int, remove_volatile_t<int>>
    && is_same_v<int, remove_volatile_t<int volatile>>
    && is_same_v<int, remove_cv_t<int>>
    && is_same_v<int, remove_cv_t<const int>>
    && is_same_v<int, remove_cv_t<volatile int>>
    && is_same_v<int, remove_cv_t<const volatile int>>
);
// add const volatile
static_assert(
       is_same_v<const int,          add_const_t<int>>
    && is_same_v<const int,          add_const_t<const int>>
    && is_same_v<volatile const int, add_const_t<volatile int>>
    && is_same_v<volatile int,       add_volatile_t<int>>
    && is_same_v<volatile int,       add_volatile_t<volatile int>>
    && is_same_v<const volatile int, add_volatile_t<const int>>
);
// match const volatile
static_assert(
       is_same_v<int,                match_cv_t<int, int>>
    && is_same_v<const int,          match_cv_t<const int, int>>
    && is_same_v<const volatile int, match_cv_t<const volatile int, int>>
    && is_same_v<const volatile int, match_cv_t<const volatile int, const volatile int>>
);
// is void
static_assert(
        is_void_v<void>
    &&  is_void_v<const void>
    &&  is_void_v<volatile void>
    &&  is_void_v<decltype(TestFunction())>
    &&  is_void_v<decltype(TestLambda())>
    && !is_void_v<void*>
    && !is_void_v<int>
    && !is_void_v<decltype(TestFunction)>
    && !is_void_v<is_void<void>>
);
// is nullptr
static_assert(
        is_null_pointer_v<std::nullptr_t>
    &&  is_null_pointer_v<decltype(nullptr)>
    &&  is_null_pointer_v<const volatile std::nullptr_t>
    && !is_null_pointer_v<int>
);
// is integral
static_assert(
        is_integral_v<int>
    &&  is_integral_v<const volatile int>
    &&  is_integral_v<bool> 
    &&  is_integral_v<char>
    && !is_integral_v<float>
    && !is_integral_v<int*>
    && !is_integral_v<TestStruct>
    &&  is_integral_v<decltype(TestStruct::MemberVariable)>
    && !is_integral_v<TestEnumType>
);
// is floating point
static_assert(
        is_floating_point_v<float>
    &&  is_floating_point_v<const volatile double>
    && !is_floating_point_v<TestStruct>
    && !is_floating_point_v<float&>
    && !is_floating_point_v<double&>
    && !is_floating_point_v<int>
);
// is array
static_assert(
        is_array_v<int[]>
    &&  is_array_v<int[3]>
    &&  is_array_v<TestStruct[]>
    && !is_array_v<TestStruct> 
    &&  is_array_v<TestStruct[3]>
    && !is_array_v<float>
    && !is_array_v<int>
    && !is_array_v<std::array<int, 3>>
);
// is enum
static_assert(
        is_enum_v<TestEnumType>
    &&  is_enum_v<TestEnumClassType>
    && !is_enum_v<int>
    && !is_enum_v<TestStruct>
    &&  is_enum_v<TestStruct::NestedEnum>
);
// is pointer
static_assert(
        is_pointer_v<TestStruct*>
    &&  is_pointer_v<TestStruct const* volatile>
    &&  is_pointer_v<void*>
    &&  is_pointer_v<int*>
    &&  is_pointer_v<int**>
    &&  is_pointer_v<void (*)()>
    && !is_pointer_v<TestStruct>
    && !is_pointer_v<TestStruct&>
    && !is_pointer_v<decltype(&TestStruct::MemberVariable)> // pointer to member variable
    && !is_pointer_v<decltype(&TestStruct::MemberFunction)> // pointer to member function
    && !is_pointer_v<int>
    && !is_pointer_v<int[10]>
    && !is_pointer_v<std::nullptr_t>
);
// is member pointer
static_assert(
        is_member_function_pointer_v<decltype(&TestStruct::MemberFunction)>
    && !is_member_function_pointer_v<decltype(&TestStruct::StaticFunction)>
    && !is_member_function_pointer_v<decltype(&TestFunction)>
    &&  is_member_object_pointer_v<decltype(&TestStruct::MemberVariable)>
    && !is_member_object_pointer_v<TestStruct*>
    &&  is_member_pointer_v<decltype(&TestStruct::MemberVariable)>
    &&  is_member_pointer_v<decltype(&TestStruct::MemberFunction)>
    && !is_member_object_pointer_v<TestStruct::NestedEnum*>
);
// is lval reference
static_assert(
       !is_lvalue_reference_v<int>
    &&  is_lvalue_reference_v<int&>
    && !is_lvalue_reference_v<int&&>
    && !is_lvalue_reference_v<TestStruct>
    &&  is_lvalue_reference_v<TestStruct&>
    && !is_lvalue_reference_v<TestStruct&&>
);
// is lval reference
static_assert(
       !is_rvalue_reference_v<int>
    && !is_rvalue_reference_v<int&>
    &&  is_rvalue_reference_v<int&&>
    && !is_rvalue_reference_v<TestStruct>
    && !is_rvalue_reference_v<TestStruct&>
    &&  is_rvalue_reference_v<TestStruct&&>
);
// is reference
static_assert(
       !is_reference_v<int>
    &&  is_reference_v<int&>
    &&  is_reference_v<int&&>
    && !is_reference_v<TestStruct>
    &&  is_reference_v<TestStruct&>
    &&  is_reference_v<TestStruct&&>
);
// is function
static_assert(
        is_function_v<decltype(TestFunction)>
    &&  is_function_v<decltype(TestStruct::StaticFunction)>
    && !is_function_v<TestInvocable>
    &&  is_function_v<TestInvocable()>
    && !is_function_v<decltype(TestLambda)>
);
// is union
static_assert(
        is_union_v<TestUnion>
    &&  is_union_v<TestEmptyUnion>
    &&  is_union_v<TestStruct::NestedUnion>
    && !is_union_v<int>
);
// is class
static_assert(
        is_class_v<TestStruct>
    &&  is_class_v<TestInvocable>
    &&  is_class_v<decltype(TestLambda)>
    && !is_class_v<TestEnumClassType>
);
// is arithmetic
static_assert(
        is_arithmetic_v<bool>
    &&  is_arithmetic_v<char>
    &&  is_arithmetic_v<char const>
    &&  is_arithmetic_v<int>
    &&  is_arithmetic_v<int const>
    &&  is_arithmetic_v<float>
    &&  is_arithmetic_v<float const>
    &&  is_arithmetic_v<decltype(TestStruct::MemberVariable)>
    && !is_arithmetic_v<TestUnion>
    && !is_arithmetic_v<char&>
    && !is_arithmetic_v<char*>
    && !is_arithmetic_v<int&>
    && !is_arithmetic_v<int*>
    && !is_arithmetic_v<float&>
    && !is_arithmetic_v<float*>
    && !is_arithmetic_v<TestEnumClassType>
    && !is_arithmetic_v<TestStruct>
);
// is compound
static_assert(
        is_compound_v<TestStruct>
    &&  is_compound_v<TestUnion>
    &&  is_compound_v<TestEnumType>
    &&  is_compound_v<decltype(TestFunction)>
    &&  is_compound_v<decltype(&TestFunction)>
    &&  is_compound_v<int[100]>
    &&  is_compound_v<int*>
    &&  is_compound_v<int&>
    &&  is_compound_v<decltype(TestStruct::StaticFunction)>
    &&  is_compound_v<TestStruct::NestedUnion>
    && !is_compound_v<int>
    && !is_compound_v<float>
    && !is_compound_v<char>
    && !is_compound_v<volatile int>
    && !is_compound_v<const char>
);
// is compound
static_assert(
        is_compound_v<TestStruct>
    &&  is_compound_v<TestUnion>
    &&  is_compound_v<TestEnumType>
    &&  is_compound_v<decltype(TestFunction)>
    &&  is_compound_v<decltype(&TestFunction)>
    &&  is_compound_v<int[100]>
    &&  is_compound_v<int*>
    &&  is_compound_v<int&>
    &&  is_compound_v<TestStruct::NestedUnion>
    &&  is_compound_v<decltype(TestStruct::StaticFunction)>
    &&  is_fundamental_v<std::nullptr_t>
    &&  is_fundamental_v<const volatile decltype(nullptr)>
    && !is_compound_v<int>
    && !is_compound_v<float>
    && !is_compound_v<char>
    && !is_compound_v<volatile int>
    && !is_compound_v<const char>
);
// is fundamental
static_assert(
        is_fundamental_v<int>
    &&  is_fundamental_v<float>
    &&  is_fundamental_v<char>
    &&  is_fundamental_v<volatile int>
    &&  is_fundamental_v<const char>
    &&  is_fundamental_v<std::nullptr_t>
    &&  is_fundamental_v<const volatile decltype(nullptr)>
    && !is_fundamental_v<TestStruct>
    && !is_fundamental_v<TestUnion>
    && !is_fundamental_v<TestEnumType>
    && !is_fundamental_v<decltype(TestFunction)>
    && !is_fundamental_v<decltype(&TestFunction)>
    && !is_fundamental_v<int[100]>
    && !is_fundamental_v<int*>
    && !is_fundamental_v<int&>
    && !is_fundamental_v<decltype(TestStruct::StaticFunction)>
    && !is_fundamental_v<TestStruct::NestedUnion>
);
// is object
static_assert(
       !is_object_v<void>
    &&  is_object_v<int>
    && !is_object_v<int&>
    &&  is_object_v<int*>
    && !is_object_v<int*&>
    &&  is_object_v<TestStruct>
    && !is_object_v<TestStruct&>
    &&  is_object_v<TestStruct*>
    && !is_object_v<int()>
    &&  is_object_v<int(*)()>
    && !is_object_v<int(&)()>
);
// is scalar
static_assert(
        is_scalar_v<int>
    &&  is_scalar_v<float>
    &&  is_scalar_v<TestEnumType>
    &&  is_scalar_v<decltype(&TestStruct::MemberVariable)>
    &&  is_scalar_v<decltype(nullptr)>
    && !is_scalar_v<TestStruct>
);