#ifndef BIRD_H
#define BIRD_H

#include "Object.h"
#include <SDL.h>

class Bird final : public Object {
	//TODO Fix documentation.

	public:
		Bird(const float x, const float y, SDL_Renderer* renderer);

		Bird(const Bird& other);

		Bird& operator=(const Bird& other);

		virtual Bird* clone() const override;

		void virtual draw(SDL_Renderer* renderer) const override;

		void virtual update(const float dt, KeyListener& listener) override;

		void copy(const Bird& other);

		float getX() {
			return rect.x;
		}

		float getY() {
			return rect.y;
		}


	private:
		float cooldown;
		float timer = cooldown;
		float acceleration;
		float gravity;
		float rotation;
		SDL_FPoint center;

};
#endif
