#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class DynamicText {

	public:

		void init(const int size, const std::string path);
		
		~DynamicText();
		
		void drawText(SDL_Renderer* renderer, const float x, const float y, const std::string text, const SDL_Color color);

		void getDimenions(const std::string text, int w, int h);

	private:
		TTF_Font* font = nullptr;
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
		SDL_FRect rect = SDL_FRect();

};


#endif

