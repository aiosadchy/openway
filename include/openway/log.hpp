#ifndef OPENWAY_LOG_HPP
#define OPENWAY_LOG_HPP

#include "openway/utility/to_string.hpp"


namespace log {

enum class Level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

using Callback = void (*)(Level level, const char *msg, const char *file, int line);

bool operator<(Level a, Level b);
const char *to_string(Level level);

void set_callback(Callback callback);

Level get_log_level();
void set_log_level(Level level);

void message(Level level, const char *msg, const char *file, int line);
void debug(const char *msg, const char *file, int line);
void info(const char *msg, const char *file, int line);
void warning(const char *msg, const char *file, int line);
void error(const char *msg, const char *file, int line);
void critical(const char *msg, const char *file, int line);

} // namespace log


#define OW_LOG_DEBUG(...)    log::debug    (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_INFO(...)     log::info     (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_WARNING(...)  log::warning  (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_ERROR(...)    log::error    (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_CRITICAL(...) log::critical (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)

#endif // OPENWAY_LOG_HPP
