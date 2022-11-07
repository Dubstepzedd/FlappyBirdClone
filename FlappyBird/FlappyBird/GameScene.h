#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Pipe.h"
#include "Bird.h"
#include "ParallaxBackground.h"
#include <vector>
#include "DynamicText.h"
#include "Utilities.h"

class GameScene final : public Scene {

	public:
		GameScene();
		~GameScene();

		virtual void init(SDL_Renderer* renderer) override;
		virtual void update(const float dt, KeyListener& listener, SFXHandler& handler, SDL_Renderer* renderer) override;
		virtual void draw(SDL_Renderer* renderer) override;
	private:

		bool isColliding();

		//Variables
		static constexpr int MIN_HEIGHT = 100;
		static constexpr int GAP = 450;
		static constexpr float COOLDOWN = 3000;

		float timer = 0;
		int score = 0;
		Bird* bird = nullptr;
		ParallaxBackground* background = nullptr;
		DynamicText font;
		std::vector<std::pair<Pipe*, Pipe*>> pipes;
};
#endif
