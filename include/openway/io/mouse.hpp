#ifndef OPENWAY_MOUSE_HPP
#define OPENWAY_MOUSE_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "openway/io/window.hpp"


class Mouse {
public:
    explicit Mouse(Window &window);
    ~Mouse();

    glm::vec2 get_movement() const;
    glm::vec2 get_position() const;

    void tick();

private:
    GLFWwindow *m_window_handle;
    glm::vec2 m_last_frame_position;
    glm::vec2 m_last_frame_movement;

};

#endif // OPENWAY_MOUSE_HPP
