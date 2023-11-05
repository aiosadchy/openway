#include "openway/utility/timer.hpp"

namespace {

double to_seconds(long long microseconds) {
    return static_cast<double>(microseconds) * 1e-6;
}

} // namespace

Timer::Timer()
    : m_start() {
    restart();
}

Timer::~Timer() = default;

double Timer::restart() {
    using namespace std::chrono;
    const auto now = high_resolution_clock::now();
    const auto before = m_start;
    m_start = now;
    const auto dur = now - before;
    const auto mcs = duration_cast<std::chrono::microseconds>(dur).count();
    return to_seconds(mcs);
}

double Timer::get_time() {
    using namespace std::chrono;
    const auto now = high_resolution_clock::now();
    const auto dur = now - m_start;
    const auto mcs = duration_cast<std::chrono::microseconds>(dur).count();
    return to_seconds(mcs);
}
