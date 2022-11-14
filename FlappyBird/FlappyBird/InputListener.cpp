#include "InputListener.h"
#include <iostream>
#include <string>

InputListener::InputListener() {
    for (unsigned i = 0; i < sizeof(keys) / sizeof(bool); i++) {
        keys[i] = false;
    }

    for (unsigned i = 0; i < sizeof(buttons) / sizeof(bool); i++) {
        buttons[i] = false;
    }

    x = 0;
    y = 0;

    running = true;

}

float InputListener::getX() {
    return x;
}

float InputListener::getY() {
    return y;
}

bool InputListener::isButtonDown(const int button) {
    return buttons[button];
}


void InputListener::listen() {
	SDL_Event event;
 
    while (SDL_PollEvent(&event)) {

        switch (event.type) {

            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                keys[event.key.keysym.sym] = true;
                break;

            case SDL_KEYUP:
                keys[event.key.keysym.sym] = false;
                break;

            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                buttons[event.button.button] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                buttons[event.button.button] = false;
                break;
        }
    }

}
