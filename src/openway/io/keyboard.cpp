#include "openway/io/keyboard.hpp"

#include <array>
#include <unordered_map>


namespace {

enum KeyState {
    WAS_PRESSED = 0,
    WAS_RELEASED = 1,
    WAS_DOWN = 2,
    IS_DOWN = 3
};

using KeyboardState = std::array<std::array<bool, 4>, GLFW_KEY_LAST + 1>;

// TODO: a faster solution
std::unordered_map<GLFWwindow *, KeyboardState> s_keyboard_state = {};

void key_callback(
        GLFWwindow *window,
        int key,
        [[maybe_unused]] int scancode,
        int action,
        [[maybe_unused]] int mods
) {
    if (key == GLFW_KEY_UNKNOWN) {
        return;
    }
    KeyboardState &keyboard = s_keyboard_state[window];
    if (action == GLFW_PRESS) {
        keyboard[key][WAS_PRESSED] = true;
        keyboard[key][IS_DOWN] = true;
    }
    if (action == GLFW_RELEASE) {
        keyboard[key][WAS_RELEASED] = true;
        keyboard[key][IS_DOWN] = false;
    }
}

} // namespace


Keyboard::Keyboard(Window &window)
    : m_window_handle(window) {
    s_keyboard_state.try_emplace(m_window_handle);
}

Keyboard::~Keyboard() = default;

bool Keyboard::is_pressed(int key) const {
    return s_keyboard_state[m_window_handle][key][WAS_PRESSED];
}

bool Keyboard::is_down(int key) const {
    return s_keyboard_state[m_window_handle][key][IS_DOWN];
}

bool Keyboard::is_released(int key) const {
    return s_keyboard_state[m_window_handle][key][WAS_RELEASED];
}

bool Keyboard::is_up(int key) const {
    return !is_down(key);
}

void Keyboard::tick() {
    for (auto &key_state : s_keyboard_state[m_window_handle]) {
        key_state[WAS_PRESSED] = false;
        key_state[WAS_RELEASED] = false;
        key_state[WAS_DOWN] = key_state[IS_DOWN];
    }
}

void Keyboard::initialize_keyboard(Window &window) {
    glfwSetKeyCallback(window, key_callback);
}
