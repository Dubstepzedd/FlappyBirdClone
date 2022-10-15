#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "KeyListener.h"
#include "Bird.h"
#include "ParallaxBackground.h"

const static double FPS = 60;
Bird* bird;
ParallaxBackground* background;

const static int WIDTH = 1000;
const static int HEIGHT = 1000;

bool isColliding() {

    if (bird->getY() < 0 || bird->getY() > HEIGHT) {
        return true;
    }

    return false;
}

void update(const float dt, KeyListener& listener) {
   
    listener.listen();
    bird->update(dt,listener);
    background->update(dt, listener);

    
    if (isColliding()) {
        //TODO This is kind of stupid.
        listener.setIsRunning(false);
    }
    
    //TODO Check collision
}   

void render(SDL_Renderer* renderer) {

    SDL_RenderClear(renderer);

    background->draw(renderer);
    bird->draw(renderer);
    
    SDL_RenderPresent(renderer);
}

void init(SDL_Renderer* renderer) {
   
    //Check memory leaks using Object.
    bird = new Bird(75, 50, renderer);
    background = new  ParallaxBackground(WIDTH, HEIGHT, renderer);


}

int main(int argc, char* argv[]) {
    
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Flappy Bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    init(renderer);

    KeyListener listener = KeyListener();

    Uint64 newTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    double delta = 0;

    while (listener.isRunning()) {
  
        lastTime = newTime;
        newTime = SDL_GetPerformanceCounter();
        delta += ((newTime - lastTime) * 1000.0) / SDL_GetPerformanceFrequency();
        
            while(delta >= 1000.0 / FPS) {

                update(delta,listener);
                render(renderer);
                delta = 0;
                
            }

    }

    //Free the memory.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete bird;
    delete background;

	return 0;
}


