#include <iostream>
#include <list>
#include <forward_list>
#include <iterator>
#include "print_compiler.hpp"

using namespace std;

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator &i, Distance n, input_iterator_tag tag [[maybe_unused]])
{
    assert(n >= 0);
    for(; n > 0; --n)
    {
        ++i;
    }
}

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator &i, Distance n, bidirectional_iterator_tag tag [[maybe_unused]])
{
    if(n >= 0)
    {
        for(; n > 0; --n)
        {
            ++i;
        }
    }
    else
    {
        for(; n < 0; ++n)
        {
            --i;
        }
    }
}

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator& i, Distance n, random_access_iterator_tag tag [[maybe_unused]])
{
    i += n;
}

template <typename Iterator, typename Distance>
inline void advance(Iterator& i, Distance n)
{
    using cat = typename iterator_traits<Iterator>::iterator_category;
    advance_aux(i, n, cat{});
}

int main()
{
    print_compiler();
    list<int> l = { 3, 7, 9, 11 };
    auto it = l.end();
    ::advance(it, -2);

    cout << *it << '\n';

    return 0;
}
