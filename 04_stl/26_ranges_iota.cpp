#include <iostream>
#include <vector>
#if __has_include(<ranges>)
    #include <ranges>
    #define WITH_RANGES
#endif

int main()
{
    using namespace std;
    using namespace std::ranges;

#ifdef WITH_RANGES
    vector<int> v{3, 9, 2, 8, 4};

    for(int i : iota_view{1, 10})
    {
        cout << i << endl;
    }
#else
    cout << "no ranges yet :-(\n";
#endif
    return 0;
}
