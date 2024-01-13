#include <optional>
#include <vector>
#include <iostream>
#include <cmath>

template <typename T>
std::optional<T> square_root(const T& x)
{
    if(x < 0.0)
    {
        return std::nullopt;
    }
    else
    {
        return std::sqrt(x);
    }
}

int main(int argc, char** argv)
{
    std::vector<double> v = { 4.0, -4.0, -0.09, 0.25 };
    
    for(const auto& d : v)
    {
        if(auto s = square_root(d); s)
        {
            std::cout << "Square root of " << d << " is " << *s << std::endl;
        }
        else
        {
            std::cout << d << " has no square root." << std::endl;
        }
    }

    return 0;
}
