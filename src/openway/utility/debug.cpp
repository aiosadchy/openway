#include "openway/utility/debug.hpp"

#include "openway/utility/log.hpp"


namespace {

void unwrap_exception(const std::exception &exception, std::vector<std::string> &output) {
    try {
        output.emplace_back(exception.what());
        std::rethrow_if_nested(exception);
    } catch (const std::exception& nested_exception) {
        unwrap_exception(nested_exception, output);
    }
}

} // namespace


std::vector<std::string> unwrap_exception(const std::exception &exception) noexcept {
    try {
        std::vector<std::string> result{};
        unwrap_exception(exception, result);
        return result;
    } catch (...) {
        OW_LOG_WARNING("an unexpected exception caught while unwrapping another exception");
    }
    return {};
}
