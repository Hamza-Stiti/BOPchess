#pragma once
#include <array>
#include <iostream>
#include "piece.h"
#include "smartPiece.h"
#include "position.h"
#include "enums.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"



class board
{
private:
	std::array<std::array<smartpiece, 8>, 8> grid;
	colour turn = colour::white;

	position black_king;
	position white_king;

	position enpassant = position(-1, -1);

public:
	board(std::array<texture*, 12>& images);

	board(std::array<texture*, 12>& images, std::string file_name);

	void save();

	void remove();

	board(board& other);

	~board();

	std::array<smartpiece, 8>& operator[](int index);

	void copy(board& other);

	inline position get_enpassant() { return enpassant; }

	inline void set_enpassant(position val) { enpassant = val; }

	inline void set_black_king(const position& new_pos) { black_king = new_pos; }

	inline void set_white_king(const position& new_pos) { white_king = new_pos; }

	inline std::array<std::array<smartpiece, 8>, 8>& getgrid() { return grid; }

	void move(class RenderWindow& winren, std::array<texture*, 12>& images, const position& start, const position& end);

	void move(const position& start, const position& end);

	inline void changeturn() { turn = turn == colour::black ? colour::white : colour::black; }

	inline colour getturn() { return turn; }

	bool check(colour oponent);

	bool check();

	game game_state();


	void promotion_queen(position pos, std::array<texture*, 12> images);
	void promotion_rook(position pos, std::array<texture*, 12> images);
	void promotion_bishop(position pos, std::array<texture*, 12> images);
	void promotion_knight(position pos, std::array<texture*, 12> images);




};