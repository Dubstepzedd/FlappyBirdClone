#include "ScoreScene.h"


ScoreScene::ScoreScene() : Scene("SCORE") {
	bigFont = DynamicText();
	smallFont = DynamicText();
	totalScore = 0;
}

void ScoreScene::init(const int score) {
	totalScore = score;
	background = ParallaxBackground();
	background.initialize(Utilities::WIDTH, Utilities::HEIGHT);

	bigFont.init(96, "fonts/SHPinscher-Regular.otf");
	smallFont.init(64, "fonts/SHPinscher-Regular.otf");
	setBtnContent(retryBtn, "RETRY", 1);
	setBtnContent(backBtn, "BACK", 2);
}	

void ScoreScene::setBtnContent(Button& btn, std::string&& text, const int yStep) {
	btn.setContent(text, 200, 50, 50, { 255,255,255 });
	btn.setFill(true);
	btn.setActionListener(this);
	int w = 0, h = 0;
	btn.getDimensions(w, h);
	btn.setPosition(Utilities::WIDTH / 2 - w / 2, Utilities::HEIGHT / 2 - h / 2 + yStep * 75);
}

void ScoreScene::update(const float dt, InputListener& listener, SFXHandler& handler) {
	background.update(dt, listener, handler);
	retryBtn.update(dt, listener, handler);
	backBtn.update(dt, listener, handler);
}

void ScoreScene::draw(SDL_Renderer* renderer) {
	background.draw(renderer);

	//Draw "GAME OVER" text 
	std::string text = "GAME OVER";
	int w = 0, h = 0;
	bigFont.getDimenions(text, w, h);
	SDL_Color color = { 0,0,0 };
	bigFont.drawText(renderer, Utilities::WIDTH / 2 - w / 2, Utilities::HEIGHT / 3 - h / 2, text, color);
	
	//Draw total score text
	text = "SCORE: " + std::to_string(totalScore);
	int h2 = 0;
	smallFont.getDimenions(text, w, h2);
	smallFont.drawText(renderer, Utilities::WIDTH / 2 - w / 2, Utilities::HEIGHT / 3 - h2 / 2 + h, text, color);
	
	//Draw the buttons.
	retryBtn.draw(renderer);
	backBtn.draw(renderer);
	
	SDL_RenderPresent(renderer);
}

void ScoreScene::onEvent(const std::string text) {
	//TODO Fix Id as parameter here.
	SceneManager* manager = SceneManager::getInstance();
	if (text == "RETRY") {
		manager->setScene("GAME");
	}
	else
		manager->setScene("MENU");

	manager->getScene()->init();
}