#ifndef OPENWAY_MOUSE_HPP
#define OPENWAY_MOUSE_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <utl/non_copyable.hpp>

class Window;
struct InputState;

class Mouse {
public:
    explicit Mouse(Window &window);
    ~Mouse();

    NON_COPYABLE(Mouse)

    glm::vec2 get_movement() const;
    glm::vec2 get_position() const;

    void next_input_frame();

private:
    InputState *m_state_ptr;
};

#endif // OPENWAY_MOUSE_HPP
