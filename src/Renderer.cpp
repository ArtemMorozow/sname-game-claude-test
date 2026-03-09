#include "Renderer.hpp"
#include <format>
#include <stdexcept>

Renderer::Renderer()
{
	window_ = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WindowWidth, WindowHeight,
		SDL_WINDOW_SHOWN
	);
	if( !window_ )
		throw std::runtime_error( std::format( "SDL_CreateWindow: {}", SDL_GetError() ) );

	renderer_ = SDL_CreateRenderer( window_, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( !renderer_ ) {
		SDL_DestroyWindow( window_ );
		throw std::runtime_error( std::format( "SDL_CreateRenderer: {}", SDL_GetError() ) );
	}
}

Renderer::~Renderer()
{
	if( renderer_ ) SDL_DestroyRenderer( renderer_ );
	if( window_ )   SDL_DestroyWindow( window_ );
}

void Renderer::fillCell( int x, int y, SDL_Color c )
{
	SDL_SetRenderDrawColor( renderer_, c.r, c.g, c.b, c.a );
	SDL_Rect rect{x * CellSize + 1, y * CellSize + 1, CellSize - 2, CellSize - 2};
	SDL_RenderFillRect( renderer_, &rect );
}

SDL_Rect Renderer::restartButtonRect()
{
	constexpr int BtnW = 120, BtnH = 44;
	return {(WindowWidth - BtnW) / 2, (WindowHeight - BtnH) / 2, BtnW, BtnH};
}

void Renderer::drawGameOver()
{
	// Dark overlay
	SDL_SetRenderDrawBlendMode( renderer_, SDL_BLENDMODE_BLEND );
	SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 160 );
	SDL_Rect overlay{0, 0, WindowWidth, WindowHeight};
	SDL_RenderFillRect( renderer_, &overlay );
	SDL_SetRenderDrawBlendMode( renderer_, SDL_BLENDMODE_NONE );

	// "Play Again" button background
	SDL_Rect btn = restartButtonRect();
	SDL_SetRenderDrawColor( renderer_, 60, 180, 75, 255 );
	SDL_RenderFillRect( renderer_, &btn );

	// Button border
	SDL_SetRenderDrawColor( renderer_, 120, 230, 80, 255 );
	SDL_RenderDrawRect( renderer_, &btn );

	// Draw a pixel-art play triangle (▶) centred in the button
	int cx = btn.x + btn.w / 2 - 4;
	int cy = btn.y + btn.h / 2;
	SDL_SetRenderDrawColor( renderer_, 255, 255, 255, 255 );
	for( int row = 0; row < 12; ++row ) {
		int half = row / 2;
		SDL_RenderDrawLine( renderer_, cx + row, cy - half, cx + row, cy + half );
	}
}

void Renderer::updateTitle( Game const& game )
{
	std::string title;
	if( game.state() == GameState::GameOver )
		title = std::format( "Snake | GAME OVER — Score: {} | Press R to restart", game.score() );
	else
		title = std::format( "Snake | Score: {}", game.score() );
	SDL_SetWindowTitle( window_, title.c_str() );
}

void Renderer::render( Game const& game )
{
	// Background
	SDL_SetRenderDrawColor( renderer_, 20, 20, 20, 255 );
	SDL_RenderClear( renderer_ );

	// Grid lines
	SDL_SetRenderDrawColor( renderer_, 35, 35, 35, 255 );
	for( int x = 0; x <= Game::GridWidth; ++x )
		SDL_RenderDrawLine( renderer_, x * CellSize, 0, x * CellSize, WindowHeight );
	for( int y = 0; y <= Game::GridHeight; ++y )
		SDL_RenderDrawLine( renderer_, 0, y * CellSize, WindowWidth, y * CellSize );

	// Food
	auto [fx, fy] = game.food().position();
	fillCell( fx, fy, {220, 50, 50, 255} );

	// Snake body (skip head)
	auto const& body = game.snake().body();
	for( std::size_t i = 1; i < body.size(); ++i )
		fillCell( body[i].x, body[i].y, {70, 170, 70, 255} );

	// Snake head
	if( !body.empty() )
		fillCell( body[0].x, body[0].y, {120, 230, 80, 255} );

	if( game.state() == GameState::GameOver )
		drawGameOver();

	SDL_RenderPresent( renderer_ );
	updateTitle( game );
}
