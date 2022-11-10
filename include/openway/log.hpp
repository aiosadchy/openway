#ifndef OPENWAY_LOG_HPP
#define OPENWAY_LOG_HPP

#include <string>

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
const char *as_string(Level level);

void set_callback(Callback callback);

Level get_log_level();
void set_log_level(Level level);

void message(Level level, const char *msg,        const char *file, int line);
void message(Level level, const std::string &msg, const char *file, int line);
void debug   (const std::string &msg, const char *file, int line);
void info    (const std::string &msg, const char *file, int line);
void warning (const std::string &msg, const char *file, int line);
void error   (const std::string &msg, const char *file, int line);
void critical(const std::string &msg, const char *file, int line);

class ExceptionLogger {
public:
    ExceptionLogger(const char *file, int line);

    template <typename E>
    [[noreturn]] void operator<<(E &&exception) const {
        error(to_string("[exception] ", exception.what()), m_file.c_str(), m_line);
        throw exception;
    }

private:
    std::string m_file;
    int m_line;

};

} // namespace Log


#define OW_LOG_DEBUG(...)    Log::debug    (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_INFO(...)     Log::info     (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_WARNING(...)  Log::warning  (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_ERROR(...)    Log::error    (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_CRITICAL(...) Log::critical (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_THROW Log::ExceptionLogger{__FILE__, __LINE__} <<

#endif // OPENWAY_LOG_HPP
