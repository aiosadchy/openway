#ifndef OPENWAY_TIMER_HPP
#define OPENWAY_TIMER_HPP

#include <chrono>


class Timer {
public:
    Timer();
    ~Timer();

    double restart();
    double get_time();

private:
    std::chrono::high_resolution_clock::time_point m_start;

};

#endif // OPENWAY_TIMER_HPP
