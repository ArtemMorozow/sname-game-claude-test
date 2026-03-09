#include <SDL2/SDL.h>
#include <cstdio>
#include "Game.hpp"
#include "Renderer.hpp"

int main()
{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		std::fprintf( stderr, "SDL_Init failed: %s\n", SDL_GetError() );
		return 1;
	}

	try {
		Game     game;
		Renderer renderer;

		// Milliseconds between game ticks (controls snake speed)
		constexpr Uint32 TickMs = 120;

		bool   running  = true;
		Uint32 lastTick = SDL_GetTicks();

		while( running ) {
			SDL_Event event;
			while( SDL_PollEvent( &event ) ) {
				switch( event.type ) {
					case SDL_QUIT:
						running = false;
						break;
					case SDL_MOUSEBUTTONDOWN:
						if( event.button.button == SDL_BUTTON_LEFT &&
						    game.state() == GameState::GameOver ) {
							SDL_Rect btn = Renderer::restartButtonRect();
							int mx = event.button.x, my = event.button.y;
							if( mx >= btn.x && mx < btn.x + btn.w &&
							    my >= btn.y && my < btn.y + btn.h )
								game.restart();
						}
						break;
					case SDL_KEYDOWN:
						switch( event.key.keysym.sym ) {
							case SDLK_UP:    [[fallthrough]];
							case SDLK_w:     game.handleInput( Direction::Up );    break;
							case SDLK_DOWN:  [[fallthrough]];
							case SDLK_s:     game.handleInput( Direction::Down );  break;
							case SDLK_LEFT:  [[fallthrough]];
							case SDLK_a:     game.handleInput( Direction::Left );  break;
							case SDLK_RIGHT: [[fallthrough]];
							case SDLK_d:     game.handleInput( Direction::Right ); break;
							case SDLK_r:
								if( game.state() == GameState::GameOver )
									game.restart();
								break;
							case SDLK_ESCAPE:
								running = false;
								break;
						}
						break;
				}
			}

			if( Uint32 const now = SDL_GetTicks(); now - lastTick >= TickMs ) {
				game.update();
				lastTick = now;
			}

			renderer.render( game );
		}
	} catch( std::exception const& e ) {
		std::fprintf( stderr, "Error: %s\n", e.what() );
		SDL_Quit();
		return 1;
	}

	SDL_Quit();
	return 0;
}
