#include "Food.hpp"
#include "Snake.hpp"
#include <vector>

Food::Food() : rng_( std::random_device{}() ) {}

void Food::randomize( int gridW, int gridH, Snake const& snake )
{
	std::vector<Vec2> candidates;
	candidates.reserve( static_cast<size_t>( gridW * gridH ) );

	for( int y = 0; y < gridH; ++y )
		for( int x = 0; x < gridW; ++x )
			if( Vec2 p{x, y}; !snake.occupies( p ) )
				candidates.push_back( p );

	if( candidates.empty() )
		return; // Snake fills the entire grid — victory condition

	std::uniform_int_distribution<int> dist( 0, static_cast<int>( candidates.size() ) - 1 );
	pos_ = candidates[dist( rng_ )];
}
