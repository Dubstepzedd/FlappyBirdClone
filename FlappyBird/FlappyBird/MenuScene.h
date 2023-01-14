#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "SceneManager.h"
#include "Scene.h"
#include "ParallaxBackground.h"
#include "Utilities.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Bird.h"
#include "Utilities.h"
#include "Button.h"

class MenuScene final : public Scene, public ActionListener {

public:
	MenuScene();
	~MenuScene();

	virtual void init() override;
	virtual void update(const float dt, InputListener& listener, SFXHandler& handler) override;
	virtual void draw(SDL_Renderer* renderer) override;
	virtual void onEvent(const std::string text) override;

private:
	static constexpr float BIRD_WIDTH = 75;
	static constexpr float BIRD_HEIGHT = 75;
	ParallaxBackground background;
	Bird bird;
	Button playBtn;
	Button exitBtn;
	bool isRunning = true;
	
};

#endif

