#include "board.h"
#include <utility>
#include <fstream>
#include "RenderWindow.h"

board::board(std::array<texture*, 12>& images) : white_king(position(4, 7)), black_king(position(4, 0))
{
	/*
	* / r / n / b / q / k / b / n / r /
	* / p / p / p / p / p / p / p / p /
	* /   /   /   /   /   /   /   /   /
	* /   /   /   /   /   /   /   /   /
	* /   /   /   /   /   /   /   /   /
	* /   /   /   /   /   /   /   /   /
	* / p / p / p / p / p / p / p / p /
	* / r / n / b / q / k / b / n / r /
	*/

	grid[0][0] = smartpiece(new rook({0, 0}, colour::black, *images.at((int)pieces_code::Brook)));
	grid[0][1] = smartpiece(new knight({ 1, 0 }, colour::black, *images.at((int)pieces_code::Bknight)));
	grid[0][2] = smartpiece(new bishop({ 2, 0 }, colour::black, *images.at((int)pieces_code::Bbishop)));
	grid[0][3] = smartpiece(new queen({ 3, 0 }, colour::black, *images.at((int)pieces_code::Bqueen)));
	grid[0][4] = smartpiece(new king({ 4, 0 }, colour::black, *images.at((int)pieces_code::Bking)));
	grid[0][5] = smartpiece(new bishop({ 5, 0 }, colour::black, *images.at((int)pieces_code::Bbishop)));
	grid[0][6] = smartpiece(new knight({ 6, 0 }, colour::black, *images.at((int)pieces_code::Bknight)));
	grid[0][7] = smartpiece(new rook({7, 0}, colour::black, *images.at((int)pieces_code::Brook)));

	for(int i = 0; i < 8; ++i)
		grid[1][i] = smartpiece(new pawn({ i, 1 }, colour::black, *images.at((int)pieces_code::Bpawn)));
	
							   
	for (int i = 0; i < 8; ++i)
		grid[6][i] = smartpiece(new pawn({ i, 6 }, colour::white, *images.at((int)pieces_code::Wpawn)));
							   
	grid[7][0] = smartpiece(new rook({ 0, 7 }, colour::white, *images.at((int)pieces_code::Wrook)));
	grid[7][1] = smartpiece(new knight({ 1, 7 }, colour::white, *images.at((int)pieces_code::Wknight)));
	grid[7][2] = smartpiece(new bishop({ 2, 7 }, colour::white, *images.at((int)pieces_code::Wbishop)));
	grid[7][3] = smartpiece(new queen({ 3, 7 }, colour::white, *images.at((int)pieces_code::Wqueen)));
	grid[7][4] = smartpiece(new king({ 4, 7 }, colour::white, *images.at((int)pieces_code::Wking)));
	grid[7][5] = smartpiece(new bishop({ 5, 7 }, colour::white, *images.at((int)pieces_code::Wbishop)));
	grid[7][6] = smartpiece(new knight({ 6, 7 }, colour::white, *images.at((int)pieces_code::Wknight)));
	grid[7][7] = smartpiece(new rook({ 7, 7 }, colour::white, *images.at((int)pieces_code::Wrook)));


}

board::board(std::array<texture*, 12>& images, std::string file_name)
{
	std::ifstream file(file_name.c_str());
	try
	{
		if (file.fail())
			throw "file doesnt exist";
		pieces_code arr[8][8];
		for (int i = 0; i < 64; ++i)
		{
			int temp = 0;
			file >> temp;

			arr[i / 8][i % 8] = (pieces_code)temp;
		}

		for (int y = 0; y < 8; ++y)
			for (int x = 0; x < 8; ++x)
				grid[y][x] = smartpiece(images, arr[y][x], position(x, y));

		int convertable;
		int x, y;

		file >> convertable;
		turn = (colour)convertable;

		file >> x >> y;
		black_king = position(x, y);

		file >> x >> y;
		white_king = position(x, y);

		file >> x >> y;
		enpassant = position(x, y);
	}
	catch (const char* error)
	{
		std::cerr << error << std::endl;
		board temp(images);
		this->copy(temp);
	}


	file.close();
}

void board::save()
{
	std::ofstream file("files/continue.txt");
	for (int i = 0; i < 64; ++i)
	{
		smartpiece& temp = grid[i / 8][i % 8];
		if (temp.nonempty())
			file << (int)grid[i / 8][i % 8]->getcode() << std::endl;
		else
			file << (int)pieces_code::empty << std::endl;
	}
	
	file << (int)turn << std::endl;
	
	file << black_king.x << "\n" << black_king.y << std::endl;

	file << white_king.x << "\n" << white_king.y << std::endl;

	file << enpassant.x << "\n" << enpassant.y << std::endl;

	file.close();
	std::ofstream file_continue_check("files/continue_check.txt");
	file_continue_check << 1;
	file_continue_check.close();
}

void board::remove()
{
	std::ofstream file("files/continue.txt");
	
	file.close();

	std::ofstream file_continue_check("files/continue_check.txt");
	
	file_continue_check << 0;

	file_continue_check.close();
}



board::board(board& other)
{
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
			grid[y][x].copying(other.grid[y][x]);

	turn = other.turn;
	
	black_king = other.black_king;
	
	white_king = other.white_king;
}



board::~board()
{}



std::array<smartpiece, 8>& board::operator[](int index)
{
	return grid[index];
}

void board::copy(board& other)
{
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
			grid[y][x].copying(other.grid[y][x]);

	turn = other.turn;

	black_king = other.black_king;

	white_king = other.white_king;
}

void board::move(RenderWindow& winren, std::array<texture*, 12>& images, const position& start, const position& end)
{
	grid[end.y][end.x] = std::move(grid[start.y][start.x]);
	
	if (!grid[end.y][end.x].nonempty()) std::cout << "empty\n";

	grid[end.y][end.x]->set_pos(end);
	
	grid[end.y][end.x]->specialcases(winren, images, *this);

}

void board::move(const position& start, const position& end)
{
	grid[end.y][end.x] = std::move(grid[start.y][start.x]);

	grid[end.y][end.x]->set_pos(end);

	grid[end.y][end.x]->specialcases(*this);

}

bool board::check(colour oponent)
{
	int max_pieces = 16;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; x++)
		{
			if (!grid[y][x].nonempty() || grid[y][x]->getcolour() != oponent)
				continue;
			--max_pieces;
			std::vector<position> temp = grid[y][x]->AvailableMoves(*this);

			auto it = std::find(temp.begin(), temp.end(), oponent == colour::black ? white_king : black_king);

			if (it != temp.end())
				return true;

			if (max_pieces == 0)
				return false;
		}
	}
	return false;
}

bool board::check()
{
	int max_pieces = 16;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; x++)
		{
			if (!grid[y][x].nonempty() || grid[y][x]->getcolour() != turn)
				continue;
			--max_pieces;
			std::vector<position> temp = grid[y][x]->AvailableMoves(*this);

			auto it = std::find(temp.begin(), temp.end(), turn == colour::black ? white_king : black_king);

			if (it != temp.end())
				return true;

			if (max_pieces == 0)
				return false;
		}
	}
	return false;
}


game board::game_state()
{

	int max_pieces(16);
	bool movable = false;
	int number_of_pieces(0);

	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
		{		
			if (!grid[y][x].nonempty())
				continue;

			if (grid[y][x]->getcolour() != turn)
			{
				++number_of_pieces;
				continue;
			}

			if (grid[y][x]->legalmoves(*this).size() > 0)
			{
				movable = true;
				++number_of_pieces;
			}
		}

	colour oponent = turn == colour::black ? colour::white : colour::black;

	if (!movable)
	{
		if (check(oponent))
			return game::checkmate;
		else
			return game::stalemate;
	}

	if(number_of_pieces == 2)
		return game::stalemate;

	return game::contin;
}



void board::promotion_queen(position pos, std::array<texture*, 12> images)
{
	colour c = grid[pos.y][pos.x]->getcolour();
	position p = grid[pos.y][pos.x]->getpos();
	pieces_code index = c == colour::black ? pieces_code::Bqueen : pieces_code::Wqueen;
	smartpiece result = new queen(p, c, *images.at((int)index));
	grid[pos.y][pos.x] = std::move(result);
}

void board::promotion_rook(position pos, std::array<texture*, 12> images)
{
	colour c = grid[pos.y][pos.x]->getcolour();
	position p = grid[pos.y][pos.x]->getpos();
	pieces_code index = c == colour::black ? pieces_code::Brook : pieces_code::Wrook;
	smartpiece result = new rook(p, c, *images.at((int)index));
	grid[pos.y][pos.x] = std::move(result);
}

void board::promotion_bishop(position pos, std::array<texture*, 12> images)
{
	colour c = grid[pos.y][pos.x]->getcolour();
	position p = grid[pos.y][pos.x]->getpos();
	pieces_code index = c == colour::black ? pieces_code::Bbishop : pieces_code::Wbishop;
	smartpiece result = new bishop(p, c, *images.at((int)index));
	grid[pos.y][pos.x] = std::move(result);
}

void board::promotion_knight(position pos, std::array<texture*, 12> images)
{
	colour c = grid[pos.y][pos.x]->getcolour();
	position p = grid[pos.y][pos.x]->getpos();
	pieces_code index = c == colour::black ? pieces_code::Bknight : pieces_code::Wknight;
	smartpiece result = new knight(p, c, *images.at((int)index));
	grid[pos.y][pos.x] = std::move(result);
}

