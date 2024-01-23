#include "texture.h"
#include<iostream>

SDL_Texture* texture::loading(SDL_Renderer* p_renderer, const std::string& filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (!surface)
	{
		std::cerr << "couldnt load image\n";
		return nullptr;
	}
	SDL_Texture* result;
	result = SDL_CreateTextureFromSurface(p_renderer, surface);
	if (!result)
	{
		std::cerr << "couldnt creat texture\n";
		return nullptr;
	}
	SDL_FreeSurface(surface);

	return result;
}


texture::texture(SDL_Renderer* p_renderer, const std::string& filename)
{
	image_texture = loading(p_renderer, filename);
}


texture::~texture()
{
	SDL_DestroyTexture(image_texture);
}

std::array<texture*, 12> texture::uploadimages(SDL_Renderer* renderer)
{
	std::array<texture*, 12> images;

	images.at((int) pieces_code::Bking) = new texture(renderer, "res/Chess_k_black.png");
	images.at((int) pieces_code::Wking) = new texture(renderer, "res/Chess_k_white.png");
	images.at((int) pieces_code::Bqueen) = new texture(renderer, "res/Chess_q_black.png");
	images.at((int) pieces_code::Wqueen) = new texture(renderer, "res/Chess_q_white.png");
	images.at((int) pieces_code::Bbishop) = new texture(renderer, "res/Chess_b_black.png");
	images.at((int) pieces_code::Wbishop) = new texture(renderer, "res/Chess_b_white.png");
	images.at((int) pieces_code::Bknight) = new texture(renderer, "res/Chess_n_black.png");
	images.at((int) pieces_code::Wknight) = new texture(renderer, "res/Chess_n_white.png");
	images.at((int) pieces_code::Brook) = new texture(renderer, "res/Chess_r_black.png");
	images.at((int) pieces_code::Wrook) = new texture(renderer, "res/Chess_r_white.png");
	images.at((int) pieces_code::Bpawn) = new texture(renderer, "res/Chess_p_black.png");
	images.at((int) pieces_code::Wpawn) = new texture(renderer, "res/Chess_p_white.png");
	

	return images;
}

void texture::freeimages(std::array<texture*, 12> images)
{
	for (texture* image : images)
	{
		if (image->image_texture == nullptr) continue;
		SDL_DestroyTexture(image->image_texture);
		delete image;
	}
}

void texture::DrawRect(SDL_Renderer* p_renderer, int p_x, int p_y, int edge, colour p_color)
{
	SDL_Rect rect{ p_x,p_y,edge,edge };// the rectangle

	if (p_color == colour::black)
		SDL_SetRenderDrawColor(p_renderer, 101, 67, 33, 255);
	else
		SDL_SetRenderDrawColor(p_renderer, 244, 226, 198, 255);

	SDL_RenderFillRect(p_renderer, &rect);

}

void texture::DrawRect(SDL_Renderer* p_renderer, int p_x, int p_y, int edge)
{
	SDL_Rect rect{ p_x , p_y, edge - (edge * 70) / 100,edge - (edge * 70) / 100};// the rectangle

	SDL_SetRenderDrawColor(p_renderer, 173, 216, 230, 255);

	SDL_RenderFillRect(p_renderer, &rect);
}

void texture::DrawTexture(SDL_Renderer* p_renderer, int p_x, int p_y, int edge)
{
	if (!image_texture) return;

	SDL_Rect rect{ p_x,p_y,edge,edge };
	SDL_RenderCopy(p_renderer, image_texture, nullptr, &rect);
}

void texture::DrawRect(SDL_Renderer* p_renderer, int p_x, int p_y, int p_w, int p_h, int r, int g, int b)
{
	SDL_Rect rect{ p_x , p_y, p_w,p_h };// the rectangle

	SDL_SetRenderDrawColor(p_renderer, r, g, b, 255);

	SDL_RenderFillRect(p_renderer, &rect);
}

void texture::DrawTexture(SDL_Renderer* p_renderer, int p_x, int p_y, int p_w, int p_h)
{
	if (!image_texture) return;

	SDL_Rect rect{ p_x,p_y,p_w,p_h };
	SDL_RenderCopy(p_renderer, image_texture, nullptr, &rect);
}
