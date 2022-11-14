#include "Bird.h"

Bird::Bird() {

}

Bird::Bird(const Bird& other) : Object(other) {
    copy(other);
}

//Does not work for pointers. Use clone() instead.
Bird& Bird::operator=(const Bird& other) {
    this->rect = other.rect;

    copy(other);

    return *this;
}

void Bird::copy(const Bird& other) {
    this->rotation = other.rotation;
    this->cooldown = other.cooldown;
    this->timer = other.timer;
    this->acceleration = other.acceleration;
    this->gravity = other.gravity;
    this->center = other.center;
}

void Bird::draw(SDL_Renderer* renderer) const  {
    SDL_RenderCopyExF(renderer, Utilities::birdTexture, NULL, &rect,rotation,&center,SDL_FLIP_NONE);
   
}

void Bird::update(const float dt, InputListener& listener, SFXHandler& handler) {
    timer += dt;

    //The rotation will not get above 180 degrees so there is no need for us to check it.
    rotation += 0.75f;

    rect.y += gravity * acceleration * 1 / dt;


    if (listener.isKeyPressed(SDLK_SPACE) && timer >= cooldown) {
        timer = 0.0f;
        acceleration = -3.0f;
        rotation = 0.0f;
        handler.playSfx("wing");
    }

    if (acceleration <= 3.0f) {
        acceleration += 0.1f;
    }
    
}

void Bird::initialize(const float x, const float y, const float width, const float height) {
    
    Object::initialize(x, y, width, height);

    rotation = 0;
    cooldown = 400;
    timer = cooldown;
    acceleration = 1.0f;
    gravity = 100.0f;

    center = SDL_FPoint();
    center.x = 25;
    center.y = 25;
}

Bird* Bird::clone() const {
    return new Bird(*this);
}