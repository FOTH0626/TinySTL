#ifndef FOTH_TYPE_TRAITS_H
#define FOTH_TYPE_TRAITS_H

// #include <type_traits>

namespace foth{

template <typename T, T val>//把 value 也作为类型的一部分
struct integral_constant{
    static constexpr T value = val;
    using value_type = T;
    using type = integral_constant<T, val>;
    constexpr operator value_type() const noexcept { return value;} //太离谱了，我才知道原来可以重载类型转换，在转换时触发这个函数
    constexpr value_type operator()() const noexcept { return value;}
};

template<bool B>
using bool_constant = integral_constant<bool, B>;//偏特化为Bool

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

//enable if
template<bool, typename T = void>
struct enable_if                    //空结构体会导致，因为不存在type
{};

template<typename T>
struct enable_if<true,T>{           //偏特化true ， 当匹配到false时会编译失败。
    using type = T;
};

template<bool Cond, typename T = void >
using enable_if_t = enable_if<Cond,T>::type;    //简写

//is same
template<class T, class U>
struct is_same : false_type
{};

template <typename T>
struct is_same<T, T> : true_type
{};

//remove cv
template<typename T>
struct remove_cv {
    using type = T;
};

template<typename T>
struct remove_cv<const T>{
    using type = T;
};

template<typename T>
struct remove_cv<volatile T>{
    using type = T;
};

template<typename T>
struct remove_cv<const volatile T>{
    using type = T;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

//remove const
template<typename T>
struct remove_const{
    using type = T;
};

template<typename T>
struct remove_const<const T>{
    using type = T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

//remove volatile           
//volatile 是一个用于声明每次取值不得从cpu缓存取值而是得从内存取值的限定符，用以保持多线程下的数据统一
template<typename T>
struct remove_volatile{
    using type = T;
};

template<typename T>
struct remove_volatile<volatile T>{
    using type = T;
};

template<typename T>
using remove_volatile_t = remove_volatile<T>::type;

//is void 
template<typename T> 
struct is_void : is_same<void, typename remove_cv<T>::type>
{};

template<typename T>
using is_void_t = is_void<T>::type;

template<typename T>
struct is_lvalue_reference : false_type
{};

template<typename T>
struct is_lvalue_reference<T&> : true_type
{};

template<typename T>
constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

//后面太长先不写了



//remove reference
template<typename T>
struct remove_reference{
    using type = T;
};

template<typename T>
struct remove_reference<T&>{
    using type = T;
};

template<typename T>
struct remove_reference<T&&>{
    using type = T;
};

template<typename T>
using remove_reference_t = remove_reference<T>::type;


}

#endif //FOTH_TYPE_TRAITS_H