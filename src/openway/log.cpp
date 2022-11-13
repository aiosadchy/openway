#include "openway/log.hpp"

#include <algorithm>
#include <iostream>


namespace {

void default_callback(Log::Level level, const char *message, const char *file, int line) {
    if (file != nullptr) {
        std::cerr << "[" << file << ":" << std::max(line, 0) << "]";
    }
    std::cerr << " [" << Log::to_string(level) << "] " << message << std::endl;
}

const char *get_relative_source_file_path(const char *source_file_path) noexcept {
    if (source_file_path == nullptr) {
        return nullptr;
    }
    if (source_file_path[0] != '/') {
        return source_file_path;
    }
    return source_file_path + sizeof(OPENWAY_SOURCE_ROOT);
}

Log::Callback g_log_callback = default_callback;

Log::Level g_log_level = Log::Level::DEBUG;

} // namespace


const char *Log::to_string(Level level) noexcept {
    switch (level) {
        case Level::DEBUG:      return "DEBUG";
        case Level::INFO:       return "INFO";
        case Level::WARNING:    return "WARNING";
        case Level::ERROR:      return "ERROR";
        case Level::CRITICAL:   return "CRITICAL";
        case Level::NONE:       return "NONE";
        default:                return "UNKNOWN_LOG_LEVEL";
    }
}

Log::Callback Log::get_callback() noexcept {
    return g_log_callback;
}

void Log::set_callback(Callback callback) noexcept {
    if (callback == nullptr) {
        callback = default_callback;
    }
    g_log_callback = callback;
}


Log::Level Log::get_log_level() noexcept {
    return g_log_level;
}

void Log::set_log_level(Level level) noexcept {
    g_log_level = level;
}


void Log::message(Level level, const char *msg, const char *file, int line) noexcept {
    if (level < g_log_level || level == Level::NONE) {
        return;
    }
    try {
        g_log_callback(level, msg, get_relative_source_file_path(file), line);
    } catch (...) {
        // do nothing
    }
}

void Log::message(Level level, const std::string &msg, const char *file, int line) noexcept {
    message(level, msg.c_str(), file, line);
}

void Log::debug(const std::string &msg, const char *file, int line) noexcept {
    message(Level::DEBUG, msg, file, line);
}

void Log::info(const std::string &msg, const char *file, int line) noexcept {
    message(Level::INFO, msg, file, line);
}

void Log::warning(const std::string &msg, const char *file, int line) noexcept {
    message(Level::WARNING, msg, file, line);
}

void Log::error(const std::string &msg, const char *file, int line) noexcept {
    message(Level::ERROR, msg, file, line);
}

void Log::critical(const std::string &msg, const char *file, int line) noexcept {
    message(Level::CRITICAL, msg, file, line);
}
