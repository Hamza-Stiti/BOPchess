#pragma once
#include <vector>
#include "enums.h"
#include "position.h"
#include "texture.h"
//#include "board.h"

class piece
{
protected:
	position pos;
	colour pcolour;
	texture& image;
	pieces_code pice_code;
	bool moved = false;


public:
	friend class smartpiece;
	piece(position p_pos, colour p_pcolour, texture& images);

	virtual void specialcases(class RenderWindow& winren, std::array<texture*, 12>& images, class board& grid){}
	
	virtual void specialcases(class board& grid){}

	virtual std::vector<position> AvailableMoves(class board& grid) = 0;

	inline bool getmoved() { return moved; }

	inline texture& getimage() { return image; }

	inline pieces_code getcode() { return pice_code; }

	virtual std::vector<position> legalmoves(class board& grid);

	bool test(class board grid, position dest);

	inline void set_pos(const position& p_pos) { pos = p_pos; }

	inline position getpos() { return pos; }

	inline colour getcolour() { return pcolour; }

	inline void drawpiece(SDL_Renderer* p_renderer, int p_x, int p_y, int edge)
	{ image.DrawTexture(p_renderer, p_x, p_y, edge); }

};
