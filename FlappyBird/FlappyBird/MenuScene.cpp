#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene() : Scene("MENU") {
	
}

MenuScene::~MenuScene()
{
}

void MenuScene::init() {
	background = ParallaxBackground();
	background.initialize(Utilities::WIDTH, Utilities::HEIGHT);

	bird = Bird();
	bird.initialize(Utilities::WIDTH / 2 - BIRD_WIDTH / 2, Utilities::HEIGHT / 3, BIRD_WIDTH, BIRD_HEIGHT);
	
	SDL_Color color = { 255,255,255 };
	playBtn.setContent("PLAY", 250, 50, 50, color);
	exitBtn.setContent("EXIT", 250, 50, 50, color);
	int gap = 25;
	int playWidth = 0;
	int playHeight = 0;
	playBtn.getDimensions(playWidth, playHeight);
	playBtn.setPosition(Utilities::WIDTH / 2 - playWidth / 2, Utilities::HEIGHT / 2 - playHeight / 2);
	playBtn.setFill(true);
	playBtn.setActionListener(this);

	int exitWidth = 0;
	int exitHeight = 0;
	exitBtn.getDimensions(exitWidth, exitHeight);
	exitBtn.setPosition(Utilities::WIDTH / 2 - exitWidth / 2, Utilities::HEIGHT / 2 - exitHeight / 2 + playHeight + gap);
	exitBtn.setFill(true);
	exitBtn.setActionListener(this);
	
}

void MenuScene::draw(SDL_Renderer* renderer) {
	background.draw(renderer);
	bird.draw(renderer);
	playBtn.draw(renderer);
	exitBtn.draw(renderer);

	SDL_RenderPresent(renderer);
}

void MenuScene::update(const float dt, InputListener& listener, SFXHandler& handler) {
	background.update(dt, listener, handler);
	playBtn.update(dt, listener, handler);
	exitBtn.update(dt, listener, handler);

	if (!isRunning) {
		listener.setIsRunning(false);
	}
	
}

void MenuScene::onEvent(const std::string text) {
	
	SceneManager* manager = SceneManager::getInstance();
	if (text == "PLAY") {
		manager->setScene("GAME");
		manager->getScene()->init();
	}
	else {
		isRunning = false;
	}

}