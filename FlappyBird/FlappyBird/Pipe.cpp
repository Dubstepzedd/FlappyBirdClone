#include "Pipe.h"


bool Pipe::isColliding(const Bird& bird) {
	SDL_FRect birdRect = bird.getRect();

	float left = birdRect.x - (rect.x + rect.w);
	float top = (birdRect.y + birdRect.h) - rect.y;
	float right = (birdRect.x + birdRect.w) - rect.x;
	float bottom = birdRect.y - (rect.y + rect.h);

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);

}

void Pipe::update(const float dt, InputListener& listener, SFXHandler& handler) {

	rect.x -= Pipe::SPEED * 1 / dt;
}

bool Pipe::isOutside() const {
	return rect.x + Pipe::PIPE_WIDTH < 0;
}

void Pipe::draw(SDL_Renderer* renderer) const {
	
	//TODO Fix stretch issue.
	SDL_RenderCopyExF(renderer, Utilities::pipeTexture, NULL, &rect, rotation, &center, SDL_FLIP_NONE);

	
} 

void Pipe::initialize(const float x, const float y, const bool isRotated) {

	Object::initialize(x, y, Pipe::PIPE_WIDTH, Pipe::PIPE_HEIGHT);

	if (isRotated) {
		rotation = 180; 
	}

	center.x = Pipe::PIPE_WIDTH / 2;
	center.y = Pipe::PIPE_HEIGHT / 2;
}

bool Pipe::hasPassed(const Bird& bird) {
	if (!passed && bird.getX() > rect.x + rect.w) {
		passed = true;
		return true;
	}

	return false;
}