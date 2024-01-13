#include <iostream>
#include <iomanip>

#if 0

CRTP(curiously recurring template pattern)

#endif

using namespace std;

template <typename T>
struct inequality
{
#if 0
    bool operator!=(const T& that) const { return !(static_cast<const T&>(*this) == that); }
#else
    bool operator!=(const T &that) const { return !(*static_cast<const T*>(this) == that); }
#endif
};

class point : public inequality<point>
{
public:
    point(int x, int y) : x(x), y(y) {}
    bool operator==(const point& that) const { return x == that.x && y == that.y; }
#if 0
    bool operator!=(const point& that) const { return x != that.x || y != that.y; }
    // bool operator!=(const point& that) const { return !(*this == that); }
#endif

private:
    int x, y;
};

int main(int argc, char* argv[])
{
    point p1(3, 4), p2(3, 5);
    cout << "p1 != p2 is "<< boolalpha << (p1 != p2) << endl;

    inequality<point> u1;
    cout << "u1 != p2 is " << boolalpha << (u1 != p2) << endl;

    return 0;
}
