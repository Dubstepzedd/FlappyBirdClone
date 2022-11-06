#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "KeyListener.h"
#include "Bird.h"
#include "ParallaxBackground.h"
#include <vector>
#include "Pipe.h"
#include <SDL_ttf.h>
#include "DynamicText.h"
#include <SDL_mixer.h>
#include "SFXHandler.h"

//TODO LIST

//2. Implement UI. Make a menu. It should have a "Play" button that starts the actual game.

//3. The player should see a defeat screen when losing that shows the score and two buttons. One button says "Retry" and will, when pressed,
//   restart the game. The other button says "Exit" and will, when pressed, close the game.


//4. Improve Bird animations.

//5. Clean up (ta bort pointers som inte behövs, gör som i DynamicText).

//END OF TODO LIST.


//Variables known/available at compile-time.
constexpr double FPS = 60;
constexpr int MIN_HEIGHT = 100;
constexpr int GAP = 450;
constexpr float COOLDOWN = 3000;
constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

//Defined at runtime.
float timer = 0;
int score = 0;
Bird* bird;
ParallaxBackground* background;
DynamicText font;
SFXHandler handler; 

std::vector<std::pair<Pipe*,Pipe*>> pipes;


bool isColliding() {

    if (bird->getY() < 0 || bird->getY() > HEIGHT) {
        return true;
    }

    return false;
}

void update(const float dt, KeyListener& listener, SDL_Renderer* renderer) {
    
    timer += dt;

    listener.listen();

    if (timer > COOLDOWN) {
        timer = 0;
     
        //rand() % expression has a bias, but this clone does not need "realistic" probability.
        float topHeight = (float)(MIN_HEIGHT + rand() % ((HEIGHT- MIN_HEIGHT) / 2));
        float topY = -Pipe::PIPE_HEIGHT + topHeight;
        float bottomY = topHeight + GAP;

        Pipe* topPipe = new Pipe(WIDTH, topY, true, renderer);
        Pipe* bottomPipe = new Pipe(WIDTH, bottomY, false, renderer);
        std::pair<Pipe*, Pipe*> pipePair = std::make_pair(topPipe,bottomPipe);
        pipes.push_back(pipePair);
    }

    for (auto it = pipes.begin(); it < pipes.end();) {
        std::pair<Pipe*, Pipe*> pipePair = *it;

        //TODO This is dumb. Pipe and ParallaxBackground do not need listener and handler?
        pipePair.first->update(dt, listener,handler);
        pipePair.second->update(dt, listener, handler);


        //--- Check if any of the pipes are colliding with the bird ---//
        if (pipePair.first->isColliding(bird) || pipePair.second->isColliding(bird)) {
            listener.setIsRunning(false);
            handler.playSfx("hit");
            return;
        }
        //--- Check if the bird has passed the pair of pipes, if so add a point ---//
        if (pipePair.first->hasPassed(bird)) {
            handler.playSfx("point");
            score++;
        }

        //--- Remove the pipes that are outside ---//
        if (pipePair.first->isOutside() && pipePair.second->isOutside()) {
            it = pipes.erase(it);
            
            delete pipePair.first;
            delete pipePair.second;
        }
        else
            //Increment like normally
            it++;
    }

    //--- Collision with the height and bottom of the window ---//
    if (isColliding()) {
        handler.playSfx("hit");
        listener.setIsRunning(false);

    }

    bird->update(dt,listener, handler);
    background->update(dt, listener, handler);


 
}   

void render(SDL_Renderer* renderer) {

    SDL_RenderClear(renderer);

    background->draw(renderer);
    for (std::pair<Pipe*, Pipe*> pair : pipes) {

        pair.first->draw(renderer);
        pair.second->draw(renderer);
    }

    bird->draw(renderer);
    
    font.drawText(renderer, 10, 0, "Score: " + std::to_string(score), {255,255,255});

    SDL_RenderPresent(renderer);
}

void init(SDL_Renderer* renderer) {
   
    //Check memory leaks using Object.
    bird = new Bird(75, 50, renderer);
    background = new ParallaxBackground(WIDTH, HEIGHT, renderer);
    font.init(45, "fonts/SHPinscher-Regular.otf");
    handler.loadSfx("sfx/sfx_wing.wav","wing");
    handler.loadSfx("sfx/sfx_point.wav", "point");
    handler.loadSfx("sfx/sfx_hit.wav", "hit");

}

int main(int argc, char* argv[]) {

    //Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
   

    SDL_Window* window = SDL_CreateWindow("Flappy Bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    

    init(renderer);

    KeyListener listener = KeyListener();

    Uint64 newTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    float delta = 0;

    while (listener.isRunning()) {
  
        lastTime = newTime;
        newTime = SDL_GetPerformanceCounter();
        delta += (float) ((newTime - lastTime) * 1000.0) / SDL_GetPerformanceFrequency();
        
            while(delta >= 1000.0 / FPS) {

                update(delta,listener,renderer);
                render(renderer);
                delta = 0;
                
            }

        SDL_Delay(1);
    }

    //Free the memory.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete bird;
    delete background;

    for (std::pair<Pipe*, Pipe*> pair : pipes) {
        delete pair.first;
        delete pair.second;
    }

	return 0;
}


