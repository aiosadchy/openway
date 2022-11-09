#include "openway/io/mouse.hpp"

#include <unordered_map>


namespace {

// TODO: a faster solution
std::unordered_map<GLFWwindow *, glm::vec2> mouse_state = {};

void cursor_position_callback(
        GLFWwindow *window,
        double x_pos,
        double y_pos
) {
    mouse_state[window] = glm::vec2{x_pos, y_pos};
}

} // namespace

Mouse::Mouse(Window &window)
    : m_window_handle(window)
    , m_last_frame_position(0, 0)
    , m_last_frame_movement(0, 0) {
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

Mouse::~Mouse() = default;

glm::vec2 Mouse::get_movement() const {
    // TODO: consistent result between ticks
    return mouse_state[m_window_handle] - m_last_position;
}

glm::vec2 Mouse::get_position() const {
    return m_last_frame_position;
}

void Mouse::tick() {
    glm::vec2 current_position =
    m_last_frame_movement =
    m_last_frame_position = mouse_state[m_window_handle];
}
