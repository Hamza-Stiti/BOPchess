#include "position.h"

position& position::operator=(const position& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

position position::operator+(const position& other) const
{
	return position(x + other.x, y + other.y);
}

bool position::operator==(const position& other)
{
	return (x == other.x) && (y == other.y);
}
