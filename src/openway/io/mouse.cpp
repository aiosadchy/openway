#include "openway/io/mouse.hpp"

#include "openway/io/input_state.hpp"
#include "openway/io/window.hpp"
#include "openway/log.hpp"

namespace {

void cursor_position_callback(
    GLFWwindow *window,
    double x_pos,
    double y_pos
) {
    InputState *input_state = static_cast<InputState *>(
        glfwGetWindowUserPointer(window)
    );
    if (input_state == nullptr) {
        return;
    }
    input_state->mouse.current_position = {x_pos, y_pos};
}

} // namespace

Mouse::Mouse(Window &window)
: m_state_ptr{static_cast<InputState *>(glfwGetWindowUserPointer(window))} {
    if (!m_state_ptr) {
        OW_LOG_THROW std::invalid_argument{
            "unable to retrieve window input state",
        };
    }
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

Mouse::~Mouse() = default;

glm::vec2 Mouse::get_movement() const {
    const auto &curr_pos = m_state_ptr->mouse.current_position;
    const auto &prev_pos = m_state_ptr->mouse.previous_position;
    return {curr_pos.x - prev_pos.x, curr_pos.y - prev_pos.y};
}

glm::vec2 Mouse::get_position() const {
    const auto &pos = m_state_ptr->mouse.current_position;
    return {pos.x, pos.y};
}

void Mouse::next_input_frame() {
    m_state_ptr->mouse.previous_position = m_state_ptr->mouse.current_position;
}
