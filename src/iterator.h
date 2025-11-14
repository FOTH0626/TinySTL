#ifndef FOTH_ITERATOR_H
#define FOTH_ITERATOR_H

// #include <iterator>

#include <cstddef>


namespace foth {


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};

template<typename Category, typename T, typename Distance = ptrdiff_t, //ptrdiff_t 被定义为两个指针相减得到的signed int
        typename Pointer = T*, class Reference = T&>
struct iterator{
    using iterator_category = Category;
    using value_type        = T;
    using pointer           = Pointer;
    using reference         = Reference;
    using difference_type   = Distance;
};

// template <typename T>
// struct has_iterator_cat{
// private:
//     struct two
// }

}

#endif //FOTH_ITERATOR_H