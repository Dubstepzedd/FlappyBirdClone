#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <iostream>
#include "InputListener.h"
#include "SFXHandler.h"
#include "Utilities.h"

class Object {
	//TODO Fix documentation.
	public:
		
		Object();

		Object(const Object& other);

		virtual ~Object();

		Object& operator=(const Object& other);

		void virtual draw(SDL_Renderer* renderer) const = 0;

		void virtual update(const float dt, InputListener& listener, SFXHandler& handler) = 0;

		void virtual initialize(const float x, const float y, const float width, const float height);

		void setPosition(const float x, const float y) {
			rect.x = x;
			rect.y = y;
		}

		void setRect(const float x, const float y, const float w, const float h) {
			setPosition(x, y);
			rect.w = w;
			rect.h = h;
		}

		SDL_FRect getRect() const {
			return rect;
		}


	protected:
		SDL_FRect rect;
};

#endif