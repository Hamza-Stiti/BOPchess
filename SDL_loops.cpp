#include "SDL_loops.h"
#include <fstream>



void main_game::loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid)
{
	update(winren, grid);
	for (int x = 0; x < 8; ++x)
	{
		if (grid[0][x].nonempty())
			if (grid[0][x]->getcode() == pieces_code::Bpawn || grid[0][x]->getcode() == pieces_code::Wpawn)
			{
				grid[0][x]->specialcases(winren, images, grid);
				grid.changeturn();
			}
		if (grid[7][x].nonempty())
			if (grid[7][x]->getcode() == pieces_code::Bpawn || grid[0][x]->getcode() == pieces_code::Wpawn)
			{
				grid[7][x]->specialcases(winren, images, grid);
				grid.changeturn();
			}
	}

	while (winren.getrunning())
	{
		update(winren, grid);

		input(winren, images, grid);

		game state = grid.game_state();		
		if (state != game::contin)
		{
			gameover::loop(winren, grid, state, grid.getturn());
			grid.remove();
			break;
		}
	}
}

void main_game::update(RenderWindow& winren, board& grid)
{
	winren.DrawBoard(grid);
	winren.clear();
}

void main_game::input(RenderWindow& winren, std::array<texture*, 12>& images, board& grid)
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			grid.save();
			winren.set_running(false);
			return;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				position start(winren.GetMousePos(winren.getwidth(), event.motion.x), winren.GetMousePos(winren.getheight(), event.motion.y));

				if (start.insideboard())
					if (grid[start.y][start.x].nonempty())
						if (grid[start.y][start.x]->getcolour() == grid.getturn())
						{
							std::vector<position> legal_moves = grid[start.y][start.x]->legalmoves(grid);
							move_input::loop(winren, images, grid, start, legal_moves);
						}
			}
			return;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				std::cout << "window resized\n";
				winren.resize();
			}
			return;

		default:
			break;
		}
	}
}



void move_input::loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, position start, std::vector<position>& moves)
{
	while (winren.getrunning())
	{
		update(winren, grid, moves);

		if(input(winren, images, grid, start, moves)) return;
	}
}

void move_input::update(RenderWindow& winren, board& grid, std::vector<position>& moves)
{
	winren.DrawBoard(grid);
	winren.DrawMoves(moves);
	winren.clear();
}

bool move_input::input(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, const position& start, std::vector<position>& legal_moves)
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			grid.save();
			winren.set_running(false);
			return true;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				position end(winren.GetMousePos(winren.getwidth(), event.motion.x), winren.GetMousePos(winren.getheight(), event.motion.y));

				if (end.insideboard())
				{
					auto it = std::find(legal_moves.begin(), legal_moves.end(), end);
					if (it != legal_moves.end())
					{
						grid.move(winren, images, start, end);
						if (grid[end.y][end.x]->getcode() == pieces_code::Bking || grid[end.y][end.x]->getcode() == pieces_code::Wking)
						{
							if (end.x == start.x + 2)
								grid.move(winren, images, position(7, end.y), position(end.x - 1, end.y));
							if (end.x == start.x - 2)
								grid.move(winren, images, position(0, end.y), position(end.x + 1, end.y));
						}
						if (grid[end.y][end.x]->getcode() == pieces_code::Bpawn || grid[end.y][end.x]->getcode() == pieces_code::Wpawn)
						{
							if (end.x != start.x)
							{
								if (!(grid.get_enpassant() == position(-1, -1)))
								{
									grid[end.y - (int)grid[end.y][end.x]->getcolour()][end.x] = smartpiece(nullptr);
								}
							}

							if ((end.y == start.y + 2 || end.y == start.y - 2) && grid[end.y][end.x]->getmoved())
								grid.set_enpassant(end);
							else
								grid.set_enpassant(position(-1, -1));
						}
						grid.changeturn();
						return true;
					}
				}
			}
			return true;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				std::cout << "window resized\n";
				winren.resize();
			}
			return false;

		default:
			break;
		}
	}
	return false;
}

void promotion::loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, position pos)
{

	texture promotion[] = {
		texture(winren.getrenderer(), "res/promotion_queen.png"), 
		texture(winren.getrenderer(), "res/promotion_rook.png"),
		texture(winren.getrenderer(), "res/promotion_bishop.png"),
		texture(winren.getrenderer(), "res/promotion_knight.png")
	};


	while (winren.getrunning())
	{
		update(winren, grid, promotion);

		pieces_code temp = input(winren, grid);

		switch (temp)
		{
		case pieces_code::Bqueen:
			grid.promotion_queen(pos, images);
			return;
		case pieces_code::Brook:
			grid.promotion_rook(pos, images);
			return;
		case pieces_code::Bbishop:
			grid.promotion_bishop(pos, images);
			return;
		case pieces_code::Bknight:
			grid.promotion_knight(pos, images);
			return;
		default:
			break;
		}
		
	}
}

void promotion::update(RenderWindow& winren, board& grid, texture* promotion)
{
	winren.DrawBoard(grid);

	promotion[0].DrawTexture(winren.getrenderer(), winren.GetDrawPos(winren.getwidth(), 2), winren.GetDrawPos(winren.getheight(), 4), winren.getedge());
	promotion[1].DrawTexture(winren.getrenderer(), winren.GetDrawPos(winren.getwidth(), 3), winren.GetDrawPos(winren.getheight(), 4), winren.getedge());
	promotion[2].DrawTexture(winren.getrenderer(), winren.GetDrawPos(winren.getwidth(), 4), winren.GetDrawPos(winren.getheight(), 4), winren.getedge());
	promotion[3].DrawTexture(winren.getrenderer(), winren.GetDrawPos(winren.getwidth(), 5), winren.GetDrawPos(winren.getheight(), 4), winren.getedge());

	winren.clear();
}

pieces_code promotion::input(RenderWindow& winren, board& grid)
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		switch (event.type) 
		{
		case SDL_QUIT:
			grid.save();
			winren.set_running(false);
			return pieces_code::Bpawn;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				position pos(winren.GetMousePos(winren.getwidth(), event.motion.x), winren.GetMousePos(winren.getheight(), event.motion.y));
				
				if (pos.insideboard())
				{
					if (pos == position(2, 4))
						return pieces_code::Bqueen;
					
					if (pos == position(3, 4))
						return pieces_code::Brook;

					if (pos == position(4, 4))
						return pieces_code::Bbishop;

					if (pos == position(5, 4))
						return pieces_code::Bknight;

				}
			}
			return pieces_code::Bpawn;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				std::cout << "window resized\n";
				winren.resize();
			}
			return pieces_code::Bpawn;
		default:
			break;
		}
	}
	
	return pieces_code::piece;
}





void gameover::loop(RenderWindow& winren, board& grid, game state, colour loser)
{
	std::string message_name = "res/";
	switch (state)
	{
	case game::checkmate:
		std::cout << "check mate\n";
		message_name += loser == colour::white ? "black_won.png" : "white_won.png";
		break;
	case game::stalemate:
		std::cout << "stale mate\n";
		message_name += "stalemate.png";
		break;
	case game::contin:
		return;
	}

	texture message(winren.getrenderer(), message_name.c_str());
	texture button(winren.getrenderer(), "res/menu.png");

	while (winren.getrunning())
	{
		update(winren, grid, message, button);

		if (input(winren))
			return;
	}
}

void gameover::update(RenderWindow& winren, board& grid, texture& message, texture& button)
{
	int x1 = winren.GetDrawPos(winren.getwidth(), 2);
	int y1 = winren.GetDrawPos(winren.getheight(), 3);
	int w1 = winren.getedge() * 4;
	int h1 = winren.getedge();
	
	int x2 = winren.GetDrawPos(winren.getwidth(), 3);
	int y2 = winren.GetDrawPos(winren.getheight(), 4);
	int w2 = winren.getedge() * 2;
	int h2 = winren.getedge();


	winren.DrawBoard(grid);

	texture::DrawRect(winren.getrenderer(), x1, y1, w1, h1, 0, 0, 0);
	message.DrawTexture(winren.getrenderer(), x1, y1, w1, h1);
	
	texture::DrawRect(winren.getrenderer(), x2, y2, w2, h2, 0, 0, 0);
	button.DrawTexture(winren.getrenderer(), x2, y2, w2, h2);

	winren.clear();
}

bool gameover::input(RenderWindow& winren)
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			winren.set_running(false);
			return false;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				position pos(winren.GetMousePos(winren.getwidth(), event.motion.x), winren.GetMousePos(winren.getheight(), event.motion.y));
				if (pos == position(3, 4) || pos == position(4, 4))
					return true;
			}
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				std::cout << "window resized\n";
				winren.resize();
			}
			return false;
		default:
			break;
		}
	}
}

void menu::loop(RenderWindow& winren, std::array<texture*, 12>& images, board& grid)
{
	texture buttons[] = {
		texture(winren.getrenderer(), "res/new_game.png"),
		texture(winren.getrenderer(), "res/continue.png"),
	};

	int r1 = 50, g1 = 50, b1 = 50, r2 = 50, g2 = 50, b2 = 50;

	while (winren.getrunning())
	{
		update(winren, buttons, r1, g1, b1, r2, b2, g2);
		if (input(winren, images, grid, r1, g1, b1, r2, b2, g2))
			return;
	}
}

void menu::update(RenderWindow& winren, texture* buttons, int r1, int g1, int b1, int r2, int g2, int b2)
{
	int x1 = winren.GetDrawPos(winren.getwidth(), 2);
	int y1 = winren.GetDrawPos(winren.getheight(), 3);
	int x2 = x1;
	int y2 = winren.GetDrawPos(winren.getheight(), 4);
	int w = winren.getedge() * 4;
	int h = winren.getedge();

	winren.DrawBackground();

	texture::DrawRect(winren.getrenderer(), x1, y1, w, h, r1, g1, b1);
	buttons[0].DrawTexture(winren.getrenderer(), x1, y1, w, h);

	texture::DrawRect(winren.getrenderer(), x2, y2, w, h, r2, g2, b2);
	buttons[1].DrawTexture(winren.getrenderer(), x2, y2, w, h);

	winren.clear();
}

bool menu::input(RenderWindow& winren, std::array<texture*, 12>& images, board& grid, int& r1, int& g1, int& b1, int& r2, int& g2, int& b2)
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			grid.save();
			winren.set_running(false);
			return true;

		case SDL_MOUSEMOTION:
		{
			position pos(winren.GetMousePos(winren.getwidth(), event.motion.x), winren.GetMousePos(winren.getheight(), event.motion.y));

			if (pos == position(2, 3) || pos == position(3, 3) || pos == position(4, 3) || pos == position(5, 3))
			{
				r1 = 0, g1 = 100; b1 = 255; r2 = 50; g2 = 50; b2 = 50;
				return false;
			}
			else if (pos == position(2, 4) || pos == position(3, 4) || pos == position(4, 4) || pos == position(5, 4))
			{
				r2 = 0, g2 = 100; b2 = 255; r1 = 50; g1 = 50; b1 = 50;
				return false;
			}
			else
			{
				r2 = 50, g2 = 50; b2 = 50; r1 = 50; g1 = 50; b1 = 50;
				return false;
			}
			return false;
		}
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				position pos(winren.GetMousePos(winren.getwidth(), event.motion.x), winren.GetMousePos(winren.getheight(), event.motion.y));
				
				if (pos == position(2, 3) || pos == position(3, 3) || pos == position(4, 3) || pos == position(5, 3))
				{
					board temp(images);
					grid.copy(temp);
					return true;
				}
				if (pos == position(2, 4) || pos == position(3, 4) || pos == position(4, 4) || pos == position(5, 4))
				{
					std::ifstream file("files/continue_check.txt");
					bool check;
					file >> check;
					file.close();
					if (check)
					{
						board temp(images, "files/continue.txt");
						grid.copy(temp);
						return true;
					}
				}
			}
			return false;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				std::cout << "window resized\n";
				winren.resize();
			}
			return false;
		default:
			break;
		}
	}
}
