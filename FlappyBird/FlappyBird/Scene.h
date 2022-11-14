#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include "InputListener.h"
#include "SFXHandler.h"

class Scene {
	
	public:
		Scene(const std::string tag);
		virtual ~Scene();
		
		//Abstract
		virtual void init();
		virtual void update(const float dt, InputListener& listener, SFXHandler& handler) = 0;
		virtual void draw(SDL_Renderer* renderer) = 0;
		

		std::string getTag() const;

	protected:
		std::string sceneTag;
};

#endif