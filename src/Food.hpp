#pragma once
#include "Types.hpp"
#include <random>

class Snake;

class Food {
public:
	Food();

	// Place food on a random cell not occupied by the snake
	void randomize( int gridW, int gridH, Snake const& snake );

	Vec2 position() const { return pos_; }

private:
	Vec2         pos_{};
	std::mt19937 rng_;
};
