#include "piece.h"
#include "board.h"
#include <utility>



piece::piece(position p_pos, colour p_pcolour, texture& p_image) :
	pos(p_pos), pcolour(p_pcolour), image(p_image), pice_code(pieces_code::piece)
{}

std::vector<position> piece::legalmoves(board & grid)
{
	std::vector<position> temp = AvailableMoves(grid);
	std::vector<position> result;
	position la = pos;
	for (const position& i : temp)
	{
		bool testing = test(grid, i);
		if (test(grid, i))
			result.push_back(i);
	}


	return result;
}

bool piece::test(board grid, position dest)
{

	grid.move(pos, dest);

	grid.changeturn();

	bool result = grid.check();

	return !result;

}



