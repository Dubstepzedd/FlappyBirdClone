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

		void virtual update(const float dt, KeyListener& listener, SFXHandler& sfxHandler) override;

		float getX() const {
			return rect.x;
		}

		float getY() const {
			return rect.y;
		}


	private:
		void copy(const Bird& other);

		float cooldown;
		float timer = cooldown;
		float acceleration;
		float gravity;
		float rotation;
		SDL_FPoint center;

};
#endif
