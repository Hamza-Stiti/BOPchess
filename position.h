#pragma once

struct position
{
	int x, y;

	position(int p_x, int p_y) : x(p_x), y(p_y) {}
	position():x(0), y(0){}
	position(const position& pos) : x(pos.x), y(pos.y) {}

	position& operator=(const position& other);
	position operator+(const position& other) const;
	bool operator==(const position& other);

	inline bool insideboard() { return (x < 8) && (x >= 0) && (y < 8) && (y >= 0); }
};

