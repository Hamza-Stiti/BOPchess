#pragma once
#include <array>
#include "RenderWindow.h"
#include "board.h"


namespace main_game
{
	void loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid);

	void update(RenderWindow& winren, board& grid);

	void input(RenderWindow& winren, std::array<texture*, 12>& images, board& grid);
}

namespace move_input
{
	void loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, position start, std::vector<position>& moves);

	void update(RenderWindow& winren, board& grid, std::vector<position>& moves);

	bool input(RenderWindow& winren, std::array<texture*, 12>& images, class board& grid, const position& start, std::vector<position>& legal_moves);
}

namespace promotion
{
	void loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, position pos);

	void update(RenderWindow& winren, board& grid, texture* promotion);

	pieces_code input(RenderWindow& winren, board& grid);
}

namespace gameover
{
	void loop(RenderWindow& winren, board& grid, game state, colour loser);

	void update(RenderWindow& winren, board& grid, texture& message, texture& button);

	bool input(RenderWindow& winren);
}

namespace menu
{
	void loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid);
	
	void update(RenderWindow& winren, texture* buttons, int r1, int g1, int b1, int r2, int g2, int b2);

	bool input(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, int& r1, int& g1, int& b1, int& r2, int& g2, int& b2);
}

