#ifndef OPENWAY_MOUSE_HPP
#define OPENWAY_MOUSE_HPP

#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <utl/non_copyable.hpp>

#include "openway/io/input_state.hpp"

class Mouse {
public:
    explicit Mouse(
        GLFWwindow *window_handle,
        std::shared_ptr<InputState> input_state
    );
    ~Mouse();

    NON_COPYABLE(Mouse)

    glm::vec2 get_movement() const;
    glm::vec2 get_position() const;

private:
    std::shared_ptr<InputState> m_state_ptr;
};

#endif // OPENWAY_MOUSE_HPP
