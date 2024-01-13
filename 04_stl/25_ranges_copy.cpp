#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

namespace dmc {

    using namespace ranges;

    template <typename R>
    concept ResizableRange =
        range<R> &&
        requires(R& r, size_t n)
        {
            r.resize(n);
        };

    template <sized_range Source, ResizableRange Target>
    auto copy(const Source& src, Target& tgt)
    {
        tgt.resize(std::ranges::size(src));
        return std::ranges::copy(src, std::begin(tgt));
    }

}

template <typename OStreamT>
auto& operator<<(OStreamT& os, const std::ranges::range auto& range)
{
    const auto begin = std::ranges::cbegin(range);
    const auto end = std::ranges::cend(range);

    os << '[';
    for (auto &&i : std::ranges::subrange(begin, end - 1))
    {
        os << i << ",";
    }
    os << *(end - 1) << ']';

    return os;
}

int main()
{
    vector<int> u{3, 2, 6, 7, 4}, v(5), w;
    cout << "u = " << (u | views::all) << endl;

    std::ranges::copy(u, std::begin(v));
    cout << "v = " << (v | views::all) << endl;

    dmc::copy(u, w);
    cout << "w = " << (w | views::all) << endl;

    return 0;
}
