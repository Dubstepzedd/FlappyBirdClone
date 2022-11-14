#ifndef UTILITIIES_H
#define UTILITIIES_H
#include <SDL.h>
#include <SDL_image.h>

class Utilities {
public:
	static constexpr int HEIGHT = 1000;
	static constexpr int WIDTH = 1000;
	static SDL_Texture* birdTexture;
	static SDL_Texture* pipeTexture;
	static SDL_Texture* backgroundTexture;

	static void initialize(SDL_Renderer* renderer);


};
#endif
