#include "Object.h"
#include <iostream>
#include <SDL_image.h>

Object::Object() {

}


Object::~Object() {
    //Nothing
}

void Object::initialize(const float x, const float y, const float width, const float height) {
    rect.w = width;
    rect.h = height;
    rect.x = x;
    rect.y = y;
}

//DRY Appears Below. Fix?
Object::Object(const Object& other) {
    this->rect = other.rect;
}

//Does not work for pointers. Use clone() instead.
Object& Object::operator=(const Object& other) {
    this->rect = other.rect;

    return *this;
}

