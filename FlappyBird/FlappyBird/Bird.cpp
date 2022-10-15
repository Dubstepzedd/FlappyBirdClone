#include "Bird.h"
#include <SDL.h>

Bird::Bird(const float x, const float y, SDL_Renderer* renderer) : Object(x, y, 50, 50, "bird.png", renderer) {
    rotation = 0;
    cooldown = 500;
    timer = cooldown;
    acceleration = 1.0f;
    gravity = 100.0f;

    center = SDL_FPoint();
    center.x = 25;
    center.y = 25;
}

//DRY Appears Below. Fix?
Bird::Bird(const Bird& other) : Object(other) {
    copy(other);
}

//Does not work for pointers. Use clone() instead.
Bird& Bird::operator=(const Bird& other) {
    this->texture = other.texture;
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
    SDL_RenderCopyExF(renderer, texture, NULL, &rect,rotation,&center,SDL_FLIP_NONE);
   
}

void Bird::update(const float dt, KeyListener& listener) {
    timer += dt;

    //The rotation will not get above 180 degrees so there is no need for us to check it.
    rotation += 0.75f;

    rect.y += gravity * acceleration * 1 / dt;


    if (listener.isKeyPressed(SDLK_SPACE) && timer >= cooldown) {
        timer = 0.0f;
        acceleration = -3.0f;
        rotation = 0.0f;
    }

    if (acceleration <= 3.0f) {
        acceleration += 0.1f;
    }
    
}

Bird* Bird::clone() const {
    return new Bird(*this);
}