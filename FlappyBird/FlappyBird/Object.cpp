#include "Object.h"
#include <iostream>
#include <SDL_image.h>

Object::Object(const float x, const float y, const float width, const float height, const std::string path, SDL_Renderer* renderer) {

    surface = IMG_Load(path.c_str());

    if (surface == nullptr) {
        throw std::invalid_argument("The given path is not correct.");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect.w = width;
    rect.h = height;
    rect.x = x;
    rect.y = y;
};

//DRY Appears Below. Fix?
Object::Object(const Object& other) {
    SDL_DestroyTexture(texture);
    this->texture = other.texture;
    this->rect = other.rect;
    SDL_FreeSurface(surface);
    this->surface = other.surface;
}

//Does not work for pointers. Use clone() instead.
Object& Object::operator=(const Object& other) {
    SDL_DestroyTexture(texture);
    this->texture = other.texture;
    this->rect = other.rect;
    SDL_FreeSurface(surface);
    this->surface = other.surface;

    return *this;
}

Object::~Object() {

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Object::draw(SDL_Renderer* renderer) const {

    SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

void Object::update(const float dt, KeyListener& listener) {

}

void Object::initialize() {
    
}

Object* Object::clone() const {
	return new Object(*this);
}