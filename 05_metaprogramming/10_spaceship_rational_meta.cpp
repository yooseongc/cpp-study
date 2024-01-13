#include <iostream>
#include <numeric>

class value
{
    public:
        explicit value(double x) : x{x}
        {}

        friend std::ostream& operator<<(std::ostream& os, value v)
        {
            return os << v.x;
        }

        auto operator<=>(const value& v2) const = default;
    
    private:
        double x;
};

class partial
{
    public:
        partial(int x, int y) : x{x}, y{y}
        {}

        bool operator==(const partial&) const = default;

        std::partial_ordering operator<=>(const partial& p2) const
        {
            using po = std::partial_ordering;
            
            if(x < p2.x && y < p2.y)
            {
                return po::less;
            }

            if(x > p2.x && y > p2.y)
            {
                return po::greater;
            }

            if(x == p2.x && y == p2.y)
            {
                return po::equivalent;
            }

            return po::unordered;
        }

    private:
        int x;
        int y;
};

struct zero_denominator {};

template <bool Canonical = false>
class rational
{
    using ordering = std::conditional_t<Canonical, std::strong_ordering, std::weak_ordering>;

    public:
        rational(int p, unsigned q) : p{p}, q{q}
        {
            if(q == 0)
            {
                throw zero_denominator{};
            }
            reduce();
        }

        bool operator==(const rational& r2) const = default;
        // bool operator==(const rational& r2) const
        // {
        //     std::cout << "denom = " << p * ll(r2.q) << ", nom = " << r2.p * ll(q) << std::endl;
        //     return p * ll(r2.q) == r2.p * ll(q);
        // }

        ordering operator<=>(const rational& r2) const
        {
            // using wo = std::weak_ordering;
            // int cmp = p * ll(r2.q) - r2.p * ll(q);
            // if(cmp == 0)
            // {
            //     return wo::equivalent;
            // }
            // else if(cmp < 0)
            // {
            //     return wo::less;
            // }
            // else
            // {
            //     return wo::greater;
            // }
            return p * ll(r2.q) <=> r2.p * ll(q);
        }

    private:
        int      p;
        unsigned q;

        static_assert(sizeof(long long) > sizeof(unsigned), "Correct comparison not guaranteed.");
        static long long ll(unsigned x)
        {
            return static_cast<long long>(x);
        }

        void reduce() & 
        {
            if constexpr(Canonical)
            {
                auto g = std::gcd(std::abs(p), q);
                p /= g;
                q /= g;
                std::cout << "p -> " << p << ", p -> " << q << ", g -> " << g << std::endl;
            }
        }
};


int main()
{
    using namespace std;

    value x{3}, y{5};

    cout << "x < y: " << boolalpha << (x < y) << endl;
    cout << "x > y: " << boolalpha << (x > y) << endl;
    cout << "x >= y: " << boolalpha << (x >= y) << endl;
    cout << "x <= y: " << boolalpha << (x <= y) << endl;
    cout << "x == y: " << boolalpha << (x == y) << endl;
    cout << "x != y: " << boolalpha << (x != y) << endl;

    rational half{1, 2}, third{1, 3}, half2{2, 4};
    cout << "half == third: " << boolalpha << (half == third) << endl;
    cout << "half != third: " << boolalpha << (half != third) << endl;
    cout << "half > third: " << boolalpha << (half > third) << endl;
    cout << "half < third: " << boolalpha << (half < third) << endl;
    cout << "half >= third: " << boolalpha << (half <= third) << endl;
    cout << "half <= third: " << boolalpha << (half >= third) << endl;
    cout << "half == half2: " << boolalpha << (half == half2) << endl;

    rational<true> half_c{1, 2}, half2_c{2, 4};
    cout << "half_c == half2_c: " << boolalpha << (half_c == half2_c) << endl;
    return 0;
}
