#pragma once
#include <SDL.h>
#include <string>
#include "enums.h"
#include "position.h"
#include "texture.h"
#include <vector>



class RenderWindow
{
private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;


	int width, height, edge;
	std::string title;
	bool running = true;
	

public:
	RenderWindow(const std::string& p_title, int p_width, int p_height);

	~RenderWindow();

	bool init();

	inline void set_running(bool val) { running = val; }

	inline SDL_Renderer* getrenderer() const { return renderer; }

	inline bool getrunning() const { return running; }

	inline int getwidth() { return width; }

	inline int getheight() { return height; }
	
	inline int getedge() { return edge; }
	
	inline int calcEdge() { return width < height ? width / 8 : height / 8; }

	void promotion(class board& grid, std::array<texture*, 12>& images, const position& pos);

	void DrawBackground() const;

	void clear() const;

	inline int GetDrawPos(int delta, int position) { return (delta / 2) - (4 * edge) + (position * edge); }

	inline int GetMousePos(int delta, int position) { return (position - (delta / 2) + (4 * edge)) / edge; }

	void DrawMoves(std::vector<position>& moves);

	void DrawBoard(class board& grid);



	void resize();



};