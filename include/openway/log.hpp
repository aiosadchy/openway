#ifndef OPENWAY_LOG_HPP
#define OPENWAY_LOG_HPP

#include "openway/utility/to_string.hpp"


// TODO: make this a class
namespace Log {

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

} // namespace Log


#define OW_LOG_DEBUG(...)    Log::debug    (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_INFO(...)     Log::info     (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_WARNING(...)  Log::warning  (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_ERROR(...)    Log::error    (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)
#define OW_LOG_CRITICAL(...) Log::critical (to_string(__VA_ARGS__).c_str(), __FILE__, __LINE__)

#endif // OPENWAY_LOG_HPP
