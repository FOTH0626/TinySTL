#ifndef FOTH_UTILITY_H
#define FOTH_UTILITY_H

// #include <utility>


#include "type_traits.h"

namespace foth{

//move
//从作用来看，move并不移动任何东西，它只是无条件的把值类别转为一个右值引用
template<typename T>
[[nodiscard,__gnu__::__always_inline__]]//返回值必须被使用，函数必须内联展开
constexpr typename foth::remove_reference_t<T>&&  //声明返回类型
move ( T&& t) noexcept {
    return static_cast<foth::remove_reference_t<T>&&>(t);//static_cast为关键词（keyword)，不属于STL
}

//通常用于转发参数包并保持左值/右值的值类别

//当进入参数包为左值 ，如 int&  则会通过重载决议匹配到该函数，
// 并通过引用折叠（即T推导为 int&,返回值为 int& && ,折叠为一个左值引用。而move函数先移除引用保持返回值永远为右值）
// 保持左值性。
//当进入参数包为右值时，如果通过别的函数的参数转发，比如
/* template< typename T>
 * auto foo (T&& arg){
 *  ...
 *   ...forward<T>(arg);
 * }
 * 
 * 调用如foo(10)时，
 * T会被推导为int，但是对于重载1有：
 * int&& forward ( int& t) noexcept
 * 与重载2有：
 * int&& forward ( int&& t ) noexcept
 * 这里的 t 实际为 foo **函数体内的arg**, 这是一个类型为 int&& 的 左值，所以最终重载决议为重载1,
 * 对于重载2 通常只会在直接调用类似于 forward<T>(10) ，使用字面量调用会匹配到重载2
 * 但是这里仍然保持了转发结果为右值。
 * 更详细的解释可以使用LLM
 */
template <typename T>
constexpr T&& forward ( foth::remove_reference_t<T>& t) noexcept{
    return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& forward ( foth::remove_reference_t<T>&& t) noexcept {
    static_assert(!foth::is_lvalue_reference_v<T>, "bad forward");
    return static_cast<T&&>(t);
}



}

#endif //FOTH_UTILITY_H