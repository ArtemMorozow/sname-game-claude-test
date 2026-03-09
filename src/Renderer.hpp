#pragma once
#include <SDL2/SDL.h>
#include "Game.hpp"

class Renderer {
public:
    static constexpr int CellSize    = 30;
    static constexpr int WindowWidth  = Game::GridWidth  * CellSize;
    static constexpr int WindowHeight = Game::GridHeight * CellSize;

    Renderer();
    ~Renderer();

    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;

    void render(const Game& game);

    // Returns the screen rect of the "Play Again" button (for hit-testing in main)
    static SDL_Rect restartButtonRect();

private:
    void fillCell(int x, int y, SDL_Color color);
    void drawGameOver();
    void updateTitle(const Game& game);

    SDL_Window*   window_   = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};
