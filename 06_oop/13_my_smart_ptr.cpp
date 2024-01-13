#include <memory>
#include <cassert>
#include <iostream>

namespace yooseongc
{
    template <typename T>
    class unique_ptr
    {
    public:
        explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}
        ~unique_ptr() { delete ptr_; }
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;
        unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }
        unique_ptr& operator=(unique_ptr&& other) noexcept 
        {
            if(this != &other)
            {
                delete ptr_;
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        }

        T* get() const noexcept { return ptr_; }
        T* release() noexcept
        {
            T* temp = ptr_;
            ptr_ = nullptr;
            return temp;
        }

        void reset(T* ptr = nullptr) noexcept
        {
            delete ptr_;
            ptr_ = ptr;
        }

        T& operator*() const noexcept { return *ptr_; }
        T* operator->() const noexcept { return ptr_; }

        explicit operator bool() const noexcept { return ptr_ != nullptr; }

    private: 
        T* ptr_;
    };

    template <typename T>
    class shared_ptr
    {
    public:
        shared_ptr() : ptr(nullptr), ref_count(new std::size_t(0)) {}
        shared_ptr(T* ptr) : ptr(ptr), ref_count(new std::size_t(1)) {}
        shared_ptr(const shared_ptr& obj)
        {
            this->ptr = obj.ptr;
            this->ref_count = obj.ref_count;
            if(nullptr != obj.ptr)
            {
                (*this->ref_count)++;
            }
        }

        shared_ptr& operator=(const shared_ptr& obj)
        {
            __cleanup__();
            this->ptr = obj.ptr;
            this->ref_count = obj.ref_count;
            if(nullptr != obj.ptr)
            {
                (*this->ref_count)++;
            }
        }

        shared_ptr(shared_ptr&& obj)
        {
            this->ptr = obj.ptr;
            this->ref_count = obj.ref_count;
            obj.ptr = obj.ref_count = nullptr;
        }

        std::size_t get_count() const { return *ref_count; }
        T* get() const { return this->ptr; }
        T* operator->() const { return this->ptr; }
        T& operator*() const { return this->ptr; }

        ~shared_ptr() { __cleanup__(); }
        
    private:
        void __cleanup__()
        {
            (*ref_count)--;
            if(*ref_count == 0)
            {
                if(nullptr != ptr)
                {
                    delete ptr;
                }
                delete ref_count;
            }
        }

        T* ptr = nullptr;
        std::size_t* ref_count = nullptr;
    };
}

class Box
{
public:
    int length, width, height;
    Box(): length(0), width(0), height(0) {}
};

int main()
{
    yooseongc::unique_ptr<int> ptr(new int(42));

    *ptr = 99;
    int* raw_ptr = ptr.release();

    assert(!ptr);
    assert(*raw_ptr == 99);

    yooseongc::shared_ptr<Box> obj;
    std::cout << obj.get_count() << std::endl;
    assert(obj.get_count() == 0);

    yooseongc::shared_ptr<Box> box1(new Box());
    std::cout << box1.get_count() << std::endl;
    assert(box1.get_count() == 1);

    yooseongc::shared_ptr<Box> box2(box1);
    std::cout << box1.get_count() << std::endl;
    std::cout << box2.get_count() << std::endl;

    assert(box1.get_count() == 2);
    assert(box2.get_count() == 2);

    return 0;
}
