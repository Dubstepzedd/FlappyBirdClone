#ifndef PARALLAXBACKGROUND_H
#define PARALLAXBACKGROUND_H

#include "Object.h"

class ParallaxBackground final : public Object {

	public:
		ParallaxBackground();

		void virtual update(const float dt, InputListener& listener, SFXHandler& handler) override;

		void virtual draw(SDL_Renderer* renderer) const override;

		void virtual initialize(const float width, const float height);

	private:
		float speed;
		SDL_FRect secondRect;
};

#endif
