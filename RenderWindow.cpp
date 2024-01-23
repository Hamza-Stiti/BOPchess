#include "RenderWindow.h"
#include <SDL.h>
#include <iostream>
#include "texture.h"
#include "board.h"
#include "SDL_loops.h"
#include <vector>


bool RenderWindow::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cerr << "failed to initialize SDL\n" << SDL_GetError << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
		std::cerr << "failed to create window\n" << SDL_GetError << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
		std::cerr << "failed to create renderer\n" << SDL_GetError << std::endl;

	return true;
}

RenderWindow::RenderWindow(const std::string& p_title, int p_width, int p_height) :
	title(p_title), width(p_width), height(p_height)
{
	edge = calcEdge();
	running = init();
}

RenderWindow::~RenderWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void RenderWindow::DrawBackground() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::clear() const
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}





void RenderWindow::DrawMoves(std::vector<position>& moves)
{
	for (position i : moves)
	{
		texture::DrawRect(renderer, GetDrawPos(width,i.x), GetDrawPos(height, i.y), edge);
	}

}

void RenderWindow::DrawBoard(board& grid)
{
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
		{
			if ((x + y) % 2)
				texture::DrawRect(renderer, GetDrawPos(width, x), GetDrawPos(height, y), edge, colour::black);
			else
				texture::DrawRect(renderer, GetDrawPos(width, x), GetDrawPos(height, y), edge, colour::white);

			if (grid[y][x].nonempty())
				grid[y][x]->drawpiece( renderer, GetDrawPos(width, grid[y][x]->getpos().x), GetDrawPos(height, grid[y][x]->getpos().y), edge );
		}
}

void RenderWindow::promotion(board& grid, std::array<texture*, 12>& images, const position& pos)
{
	promotion::loop(*this, images, grid, pos);
}



void RenderWindow::resize()
{
	SDL_GetWindowSize(window, &width, &height);

	edge = calcEdge();
}
