#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string_view>
#include <string>
#include <typeinfo>
#include <ranges>

using namespace std;

template <typename OStreamT>
auto &operator<<(OStreamT &os, const std::ranges::range auto &range)
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
    
    using namespace std::ranges;
    
    auto in_range = [](int i){ return i > 4 && i < 7; };
    auto square = [](int n){ return n * n; };
    vector<int> seq = { 3, 4, 7, 6, 9, 2, 5, 7, 8 };

    for (int i : views::filter(seq, in_range))
    {
        cout << i << " is in range.\n";
    }
    cout << endl;

    for (int i : views::transform(views::filter(seq, in_range), square))
    {
        cout << i << " is the squared value of an in-range entry.\n";
    }
    cout << endl;

    for (int i : seq | views::filter(in_range) | views::transform(square))
    {
        cout << i << " is the squared value of an in-range entry.\n";
    }
    cout << endl;

    cout << "seq = " << views::all(seq) << endl << endl;

    vector<string> ss{"Discovering ", "Modern ", "C++"};
    cout << "joined:    ";
    for (char const c : ss | views::join)
    {
        cout << c;
    }
    cout << endl << endl;

    vector<int> seq2 = {3, 4, 7, 9, 2, 5, 7, 8, 3, 4, 3, 9};
    cout << "seq2:          " << (seq2 | views::all) << endl;
    cout << "sorted:        " << (ranges::sort(seq2), seq2 | views::all) << endl;
    cout << "unique:        " << (ranges::unique(seq2) | views::all ) << endl;

    return 0;
}
