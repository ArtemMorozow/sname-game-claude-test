#pragma once
#include "Types.hpp"
#include <deque>

class Snake {
public:
    Snake(Vec2 startPos, Direction startDir);

    // Advance head by one cell; if growing, keep tail in place
    void move();
    // Flag the snake to not discard its tail on the next move
    void grow();
    // Change direction unless it would reverse the snake into itself
    void changeDirection(Direction newDir);

    bool occupies(Vec2 pt) const;
    bool collidesWithSelf() const;

    Vec2                     head()      const { return body_.front(); }
    const std::deque<Vec2>&  body()      const { return body_; }
    Direction                direction() const { return dir_; }

    void reset(Vec2 startPos, Direction startDir);

private:
    std::deque<Vec2> body_;
    Direction        dir_;
    bool             growing_ = false;
};
