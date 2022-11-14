#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Pipe.h"
#include "Bird.h"
#include "ParallaxBackground.h"
#include <vector>
#include "DynamicText.h"
#include "Utilities.h"
#include "SceneManager.h"
#include "ScoreScene.h"

class GameScene final : public Scene {

	public:
		GameScene();

		virtual void init() override;
		virtual void update(const float dt, InputListener& listener, SFXHandler& handler) override;
		virtual void draw(SDL_Renderer* renderer) override;
		void killPlayer();

	private:
		void reset();
		bool isColliding();

		//Variables
		static constexpr int MIN_HEIGHT = 100;
		static constexpr int GAP = 450;
		static constexpr float COOLDOWN = 3000;

		float timer;
		int score;
		Bird bird;
		ParallaxBackground background;
		DynamicText font;
		std::vector<std::pair<Pipe*, Pipe*>> pipes;
};
#endif
