#ifndef PIPE_H
#define PIPE_H
#include "Object.h"
#include "Bird.h"
#include <SDL.h>

class Pipe final : public Object {
	
	public:
		Pipe(const float x, const float y, const bool isRotated, SDL_Renderer* renderer);

		bool isColliding(const Bird* bird);

		virtual void update(const float dt, KeyListener& listener, SFXHandler& handler) override;

		virtual void draw(SDL_Renderer* renderer) const override;

		bool isOutside() const;

		float getX() const {
			return rect.x;
		}

		bool hasPassed(const Bird* bird);

		static constexpr float PIPE_WIDTH = 250.0f / 3;
		static constexpr float PIPE_HEIGHT = 2000.0f / 3;
	private:
		bool passed = false;
		static constexpr float SPEED = 50;
		float rotation = 0;
		SDL_FPoint center;
		

};

#endif
