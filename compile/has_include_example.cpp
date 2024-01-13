#include <iostream>

#if __has_include(<any>)
    #include <any>
#endif

int main()
{
#if __has_include(<any>)
    std::cout << "any found, we do something useful." << std::endl;
#else
    std::cout << "any not found, we have to skip this example." << std::endl;
#endif

    return 0;
}