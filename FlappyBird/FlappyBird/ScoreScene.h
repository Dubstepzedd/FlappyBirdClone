#ifndef SCORESCENE_H
#define SCORESCENE_H
#include "Scene.h"
#include "ActionListener.h"
#include "Utilities.h"
#include "ParallaxBackground.h"
#include "DynamicText.h"
#include "Button.h"
#include "SceneManager.h"

class ScoreScene final : public Scene, public ActionListener {

public:
	ScoreScene();

	void init(const int score);

	void update(const float dt, InputListener& listener, SFXHandler& handler) override;

	void draw(SDL_Renderer* renderer) override;
	
	void onEvent(const std::string text) override;

	void setBtnContent(Button& btn, std::string&& text, const int yStep);

private:
	int totalScore;
	ParallaxBackground background;
	DynamicText bigFont;
	DynamicText smallFont;

	Button retryBtn;
	Button backBtn;
};
#endif
