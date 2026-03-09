#pragma once
#include <SDL2/SDL.h>
#include "Game.hpp"

class Renderer {
public:
	static constexpr int CellSize     = 30;
	static constexpr int WindowWidth  = Game::GridWidth  * CellSize;
	static constexpr int WindowHeight = Game::GridHeight * CellSize;

	Renderer();
	~Renderer();

	Renderer( Renderer const& )            = delete;
	Renderer& operator=( Renderer const& ) = delete;

	void render( Game const& game );

	// Returns the screen rect of the "Play Again" button (for hit-testing in main)
	static SDL_Rect restartButtonRect();

private:
	void fillCell( int x, int y, SDL_Color color );
	void drawGameOver();
	void updateTitle( Game const& game );

	SDL_Window*   window_   = nullptr;
	SDL_Renderer* renderer_ = nullptr;
};
