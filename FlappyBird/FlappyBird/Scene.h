#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include "KeyListener.h"
#include "SFXHandler.h"

class Scene {
	
	public:
		Scene(const std::string tag);
		~Scene();
		
		//Abstract
		virtual void init(SDL_Renderer* renderer) = 0;
		virtual void update(const float dt, KeyListener& listener, SFXHandler& handler, SDL_Renderer* renderer) = 0;
		virtual void draw(SDL_Renderer* renderer) = 0;
		

		std::string getTag() const;

	protected:
		std::string sceneTag;
};

#endif