#include <iostream>
#include <typeinfo> 
#include <string>
#include <vector>
#include <memory>

#include "./my_info.hpp"

using namespace std;

template <typename T>
string l_or_r(const T&)
{
    // const l-value reference parameter
    return "const";
}

template <typename T>
string l_or_r(T&)
{
    // l-value reference parameter
    return "mutable";
}

// macro for testing
#define info(TPara, p)                                                                 \
    cout                                                                               \
        << "Type of TPara is " << typeid(TPara).name()                                 \
        << " == " << my_info<TPara>()                                                  \
        << ", is" << (is_lvalue_reference<TPara>::value ? "" : " no") << " lref"       \
        << ", is" << (is_rvalue_reference<TPara>::value ? "" : " no") << " rref"       \
        << ", is" << (is_const<TPara>::value ? "" : " not") << " const\n"              \
        << "Type of p is " << typeid(p).name()                                         \
        << " == " << my_info<decltype(p)>()                                            \
        << ", is" << (is_lvalue_reference<decltype(p)>::value ? "" : " no") << " lref" \
        << ", is" << (is_rvalue_reference<decltype(p)>::value ? "" : " no") << " rref" \
        << ", is " << l_or_r(p) \
        << "\n=======================\n\n";

struct rubbish {};

struct dummy
{
    dummy& operator=(int i)
    {
        j = i;
        return *this;
    }
    int j = 8;
};

template <typename TPara>
void f1(TPara p)
{
    info(TPara, p);
}

template <typename TPara>
void f2(const TPara& p)
{
    info(TPara, p);
}

template <typename TPara>
void f3(TPara& p)
{
    info(TPara, p);
}

template <typename TPara>
void f4(TPara&& p)
{
    info(TPara, p);
}

template <typename TPara>
void f5(TPara&& p)
{
    f4(forward<TPara>(p));
}

int main()
{
    cout << "\n\n";

    int        i = 0;
    int&       j = i;
    const int& k = i;

    /// TPara
    f1(3);
    f1(i);
    f1(j);
    f1(k);

    unique_ptr<int> up;
    // f1(up);    // Error: no copy ctor
    f1(move(up)); // OK: move ctor

    /// const TPara&
    f2(3);
    f2(i);
    f2(j);
    f2(k);
    f2(up);

    /// TPara&
    // f3(3);
    f3<const int>(3);
    f3<const int&>(3);
    f3<const int&&>(3);
    f3(i);
    f3(j);
    f3(k);
    f3(up);

    /// TPara&&
    f4(3);
    f4(i);
    f4(move(i));
    f4(j);
    f4(k);
    f4(move(up));

    /// TPara&& with forward
    f5(3);
    f5(i);
    f5(move(i));
    f5(j);
    f5(k);
    f5(move(up));

    f4(dummy{});

    using int_ref = int&;
    cout << "The type of int& && is " << my_info<int_ref&&>() << endl;

    return 0;
}

#if 0

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIiE, is no lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIiE, is no lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIiE, is no lref, is no rref, i smutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIiE, is no lref, is no rref, is mutable
=======================

Type of TPara is St10unique_ptrIiSt14default_deleteIiEE == 4wrapISt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is no rref, is not const
Type of p is St10unique_ptrIiSt14default_deleteIiEE == 4wrapISt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is St10unique_ptrIiSt14default_deleteIiEE == 4wrapISt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is no rref, is not const
Type of p is St10unique_ptrIiSt14default_deleteIiEE == 4wrapIRKSt10unique_ptrIiSt14default_deleteIiEEE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIKiE, is no lref, is no rref, is const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIRKiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIOKiE, is no lref, is rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIRiE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIRiE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIKiE, is no lref, is no rref, is const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is St10unique_ptrIiSt14default_deleteIiEE == 4wrapISt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is no rref, is not const
Type of p is St10unique_ptrIiSt14default_deleteIiEE == 4wrapIRSt10unique_ptrIiSt14default_deleteIiEEE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIOiE, is no lref, is rref, is mutable
=======================

Type of TPara is i == 4wrapIRiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRiE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIOiE, is no lref, is rref, is mutable
=======================

Type of TPara is i == 4wrapIRiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRiE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIRKiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is St10unique_ptrIiSt14default_deleteIiEE == 4wrapISt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is no rref, is not const
Type of p is St10unique_ptrIiSt14default_deleteIiEE == 4wrapIOSt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is rref, ismutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIOiE, is no lref, is rref, is mutable
=======================

Type of TPara is i == 4wrapIRiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRiE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIiE, is no lref, is no rref, is not const
Type of p is i == 4wrapIOiE, is no lref, is rref, is mutable
=======================

Type of TPara is i == 4wrapIRiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRiE, is lref, is no rref, is mutable
=======================

Type of TPara is i == 4wrapIRKiE, is lref, is no rref, is not const
Type of p is i == 4wrapIRKiE, is lref, is no rref, is const
=======================

Type of TPara is St10unique_ptrIiSt14default_deleteIiEE == 4wrapISt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is no rref, is not const
Type of p is St10unique_ptrIiSt14default_deleteIiEE == 4wrapIOSt10unique_ptrIiSt14default_deleteIiEEE, is no lref, is rref, is mutable
=======================

Type of TPara is 5dummy == 4wrapI5dummyE, is no lref, is no rref, is not const
Type of p is 5dummy == 4wrapIO5dummyE, is no lref, is rref, is mutable
=======================

The type of int& && is 4wrapIRiE

#endif