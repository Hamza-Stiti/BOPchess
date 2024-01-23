#pragma once
#include<string>
#include <SDL_image.h>
#include <array>
#include "position.h"
#include "enums.h"


class texture
{
private:

	SDL_Texture* image_texture;

	SDL_Texture* loading(SDL_Renderer* p_renderer, const std::string& filename);

public:
	texture(SDL_Renderer* p_renderer, const std::string& filename);

	texture() : image_texture(nullptr) {}



	~texture();


	static std::array<texture*, 12> uploadimages(SDL_Renderer* renderer);

	static void freeimages(std::array<texture*, 12> images);

	static void DrawRect(SDL_Renderer* p_renderer, int p_x, int p_y, int edge, colour p_color);

	static void DrawRect(SDL_Renderer* p_renderer, int p_x, int p_y, int edge);

	static void DrawRect(SDL_Renderer* p_renderer, int p_x, int p_y, int p_w, int p_h, int r, int g, int b);


	void DrawTexture(SDL_Renderer* p_renderer, int p_x, int p_y, int edge);

	void DrawTexture(SDL_Renderer* p_renderer, int p_x, int p_y, int p_w, int p_h);
};