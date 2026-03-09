#include "Game.hpp"

static constexpr Vec2      kStartPos {Game::GridWidth / 2, Game::GridHeight / 2};
static constexpr Direction kStartDir  = Direction::Right;

Game::Game()
	: snake_( kStartPos, kStartDir )
	, pendingDir_( kStartDir )
{
	food_.randomize( GridWidth, GridHeight, snake_ );
}

void Game::update()
{
	if( state_ != GameState::Running )
		return;

	snake_.changeDirection( pendingDir_ );
	snake_.move();

	auto [hx, hy] = snake_.head();

	if( hx < 0 || hx >= GridWidth || hy < 0 || hy >= GridHeight ) {
		state_ = GameState::GameOver;
		return;
	}

	if( snake_.collidesWithSelf() ) {
		state_ = GameState::GameOver;
		return;
	}

	if( snake_.head() == food_.position() ) {
		snake_.grow();
		++score_;
		food_.randomize( GridWidth, GridHeight, snake_ );
	}
}

void Game::handleInput( Direction dir )
{
	pendingDir_ = dir;
}

void Game::restart()
{
	snake_.reset( kStartPos, kStartDir );
	pendingDir_ = kStartDir;
	food_.randomize( GridWidth, GridHeight, snake_ );
	state_ = GameState::Running;
	score_ = 0;
}
