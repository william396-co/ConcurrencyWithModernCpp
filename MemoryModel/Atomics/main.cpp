#include "spinlock.h"

#include <ios>
#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <utility>
#include <iomanip>

struct A
{
    int a;
    //    std::string b;
};

struct B
{
    int a[100];
    //std::string a;
};
struct C
{
    float f;
};

int main()
{
    println( std::boolalpha,
        "std::atomic<A> is lock free? ", // true
        std::atomic<A> {}.is_lock_free(),
        "\nstd::atomic<B> is lock free? ", // false
        std::atomic<B> {}.is_lock_free(),
        "\nstd::atomic<C> is lock free ? ", // true
        std::atomic<C> {}.is_lock_free(),
        "\nstd::atomic<bool> is lock free ? ", // true
        std::atomic<bool> {}.is_lock_free(),
        "\nstd::atomic<A> is always lock free ? ", // true
        std::atomic<A>::is_always_lock_free,
        "\nstd::atomic<B> is always lock free ? ", // false
        std::atomic<B>::is_always_lock_free,
        "\nstd::atomic<C> is always lock free ? ", // true
        std::atomic<C>::is_always_lock_free,
        "\nstd::atomic<int> is lock free? ", // true
        std::atomic_int {}.is_lock_free() );

    spinlock_test();

    return 0;
}
