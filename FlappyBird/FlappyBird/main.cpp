#include <iostream>
#include <SDL.h>
#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "InputListener.h"
#include "ScoreScene.h"

//TODO LIST

//1. Clean up (ta bort pointers som inte behövs, gör som i DynamicText).


//END OF TODO LIST.
constexpr double FPS = 60;

int main(int argc, char* argv[]) {

    //Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
   
    SDL_Window* window = SDL_CreateWindow("Flappy Bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Utilities::WIDTH, Utilities::HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SceneManager* manager = SceneManager::getInstance();
    manager->addScene(new GameScene());
    manager->addScene(new MenuScene());
    manager->addScene(new ScoreScene());

    //Set the start scene to the menu scene.
    manager->setScene("MENU");

    Scene* scene = manager->getScene();
    scene->init();
    


    InputListener listener = InputListener();
    SFXHandler handler = SFXHandler();
    
    //Load all SFX.
    handler.loadSfx("sfx/sfx_wing.wav", "wing");
    handler.loadSfx("sfx/sfx_point.wav", "point");
    handler.loadSfx("sfx/sfx_hit.wav", "hit");
    handler.loadSfx("sfx/sfx_swooshing.wav", "click");

    Utilities::initialize(renderer);

    Uint64 newTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    float delta = 0;

    while (listener.isRunning()) {
  
        lastTime = newTime;
        newTime = SDL_GetPerformanceCounter();
        delta += (float) ((newTime - lastTime) * 1000.0) / SDL_GetPerformanceFrequency();
        
            while(delta >= 1000.0 / FPS) {
                Scene* scene = manager->getScene();

                listener.listen();
                scene->update(delta, listener, handler);
                scene->draw(renderer);
                delta = 0;
                
            }

        SDL_Delay(1);
    }

    //Free the memory.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


	return 0;
}


