#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void print_some_string(string_view sv)
{
    cout << sv << endl;
}

namespace std
{
    string operator+(string_view v1, string_view v2)
    {
        return string(v1) + string(v2);
    }
}

template <typename T>
T twice(T x) // statle memory in string_view
{
    return x + x;
}

template <typename T>
auto twice_with_auto(T x)
{
    return x + x;
}

int main()
{
    print_some_string("const char*");
    print_some_string("string"s);

    unsigned size = 100000;
    
    string      many_a(size, 'a');
    string_view many_a_view(many_a);

    string      still_many_a = many_a.substr(0, size / 2);
    string_view still_many_a_view = many_a_view.substr(0, size / 2);

    string_view h1 = twice_with_auto("Herbert"sv);
    cout << "h1 is " << h1 << ".\n";

    string_view h2 = twice("Herbert"sv);
    cout << "h2 is " << h2 << ".\n";

    constexpr string_view name = "Herbert"; 

    return 0;
}
