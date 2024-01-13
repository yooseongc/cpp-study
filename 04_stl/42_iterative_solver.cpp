#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/itl/itl.hpp>
// #include <mutex>
#include <shared_mutex>


class interruptible_iteration
{
    public:
        interruptible_iteration(itl::basic_iteration<double> &iter)
            : iter{iter}, interrupted{false}
        {}

        bool finished(double r)
        {
            // m.lock();
            // bool i = interrupted;
            // bool f = iter.finished(r);
            // m.unlock();
            // return f || i;

            // std::lock_guard<std::mutex> g{m};
            std::shared_lock<std::shared_mutex> g{m};
            return iter.finished(r) || interrupted; 
        }

        void interrupt()
        {
            // m.lock();
            // interrupted = true;
            // m.unlock();

            // std::lock_guard<std::mutex> g{m};
            std::shared_lock<std::shared_mutex> g{m};
            interrupted = true;
        }

        bool is_interrupted() const
        {
            // m.lock();
            // bool i = interrupted;
            // m.unlock();
            // return i;

            // std::lock_guard<std::mutex> g{m};
            std::shared_lock<std::shared_mutex> g{m};
            return interrupted;
        }

    private:
        itl::basic_iteration<double>    &iter;
        bool                            interrupted;
        mutable std::shared_mutex       m;
};
