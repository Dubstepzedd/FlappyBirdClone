#ifndef PARALLAXBACKGROUND_H
#define PARALLAXBACKGROUND_H

#include "Object.h"

class ParallaxBackground : public Object {

	public:
		ParallaxBackground(const float width, const float height, SDL_Renderer* renderer);

		void virtual update(const float dt, KeyListener& listener) override;

		void virtual draw(SDL_Renderer* renderer) const override;

	private:
		float speed;
		SDL_FRect secondRect;
};

#endif
