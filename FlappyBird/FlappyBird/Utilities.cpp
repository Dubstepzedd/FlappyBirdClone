#include "Utilities.h"

SDL_Texture* Utilities::birdTexture = 0;
SDL_Texture* Utilities::backgroundTexture = 0;
SDL_Texture* Utilities::pipeTexture = 0;

void Utilities::initialize(SDL_Renderer* renderer) {
	
	//Bird Image.
	SDL_Surface* birdSurface = IMG_Load("images/bird.png");
	Utilities::birdTexture = SDL_CreateTextureFromSurface(renderer, birdSurface);
	SDL_FreeSurface(birdSurface);
	
	// Pipe Image
	SDL_Surface* pipeSurface = IMG_Load("images/pipe.png");
	Utilities::pipeTexture = SDL_CreateTextureFromSurface(renderer, pipeSurface);
	SDL_FreeSurface(pipeSurface);

	//Background Image
	SDL_Surface* backgroundSurface = IMG_Load("images/background.png");
	Utilities::backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_FreeSurface(backgroundSurface);


}