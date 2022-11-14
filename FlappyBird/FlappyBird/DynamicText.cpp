#include "DynamicText.h"
#include <iostream>
#include <SDL_ttf.h>


void DynamicText::init(const int size, const std::string path) {
	if (TTF_Init() != 0) {
		std::cout << "Could not initialize SDL2_ttf. Error: " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont(path.c_str(), size);
}

DynamicText::~DynamicText() {
	TTF_CloseFont(font);
}

void DynamicText::drawText(SDL_Renderer* renderer, const float x, const float y, const std::string text, const SDL_Color color) {

	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	int w, h;
	TTF_SizeUTF8(font, text.c_str(), &w, &h);
	rect.x = x;
	rect.y = y;
	rect.w = (float) w;
	rect.h = (float) h; //This is a bit larger than the actual text height. Could not find any solution to this.

	SDL_RenderCopyF(renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void DynamicText::getDimenions(const std::string text, int& w, int& h) {
	TTF_SizeUTF8(font, text.c_str(), &w, &h);
}