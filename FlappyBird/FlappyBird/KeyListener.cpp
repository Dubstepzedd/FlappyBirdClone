#include "KeyListener.h"
#include <iostream>

KeyListener::KeyListener() {
    for (unsigned i = 0; i < sizeof(keys) / sizeof(bool); i++) {
        keys[i] = false;
    }

    running = true;

}
void KeyListener::listen() {
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
        }
    }

}
