#include "openway/io/keyboard.hpp"

#include <utility>

#include "openway/log.hpp"

namespace {

enum KeyState {
    WAS_PRESSED  = 0,
    WAS_RELEASED = 1,
    WAS_DOWN     = 2,
    IS_DOWN      = 3
};

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
    InputState *input_state = static_cast<InputState *>(
        glfwGetWindowUserPointer(window)
    );
    if (input_state == nullptr) {
        return;
    }
    if (action == GLFW_PRESS) {
        input_state->keyboard[key][WAS_PRESSED] = true;
        input_state->keyboard[key][IS_DOWN]     = true;
    }
    if (action == GLFW_RELEASE) {
        input_state->keyboard[key][WAS_RELEASED] = true;
        input_state->keyboard[key][IS_DOWN]      = false;
    }
}

} // namespace

Keyboard::Keyboard(
    GLFWwindow *window_handle,
    std::shared_ptr<InputState> input_state
)
    : m_state_ptr{std::move(input_state)} {
    if (!m_state_ptr) {
        OW_LOG_THROW std::invalid_argument{"empty window state"};
    }
    glfwSetKeyCallback(window_handle, key_callback);
}

Keyboard::~Keyboard() = default;

bool Keyboard::is_pressed(int glfw_key) const {
    return m_state_ptr->keyboard[glfw_key][WAS_PRESSED];
}

bool Keyboard::is_down(int glfw_key) const {
    return m_state_ptr->keyboard[glfw_key][IS_DOWN];
}

bool Keyboard::is_released(int glfw_key) const {
    return m_state_ptr->keyboard[glfw_key][WAS_RELEASED];
}

bool Keyboard::is_up(int glfw_key) const {
    return !is_down(glfw_key);
}

void Keyboard::next_input_frame() {
    for (auto &key_state : m_state_ptr->keyboard) {
        key_state[WAS_PRESSED]  = false;
        key_state[WAS_RELEASED] = false;
        key_state[WAS_DOWN]     = key_state[IS_DOWN];
    }
}
