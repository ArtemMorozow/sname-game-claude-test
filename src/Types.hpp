#pragma once

enum class Direction { Up, Down, Left, Right };
enum class GameState { Running, GameOver };

struct Vec2 {
	int x, y;
	auto operator<=>( Vec2 const& ) const = default;
	Vec2 operator+( Vec2 o ) const { return {x + o.x, y + o.y}; }
};

inline Vec2 dirVec( Direction d )
{
	switch( d ) {
		case Direction::Up:    return { 0, -1};
		case Direction::Down:  return { 0,  1};
		case Direction::Left:  return {-1,  0};
		case Direction::Right: return { 1,  0};
	}
	return {};
}

inline bool areOpposite( Direction a, Direction b )
{
	return (a == Direction::Up    && b == Direction::Down)  ||
	       (a == Direction::Down  && b == Direction::Up)    ||
	       (a == Direction::Left  && b == Direction::Right) ||
	       (a == Direction::Right && b == Direction::Left);
}
