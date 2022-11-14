#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene() : Scene("MENU") {
	
}

void MenuScene::init() {
	background = ParallaxBackground();
	background.initialize(Utilities::WIDTH, Utilities::HEIGHT);

	bird = Bird();
	bird.initialize(Utilities::WIDTH / 2 - BIRD_WIDTH / 2, Utilities::HEIGHT / 3, BIRD_WIDTH, BIRD_HEIGHT);
	
	SDL_Color color = { 255,255,255 };
	playBtn.setContent("PLAY", 250, 50, 50, color);

	int x = 0;
	int y = 0;
	playBtn.getDimensions(x, y);
	playBtn.setPosition(Utilities::WIDTH / 2 - x / 2, Utilities::HEIGHT / 2 - y / 2);
	
	playBtn.setFill(true);
	playBtn.setActionListener(this);
}

void MenuScene::draw(SDL_Renderer* renderer) {
	background.draw(renderer);
	bird.draw(renderer);
	playBtn.draw(renderer);
	SDL_RenderPresent(renderer);
}

void MenuScene::update(const float dt, InputListener& listener, SFXHandler& handler) {
	background.update(dt, listener, handler);
	playBtn.update(dt, listener, handler);
	
}

void MenuScene::onEvent(const std::string text) {
	//TODO FIX ID AS PARAMETER.
	SceneManager* manager = SceneManager::getInstance();
	manager->setScene("GAME");
	manager->getScene()->init();
	
}