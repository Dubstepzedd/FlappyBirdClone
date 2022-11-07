#include "GameScene.h"


GameScene::GameScene() : Scene("GAME") {
    DynamicText font = DynamicText();
}

GameScene::~GameScene() {
    delete bird;
    delete background;

    for (std::pair<Pipe*, Pipe*> pair : pipes) {
        delete pair.first;
        delete pair.second;
    }
}


bool GameScene::isColliding() {

    if (bird->getY() < 0 || bird->getY() > HEIGHT) {
        return true;
    }

    return false;
}

void GameScene::update(const float dt, KeyListener& listener, SFXHandler& handler, SDL_Renderer* renderer) {

    timer += dt;

    listener.listen();

    if (timer > COOLDOWN) {
        timer = 0;

        //rand() % expression has a bias, but this clone does not need "realistic" probability.
        float topHeight = (float)(MIN_HEIGHT + rand() % ((HEIGHT - MIN_HEIGHT) / 2));
        float topY = -Pipe::PIPE_HEIGHT + topHeight;
        float bottomY = topHeight + GAP;

        Pipe* topPipe = new Pipe(WIDTH, topY, true, renderer);
        Pipe* bottomPipe = new Pipe(WIDTH, bottomY, false, renderer);
        std::pair<Pipe*, Pipe*> pipePair = std::make_pair(topPipe, bottomPipe);
        pipes.push_back(pipePair);
    }

    for (auto it = pipes.begin(); it < pipes.end();) {
        std::pair<Pipe*, Pipe*> pipePair = *it;

        //TODO This is dumb. Pipe and ParallaxBackground do not need listener and handler?
        pipePair.first->update(dt, listener, handler);
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

    bird->update(dt, listener, handler);
    background->update(dt, listener, handler);

}

void GameScene::draw(SDL_Renderer* renderer)  {

    SDL_RenderClear(renderer);

    background->draw(renderer);
    for (std::pair<Pipe*, Pipe*> pair : pipes) {

        pair.first->draw(renderer);
        pair.second->draw(renderer);
    }

    bird->draw(renderer);

    font.drawText(renderer, 10, 0, "Score: " + std::to_string(score), { 255,255,255 });

    SDL_RenderPresent(renderer);
}

void  GameScene::init(SDL_Renderer* renderer) {

    //Check memory leaks using Object.
    bird = new Bird(75, 50, renderer);
    background = new ParallaxBackground(WIDTH, HEIGHT, renderer);
    font.init(45, "fonts/SHPinscher-Regular.otf");
 

}