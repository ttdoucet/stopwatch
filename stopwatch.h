/* Written by Todd Doucet.  See file copyright.txt.
 */
#pragma once

#include <chrono>
#include <iostream>
#include <cstdint>

namespace detail_stopwatch {

using namespace std::chrono;

class stopwatch
{
public:
    void start()
    {
        started = high_resolution_clock::now();
    }

    void stop()
    {
        time_point stopped = std::chrono::high_resolution_clock::now();
        accum += (stopped - started).count();
    }

    void reset()
    {
        accum = 0;
    }

    int64_t elapsed_ns()
    {
        static_assert( std::ratio_equal<std::nano,
                                        std::chrono::high_resolution_clock::period>()
                     );
        return accum;
    }

    double elapsed_usec()
    {
        return elapsed_ns() / 1.0e3;
    }

    double elapsed_msec()
    {
        return elapsed_ns() / 1.0e6;
    }

    double elapsed_sec()
    {
        return elapsed_ns() / 1.0e9;
    }

private:
    time_point<high_resolution_clock> started;
    int64_t accum = 0;
};

} // namespace detail_stopwatch

using detail_stopwatch::stopwatch;
