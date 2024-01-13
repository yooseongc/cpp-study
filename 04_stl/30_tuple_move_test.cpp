#include <iostream>
#include <tuple>
#include <functional>
#include <typeinfo>

using namespace std;

struct dings
{
    dings() : i{}, p{} {}
    dings(int i) : i(i), p(new int) {}
    dings(const dings& that) : i(that.i), p(new int)
    {
        cout << "Copy Constructor" << endl;
    }
    dings(dings&& that) : i(that.i), p(that.p)
    {
        that.p = nullptr;
        cout << "Move Constructor" << endl;
    }

    ~dings() { delete p; }

    dings& operator=(const dings& that)
    {
        i = that.i;
        return *this;
    }

    dings& operator=(dings&& that)
    {
        p = that.p;
        that.p = nullptr;
        i = that.i;
        return *this;
    }

    int i;
    int* p;
};

tuple<dings, dings> f(bool c)
{
    dings d(3), e(1);
    if(c)
    {
        d.i = 2;
    }

    cout << "d.p = " << d.p << endl;
    cout << "e.p = " << e.p << endl;

    return make_tuple(move(d), move(e));
}

struct matrix
{
    matrix() = default;
    matrix(const matrix&) { cout << "Copy Constructor" << endl; }
    matrix(matrix&&)      { cout << "Move Constroctor" << endl; }
    matrix& operator=(const matrix&) { cout << "Copy Assignment" << endl; return *this; }
    matrix& operator=(matrix&&)      { cout << "Move Assignment" << endl; return *this; }
};

struct vector {};

tuple<matrix, ::vector> lu(const matrix& A)
{
    matrix LU;
    ::vector p;
    // calculate ...
    return make_tuple(move(LU), move(p));
}

int main()
{
    auto td = f(true);
    auto d = move(get<0>(td));
    auto e = move(get<1>(td));

    cout << "d.i = " << d.i << endl;
    cout << "e.i = " << e.i << endl;
    cout << "d.p = " << d.p << endl;
    cout << "e.p = " << e.p << endl;

    matrix A;
    matrix LU;
    ::vector p;
    cout << "Los." << endl;
    tie(LU, p) = lu(A);

    return 0;
}
