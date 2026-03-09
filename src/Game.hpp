#pragma once
#include "Types.hpp"
#include "Snake.hpp"
#include "Food.hpp"

class Game {
public:
    static constexpr int GridWidth  = 20;
    static constexpr int GridHeight = 20;

    Game();

    // Called once per game tick
    void update();
    // Queue a direction change; ignored if it would reverse the snake
    void handleInput(Direction dir);
    // Reset to initial state
    void restart();

    GameState        state() const { return state_; }
    const Snake&     snake() const { return snake_; }
    const Food&      food()  const { return food_; }
    int              score() const { return score_; }

private:
    Snake     snake_;
    Food      food_;
    GameState state_       = GameState::Running;
    Direction pendingDir_;
    int       score_       = 0;
};
