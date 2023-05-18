#pragma once
#include "../../util/print.h"

#include <atomic>
#include <thread>

class Spinlock
{
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
        while ( flag.test_and_set() )
            ;
    }
    void unlock()
    {
        flag.clear();
    }
};

Spinlock spin;
inline void workOnResource( int id )
{
    spin.lock();

    println( "threadid = ", std::this_thread::get_id(), " id = ", id );
    // shared resources
    spin.unlock();
}

inline void spinlock_test()
{
    println( __PRETTY_FUNCTION__ );

    for ( int i = 0; i < 10; ++i ) {
        std::thread t1( workOnResource, 1 );
        std::thread t2( workOnResource, 2 );

        t1.join();
        t2.join();
    }
}
