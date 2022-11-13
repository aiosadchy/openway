#ifndef OPENWAY_LOG_HPP
#define OPENWAY_LOG_HPP

#include <exception>
#include <string>
#include <type_traits>

#include "openway/utility/to_string.hpp"


class Log {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL,
        NONE,
    };

    using Callback = void (*)(Level level, const char *msg, const char *file, int line);

public:
    static const char *to_string(Level level) noexcept;

    static Callback get_callback() noexcept;
    static void set_callback(Callback callback) noexcept;

    static Level get_log_level() noexcept;
    static void set_log_level(Level level) noexcept;

    static void message(Level level, const char *msg,        const char *file, int line) noexcept;
    static void message(Level level, const std::string &msg, const char *file, int line) noexcept;
    static void debug   (const std::string &msg, const char *file, int line) noexcept;
    static void info    (const std::string &msg, const char *file, int line) noexcept;
    static void warning (const std::string &msg, const char *file, int line) noexcept;
    static void error   (const std::string &msg, const char *file, int line) noexcept;
    static void critical(const std::string &msg, const char *file, int line) noexcept;

    inline static auto exception_logger(const char *file, int line) noexcept {
        return ExceptionLogger{file, line};
    }

    Log() = delete;
    ~Log() = delete;

private:
    class ExceptionLogger {
    public:
        inline ExceptionLogger(const char *file, int line) noexcept
            : m_file{file}
            , m_line{line} {
        }

        template <typename E>
        [[noreturn]] inline void operator<<(E &&exception) const {
            error(::to_string("[exception] ", exception.what()), m_file, m_line);
            std::exception_ptr current_exception = std::current_exception();
            if (current_exception) {
                std::throw_with_nested(std::forward<E>(exception));
            }
            throw exception;
        }

    private:
        const char *m_file;
        int m_line;

    };

};


inline bool operator<(Log::Level a, Log::Level b) noexcept {
    using U = std::underlying_type_t<Log::Level>;
    return static_cast<U>(a) < static_cast<U>(b);
}


#define OW_LOG_DEBUG(...)    Log::debug    (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_INFO(...)     Log::info     (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_WARNING(...)  Log::warning  (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_ERROR(...)    Log::error    (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_CRITICAL(...) Log::critical (to_string(__VA_ARGS__), __FILE__, __LINE__)
#define OW_LOG_THROW Log::exception_logger(__FILE__, __LINE__) <<

#endif // OPENWAY_LOG_HPP
