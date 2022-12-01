#include "openway/io/mouse.hpp"

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

Mouse::Mouse(
    GLFWwindow *window_handle,
    std::shared_ptr<InputState> input_state
)
    : m_state_ptr{std::move(input_state)} {
    if (!m_state_ptr) {
        OW_LOG_THROW std::invalid_argument{"empty window state"};
    }
    glfwSetCursorPosCallback(window_handle, cursor_position_callback);
}

Mouse::~Mouse() = default;

glm::vec2 Mouse::get_movement() const {
    // TODO: consistent result between ticks
    return {};
}

glm::vec2 Mouse::get_position() const {
    const InputState::Mouse::Position pos = m_state_ptr->mouse.current_position;
    return {pos.x, pos.y};
}
