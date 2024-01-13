#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;

namespace dmc
{

    template <typename Container, typename Functor>
    constexpr Container transform(const Container& c, Functor f)
    {
        Container t{};
        for(unsigned i = 0; i < size(c); ++i)
        {
            t[i] = f(c[i]);
        }
        return t;
    }

    constexpr int inc_by_3(int i)
    {
        return i + 3;
    }
}

int main()
{
    constexpr array<int, 6> a{{3, 7, 2, 4, 5, 9}};
    constexpr auto daf = dmc::transform(a, dmc::inc_by_3);
    copy(begin(daf), end(daf), ostream_iterator<int>(cout, ", "));
    cout << endl;

    constexpr auto dal1 = dmc::transform(a, [](int i) constexpr -> int { return i + 3; });
    copy(begin(dal1), end(dal1), ostream_iterator<int>(cout, ", "));
    cout << endl;

    int inc = 3;
    constexpr int cinc = 3;
    constexpr auto dal2 = dmc::transform(a, [](int i){ return i + cinc; });
    copy(begin(dal2), end(dal2), ostream_iterator<int>(cout, ", "));
    cout << endl;

    constexpr auto l1 = [](int i){ return i + 3; };

    auto l3 = [](int i){ return i+3; };
    constexpr auto dal3 = dmc::transform(a, l3);
    copy(begin(dal3), end(dal3), ostream_iterator<int>(cout, ", "));
    cout << endl;

    (void)inc; (void)l1;
    
    return 0;
}

