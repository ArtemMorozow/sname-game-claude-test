#include "Snake.hpp"
#include <algorithm>
#include <ranges>

Snake::Snake( Vec2 startPos, Direction startDir )
{
	reset( startPos, startDir );
}

void Snake::reset( Vec2 startPos, Direction startDir )
{
	body_.clear();
	dir_     = startDir;
	growing_ = false;

	// Start with length 3, extending backwards from head
	Vec2 back = dirVec( startDir );
	body_.push_back( startPos );
	body_.push_back( {startPos.x - back.x,     startPos.y - back.y} );
	body_.push_back( {startPos.x - back.x * 2, startPos.y - back.y * 2} );
}

void Snake::move()
{
	body_.push_front( head() + dirVec( dir_ ) );
	if( !growing_ )
		body_.pop_back();
	growing_ = false;
}

void Snake::grow()
{
	growing_ = true;
}

void Snake::changeDirection( Direction newDir )
{
	if( !areOpposite( dir_, newDir ) )
		dir_ = newDir;
}

bool Snake::occupies( Vec2 pt ) const
{
	return std::ranges::any_of( body_, [pt]( Vec2 v ) { return v == pt; } );
}

bool Snake::collidesWithSelf() const
{
	auto h = head();
	return std::ranges::any_of( body_ | std::views::drop( 1 ), [h]( Vec2 v ) { return v == h; } );
}
