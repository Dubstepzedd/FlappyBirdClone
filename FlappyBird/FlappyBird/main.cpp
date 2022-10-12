#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Object.h"

const static double FPS = 60;
bool isRunning = true;
Object* obj;
Object* obj2;

void pollEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {

            case SDL_QUIT: 
                isRunning = false;
                break;

            default:
                break;
        }
    }
}

void update(const float dt) {
   //Update shit?

    obj2->setRect(100, 100, 100, 100);
    pollEvents();
}


void render(SDL_Renderer* renderer) {

    SDL_RenderClear(renderer);

    obj->draw(renderer);
    obj2->draw(renderer);

    SDL_RenderPresent(renderer);
}

void init(SDL_Renderer* renderer) {
   
    //Check memory leaks using Object.
    obj = new Object(0, 0, 50,50,"test.jpg", renderer);
    obj2 = obj->clone();
    obj2->setRect(100, 100, 100, 100);


}

int main(int argc, char* argv[]) {
    
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    init(renderer);

    Uint64 newTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    double delta = 0;
    
    while (isRunning) {

        lastTime = newTime;
        newTime = SDL_GetPerformanceCounter();
        delta += ((newTime - lastTime) * 1000.0) / SDL_GetPerformanceFrequency();
        
            while(delta >= 1000.0 / FPS) {

                update(delta);
                render(renderer);

                delta -= 1000.0 / FPS;
                
            }

    }

    //Free the memory.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    delete obj;
    delete obj2;

	return 0;
}


