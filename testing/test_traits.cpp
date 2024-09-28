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

enum TestEnumType { TEST_ENUM_VAL = -1 };
enum TestEnumTypeEx : u16 {};

enum class TestEnumClassType {};

struct TestEmptyStruct {};
struct TestStructWithVirtualFunc {
    virtual void foo() {}
};
struct TestStructFinal final : TestStruct {};
struct TestStructPureVirtualFunc {
    virtual ~TestStructPureVirtualFunc() = default;
    virtual void foo() = 0;
};
struct TestStructInheritPureVirtual : TestStructPureVirtualFunc {};

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
// is abstract
static_assert(
       is_abstract_v<TestStructPureVirtualFunc>
    && is_abstract_v<TestStructInheritPureVirtual>
    && !is_abstract_v<TestStruct>
    && !is_abstract_v<TestStructWithVirtualFunc>
    && !is_abstract_v<TestStructFinal>
);
// is aggregate
static_assert(
    is_aggregate_v<TestStruct>
    && is_aggregate_v<TestEmptyUnion>
    && is_aggregate_v<TestUnion>
    && is_aggregate_v<TestStruct::NestedUnion>
    && is_aggregate_v<TestStructFinal> // inherit aggregate type
    && !is_aggregate_v<TestStruct::NestedEnum>
    && !is_aggregate_v<TestEnumClassType>
    && !is_aggregate_v<TestStructInheritPureVirtual> // no member variables
    && !is_aggregate_v<TestStructWithVirtualFunc>
);
// is empty
static_assert(
        is_empty_v<TestEmptyStruct>
    && !is_empty_v<int>            // primitives are not empty types
    && !is_empty_v<TestEmptyUnion> // empty unions are not emtpy types
    && !is_empty_v<TestEnumType>   // empty enums  are not empty types
    && !is_empty_v<TestEnumClassType>
);
// is final
static_assert(
        is_final_v<TestStructFinal>
    &&  is_final_v<const volatile TestStructFinal>
    && !is_final_v<TestStruct>
    && !is_final_v<int>
);
// is polymorphic
static_assert(
        is_polymorphic_v<TestStructPureVirtualFunc>
    &&  is_polymorphic_v<TestStructWithVirtualFunc>
    &&  is_polymorphic_v<TestStructInheritPureVirtual>
    && !is_polymorphic_v<TestStruct>
    && !is_polymorphic_v<TestStructFinal>
    && !is_polymorphic_v<int>
);
// is standard layout
static_assert(
        is_standard_layout_v<int>
    &&  is_standard_layout_v<TestStruct>
    &&  is_standard_layout_v<TestStructFinal>
    &&  is_standard_layout_v<TestEmptyStruct>
    && !is_standard_layout_v<TestStructWithVirtualFunc>
    && !is_standard_layout_v<TestStructPureVirtualFunc>
    && !is_standard_layout_v<TestStructInheritPureVirtual>
);
// is trivial
static_assert(
        is_trivial_v<int> // primitive
    &&  is_trivial_v<TestEmptyStruct>
    &&  is_trivial_v<TestInvocable>
    && !is_trivial_v<TestStruct>
    && !is_trivial_v<TestStructFinal>
    && !is_trivial_v<TestStructPureVirtualFunc>
    && !is_trivial_v<TestStructWithVirtualFunc>
    && !is_trivial_v<TestStructInheritPureVirtual>
);
// extent
static_assert(
       extent_v<int[3]>       == 3
    && extent_v<int[3], 0>    == 3
    && extent_v<int[3][4], 0> == 3
    && extent_v<int[3][4], 1> == 4
    && extent_v<int[3][4], 2> == 0
    && extent_v<int[]>        == 0
);
// remove extents
static_assert(
       is_same_v<int   , remove_extent_t<int>>
    && is_same_v<int   , remove_extent_t<int[]>>
    && is_same_v<int   , remove_extent_t<int[1]>>
    && is_same_v<int[2], remove_extent_t<int[1][2]>>
);
// remove all extents
static_assert(
       is_same_v<int, remove_all_extents_t<int>>
    && is_same_v<int, remove_all_extents_t<int[]>>
    && is_same_v<int, remove_all_extents_t<int[1]>>
    && is_same_v<int, remove_all_extents_t<int[1][2]>>
    && is_same_v<int, remove_all_extents_t<int[1][2][3]>>
    && is_same_v<int, remove_all_extents_t<int[1][2][3][4]>>
);
// is signed
static_assert(
        is_signed_v<signed>
    &&  is_signed_v<signed char>
    &&  is_signed_v<float>
    &&  is_signed_v<double>
    && !is_signed_v<unsigned>
    && !is_signed_v<unsigned int>
    && !is_signed_v<TestStruct>
);
// is unsigned
static_assert(
        is_unsigned_v<unsigned>
    &&  is_unsigned_v<unsigned char>
    &&  is_unsigned_v<unsigned int>
    && !is_unsigned_v<signed>
    && !is_unsigned_v<signed char>
    && !is_unsigned_v<float>
    && !is_unsigned_v<double>
    && !is_unsigned_v<TestStruct>
);
// make signed
static_assert(
        is_same_v<signed char,         make_signed_t<char>>
    &&  is_same_v<signed int,          make_signed_t<int>>
    &&  is_same_v<signed volatile int, make_signed_t<volatile int>>
    &&  is_same_v<signed short,        make_signed_t<short>>
    &&  is_same_v<signed int,          make_signed_t<TestEnumType>>
    &&  is_same_v<signed int,          make_signed_t<TestEnumClassType>>
);
// make unsigned
static_assert(
        is_same_v<unsigned char,         make_unsigned_t<char>>
    &&  is_same_v<unsigned int,          make_unsigned_t<int>>
    &&  is_same_v<unsigned volatile int, make_unsigned_t<volatile int>>
    &&  is_same_v<unsigned short,        make_unsigned_t<short>>
    &&  is_same_v<unsigned int,          make_unsigned_t<TestEnumType>>
    &&  is_same_v<unsigned int,          make_unsigned_t<TestEnumClassType>>
);
// negation
static_assert(
       is_same_v<false_type, typename negation<bool_constant<true>> ::type>
    && is_same_v<true_type,  typename negation<bool_constant<false>>::type>
    && negation_v<true_type>  == false
    && negation_v<false_type> == true
);
// disjunction
static_assert(
        conjunction_v<>
    &&  conjunction_v<true_type, true_type>
    &&  conjunction_v<true_type, true_type, true_type, true_type, true_type>
    && !conjunction_v<true_type, false_type>
    && !conjunction_v<true_type, true_type, true_type, false_type>
);
// conjunction
static_assert(
        disjunction_v<true_type, true_type>
    &&  disjunction_v<true_type, true_type, true_type, true_type, true_type>
    &&  disjunction_v<true_type, false_type>
    &&  disjunction_v<true_type, true_type, true_type, false_type>
    && !disjunction_v<>
    && !disjunction_v<false_type>
    && !disjunction_v<false_type, false_type>
    && !disjunction_v<false_type, false_type, false_type>
);
// enable if
static_assert(
        is_same_v<int, enable_if_t<true, int>>
//  && !is_same_v<float, enable_if_t<false, int>> // should fail to compile
);
// conditional
static_assert(
       is_same_v<int,   conditional_t<true,  int, float>>
    && is_same_v<float, conditional_t<false, int, float>>
);
// underlying type
static_assert(
        is_same_v<int, underlying_type_t<TestEnumType>>
    &&  is_same_v<int, underlying_type_t<TestEnumClassType>>
    &&  is_same_v<u16, underlying_type_t<TestEnumTypeEx>>
);
// decay
static_assert(
        is_same_v<decay_t<int>,        int>
    && !is_same_v<decay_t<int>,        float>
    &&  is_same_v<decay_t<int&>,       int>
    &&  is_same_v<decay_t<int&&>,      int>
    &&  is_same_v<decay_t<const int&>, int>
    &&  is_same_v<decay_t<int[2]>,     int*>
    && !is_same_v<decay_t<int[4][2]>,  int*>
    && !is_same_v<decay_t<int[4][2]>,  int**>
    &&  is_same_v<decay_t<int[4][2]>,  int(*)[2]>
    &&  is_same_v<decay_t<int(int)>,   int(*)(int)>
);
// common type
static_assert(
        is_same_v<int, common_type_t<int, short, char, signed char>>
    &&  is_same_v<TestStruct, common_type_t<TestStruct, TestStructFinal>>
    &&  is_same_v<TestStructPureVirtualFunc, common_type_t<TestStructInheritPureVirtual, TestStructPureVirtualFunc>>
);
// is base of
static_assert(
        is_base_of_v<TestStruct, TestStructFinal>
    &&  is_base_of_v<TestStructPureVirtualFunc, TestStructInheritPureVirtual>
    && !is_base_of_v<TestStructFinal, TestStruct>
    && !is_base_of_v<TestStructInheritPureVirtual, TestStructPureVirtualFunc>
    && !is_base_of_v<int, signed int> // primitives
);

namespace {
    struct TestPod { int data; };
}

// is pod
static_assert(
        is_pod_v<int>
    &&  is_pod_v<TestEmptyStruct>
    &&  is_pod_v<TestEmptyUnion>
    &&  is_pod_v<TestUnion>
    &&  is_pod_v<TestPod>
    && !is_pod_v<TestStruct>
    && !is_pod_v<TestStructPureVirtualFunc>
    && !is_pod_v<TestStructFinal>
    && !is_pod_v<TestStructInheritPureVirtual>
);
// is literal type
static_assert(
        is_literal_type_v<int>
    &&  is_literal_type_v<TestStruct>
    &&  is_literal_type_v<TestStructFinal>
    && !is_literal_type_v<TestStructPureVirtualFunc>
    && !is_literal_type_v<TestStructInheritPureVirtual>
);
namespace {
struct TestDeletedDtorStruct { ~TestDeletedDtorStruct() = delete; };
struct TestNoThrowDtorStruct { ~TestNoThrowDtorStruct() noexcept = default; };
}
// is destructible
static_assert(
        is_destructible_v<int>
    &&  is_destructible_v<TestStruct>
    &&  is_destructible_v<TestStructPureVirtualFunc>
    && !is_destructible_v<void>
    && !is_destructible_v<decltype(TestFunction)>
    && !is_destructible_v<int[]>
    && !is_destructible_v<TestDeletedDtorStruct>
);
// is nothrow destructible
static_assert(
        is_nothrow_destructible_v<int>
    &&  is_nothrow_destructible_v<TestNoThrowDtorStruct>
    && !is_nothrow_destructible_v<TestDeletedDtorStruct>
);
// is convertible
static_assert(
        is_convertible_v<TestStructFinal*, TestStruct*>
    && !is_convertible_v<TestStruct*, TestStructFinal*>
    &&  is_convertible_v<TestStructInheritPureVirtual*, TestStructPureVirtualFunc*>
    &&  is_convertible_v<TestEnumType, int>
);
// // is swappable
static_assert(
        is_swappable_v<int>
    &&  is_swappable_v<TestStruct>
    &&  is_swappable_v<TestStructFinal>
    && !is_swappable_with_v<TestStruct&, TestStructFinal&>
);