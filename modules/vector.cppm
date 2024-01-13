export module vector;

export namespace dmc
{
    template <typename Value>
    class vector;
}

#if defined(__GXX_WEAK__)
#include <bits/gthr-default.h>
#endif

#include <iostream>
#include <memory>
#include <algorithm>
#include <initializer_list>

// import std.iostream;
// import std.memory;
// import std.algorithm;
// import std.initializer_list;


namespace dmc
{

    struct range_error {};
    struct incompatible {};

    template <typename Value>
    class vector
    {
        void check_index(int i) const
        {
            if (i < 0 || i >= my_size)
                throw range_error{};
        }
        void copy(const vector &that) { std::copy(&that.data[0], &that.data[that.my_size], &data[0]); }

    public:
        vector() : my_size{0}, data{} {}

        explicit vector(int size) : my_size{size}, data{new Value[my_size]} {}

        vector(std::initializer_list<Value> values) : vector(values.size())
        {
            *this = values;
            // std::cout << "initializer_list constructor called.\n";
        }

        vector(const vector &that) : vector(that.size())
        {
            copy(that);
        }

        vector(vector &&that) : my_size{that.my_size}, data{std::move(that.data)}
        {
            that.my_size = 0;
        }

        vector &operator=(const vector &that) &
        {
            check_size(that.my_size);
            copy(that);
            return *this;
        }

        vector &operator=(vector &&that) &
        {
            check_size(that.size());
            data = std::move(that.data);
            that.my_size = 0;
            return *this;
        }

        vector &operator=(std::initializer_list<Value> values) &
        {
            check_size(values.size());
            std::copy(begin(values), end(values), &data[0]);
            return *this;
        }

        void check_size(int that_size) const
        {
            if (my_size != that_size)
                throw incompatible{};
        }
        int size() const { return my_size; }

        const Value &operator[](int i) const &
        {
            check_index(i);
            return data[i];
        }
        Value &operator[](int i) &
        {
            check_index(i);
            return data[i];
        }
        Value operator[](int i) &&
        {
            check_index(i);
            return data[i];
        }

    private:
        int my_size;
        std::unique_ptr<Value[]> data;
    };
}
