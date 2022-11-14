#include "ParallaxBackground.h"

ParallaxBackground::ParallaxBackground() {
	secondRect = SDL_FRect();
	speed = 10;
}

void ParallaxBackground::update(const float dt, InputListener& listener, SFXHandler& handler) {
	
	rect.x -= speed * 1 / dt;
	secondRect.x -= speed * 1 / dt;

	if(rect.x + rect.w < 0) {
		rect.x = secondRect.x + secondRect.w;
	}

	else if (secondRect.x + secondRect.w < 0) {
		secondRect.x = rect.x + rect.w;
	}

}

void ParallaxBackground::initialize(const float width, const float height) {
	Object::initialize(width,0,width,height);

	secondRect.x = 0;
	secondRect.y = 0;
	secondRect.w = width;
	secondRect.h = height;
}


void ParallaxBackground::draw(SDL_Renderer* renderer) const {
	SDL_RenderCopyF(renderer, Utilities::backgroundTexture, NULL, &rect);
	SDL_RenderCopyF(renderer, Utilities::backgroundTexture, NULL, &secondRect);
}