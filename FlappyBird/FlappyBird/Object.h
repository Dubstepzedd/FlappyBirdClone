#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <iostream>
#include "KeyListener.h"

class Object {
	//TODO Fix documentation.
	public:
		
		Object(const float x, const float y, const float width, const float height, const std::string path, SDL_Renderer* renderer);

		Object(const Object& other);

		virtual ~Object();

		Object& operator=(const Object& other);

		void virtual draw(SDL_Renderer* renderer) const;

		void virtual update(const float dt, KeyListener& listener);

		void virtual initialize();

		virtual Object* clone() const;

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
		SDL_Texture* texture;
		SDL_FRect rect;
		SDL_Surface* surface;
};

#endif