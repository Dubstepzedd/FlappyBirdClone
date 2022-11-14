#include "Button.h"

void Button::setContent(const std::string& text, const float width, const float height, const int fontHeight, const
	SDL_Color& color) {
	bounds.w = width;
	bounds.h = height;
	bounds.x = 0;
	bounds.y = 0;
	this->color = color;
	this->text = text;
	time = COOLDOWN;
	//Default values.
	boundsColor = { 0,0,0 };
	isFill = false;

	font.init(fontHeight, "fonts/SHPinscher-Regular.otf");
	font.getDimenions(text, fontW, fontH);
}

void Button::setPosition(const float x, const float y) {
	bounds.x = x;
	bounds.y = y;
}

void Button::draw(SDL_Renderer* renderer) {
	SDL_Color prevColor = SDL_Color();
	SDL_GetRenderDrawColor(renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);

	SDL_SetRenderDrawColor(renderer, boundsColor.r, boundsColor.g, boundsColor.b, boundsColor.a);

	if (isFill)
		SDL_RenderFillRectF(renderer, &bounds);
	else
		SDL_RenderDrawRectF(renderer, &bounds);

	font.drawText(renderer, bounds.x + bounds.w / 2 - fontW / 2, bounds.y + bounds.h / 2 - fontH / 2, text, color);

	SDL_SetRenderDrawColor(renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void Button::update(const float dt,  InputListener& listener, SFXHandler& handler) {
	
	time += dt;

	float x = listener.getX();
	float y = listener.getY();

	if (time >= COOLDOWN && x > bounds.x && x < bounds.x + bounds.w && y > bounds.y && y < bounds.y + bounds.h && listener.isButtonDown(SDL_BUTTON_LEFT)) {
		actionListener->onEvent(text);
		handler.playSfx("click");
		time = 0;
	}
}

void Button::setActionListener(ActionListener* listener) {
	actionListener = listener;
}

void Button::setFill(const bool isFill) {
	this->isFill = isFill;
}

void Button::setBoundsColor(const SDL_Color& color) {
	boundsColor = color;
}

void Button::getDimensions(int& w, int& h) {
	w = bounds.w;
	h = bounds.h;
}