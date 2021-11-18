#include <iostream>

#include <utl/utl.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
    UTL_REPEAT(1) {
        std::cout << "Everything seems to be working..." << std::endl;
    }
    return 0;
}
