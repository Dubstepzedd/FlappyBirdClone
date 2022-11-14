#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include "InputListener.h"
#include <string>
#include "DynamicText.h"
#include "ActionListener.h"
#include "SFXHandler.h"

class Button {

public:
	
	void setContent(const std::string& text, const float width, const float height, const int fontHeight, const SDL_Color& color);

	void draw(SDL_Renderer* renderer);

	void update(const float dt, InputListener& listener, SFXHandler& handler);

	void setFill(const bool isFill);

	void setBoundsColor(const SDL_Color& color);
	
	void setActionListener(ActionListener* listener);
	
	void setPosition(const float x, const float y);

	void getDimensions(int& w, int& h);

private:
	static constexpr float COOLDOWN = 1000.0;
	float time;
	ActionListener* actionListener = nullptr;
	SDL_FRect bounds;
	std::string text;
	int fontH, fontW;
	DynamicText font;
	SDL_Color color;
	SDL_Color boundsColor;
	bool isFill;
	
};

#endif
