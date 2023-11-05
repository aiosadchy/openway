#ifndef OPENWAY_SRC_OPENWAY_GRAPHICS_DRAWABLE_HPP
#define OPENWAY_SRC_OPENWAY_GRAPHICS_DRAWABLE_HPP

class Drawable {
public:
    Drawable() = default;
    virtual ~Drawable() = default;

    virtual void draw() const = 0;
};

#endif // OPENWAY_SRC_OPENWAY_GRAPHICS_DRAWABLE_HPP
