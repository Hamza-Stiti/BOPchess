#include <SDL.h>
#include <iostream>
#include "RenderWindow.h"
#include "enums.h"
#include "texture.h"
#include "board.h"
#include "SDL_loops.h"



int main(int argc, char* args[])
{
	RenderWindow winren("chess", 500, 500);
	std::array<texture*, 12> images = texture::uploadimages(winren.getrenderer());

	board grid(images);
	
	while (winren.getrunning())
	{
		menu::loop(winren, images, grid);
		if (winren.getrunning())
			main_game::loop(winren, images, grid);
	}

	texture::freeimages(images);

	return 0;
}