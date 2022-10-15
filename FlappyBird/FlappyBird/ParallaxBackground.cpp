#include "ParallaxBackground.h"

ParallaxBackground::ParallaxBackground(const float width, const float height, SDL_Renderer* renderer) : Object(0, 0, width, height, "background.png", renderer) {
	speed = 10;
	secondRect.x = width;
	secondRect.y = 0;
	secondRect.w = width;
	secondRect.h = height;
}

void ParallaxBackground::update(const float dt, KeyListener& listener) {
	
	if(rect.x + rect.w < 0) {
		rect.x = rect.w;
	}

	if (secondRect.x + secondRect.w < 0) {
		secondRect.x = secondRect.w;
	}

	rect.x -= speed * 1 / dt;
	secondRect.x -= speed * 1 / dt;
}


void ParallaxBackground::draw(SDL_Renderer* renderer) const {
	SDL_RenderCopyF(renderer, texture, NULL, &rect);
	SDL_RenderCopyF(renderer, texture, NULL, &secondRect);
}