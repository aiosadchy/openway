#include <algorithm>
#include <iostream>
#include <type_traits>

#include "openway/log.hpp"


namespace log {

namespace {

void default_callback(Level level, const char *message, const char *file, int line) {
    if (file != nullptr) {
        std::cerr << "[" << file << ":" << std::max(line, 0) << "]";
    }
    std::cerr << " [" << to_string(level) << "] " << message << std::endl;
}

const char *get_relative_source_file_path(const char *source_file_path) {
    if (source_file_path == nullptr) {
        return nullptr;
    }
    if (source_file_path[0] != '/') {
        return source_file_path;
    }
    return source_file_path + sizeof(OPENWAY_SOURCE_ROOT);
}

Callback g_log_callback = default_callback;

Level g_log_level = Level::DEBUG;

} // namespace


bool operator<(Level a, Level b) {
    using U = std::underlying_type_t<Level>;
    return static_cast<U>(a) < static_cast<U>(b);
}

const char *to_string(Level level) {
    switch (level) {
        case Level::DEBUG:      return "DEBUG";
        case Level::INFO:       return "INFO";
        case Level::WARNING:    return "WARNING";
        case Level::ERROR:      return "ERROR";
        case Level::CRITICAL:   return "CRITICAL";
        default:                return "UNKNOWN_LOG_LEVEL";
    }
}


void set_callback(Callback callback) {
    if (callback == nullptr) {
        callback = default_callback;
    }
    g_log_callback = callback;
}


Level get_log_level() {
    return g_log_level;
}

void set_log_level(Level level) {
    g_log_level = level;
}


void message(Level level, const char *msg, const char *file, int line) {
    if (level < g_log_level) {
        return;
    }
    g_log_callback(level, msg, get_relative_source_file_path(file), line);
}

void message(Level level, const std::string &msg, const char *file, int line) {
    message(level, msg.c_str(), file, line);
}

void debug(const std::string &msg, const char *file, int line) {
    message(Level::DEBUG, msg, file, line);
}

void info(const std::string &msg, const char *file, int line) {
    message(Level::INFO, msg, file, line);
}

void warning(const std::string &msg, const char *file, int line) {
    message(Level::WARNING, msg, file, line);
}

void error(const std::string &msg, const char *file, int line) {
    message(Level::ERROR, msg, file, line);
}

void critical(const std::string &msg, const char *file, int line) {
    message(Level::CRITICAL, msg, file, line);
}


ExceptionLogger::ExceptionLogger(const char *file, int line)
    : m_file{file}
    , m_line{line} {
}

} // namespace log
