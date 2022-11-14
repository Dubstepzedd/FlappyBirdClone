#ifndef PIPE_H
#define PIPE_H
#include "Object.h"
#include "Bird.h"
#include <SDL.h>
#include "Utilities.h"

class Pipe final : public Object {
	
	public:

		bool isColliding(const Bird& bird);

		virtual void update(const float dt, InputListener& listener, SFXHandler& handler) override;

		virtual void draw(SDL_Renderer* renderer) const override;

		virtual void initialize(const float x, const float y, const bool isRotated);

		bool isOutside() const;

		float getX() const {
			return rect.x;
		}

		bool hasPassed(const Bird& bird);

		static constexpr float PIPE_WIDTH = 250.0f / 3;
		static constexpr float PIPE_HEIGHT = 2000.0f / 3;
	private:
		bool passed = false;
		static constexpr float SPEED = 50;
		float rotation = 0;
		SDL_FPoint center;
		

};

#endif
