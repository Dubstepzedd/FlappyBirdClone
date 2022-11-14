#include "GameScene.h"

GameScene::GameScene() : Scene("GAME") {
    bird = Bird();
    background = ParallaxBackground();
    DynamicText font = DynamicText();
}

bool GameScene::isColliding() {

    if (bird.getY() < 0 || bird.getY() > Utilities::HEIGHT) {
        return true;
    }
    return false;
}

void GameScene::update(const float dt, InputListener& listener, SFXHandler& handler) {

    timer += dt;

    if (timer > COOLDOWN) {
        timer = 0;

        //rand() % expression has a bias, but this clone does not need "realistic" probability.
        float topHeight = (float)(MIN_HEIGHT + rand() % ((Utilities::HEIGHT - MIN_HEIGHT) / 2));
        float topY = -Pipe::PIPE_HEIGHT + topHeight;
        float bottomY = topHeight + GAP;

        Pipe* topPipe = new Pipe();
        topPipe->initialize(Utilities::WIDTH, topY, true);

        Pipe* bottomPipe = new Pipe();
        bottomPipe->initialize(Utilities::WIDTH, bottomY, false);

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
            
            handler.playSfx("hit");
            killPlayer();
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

        killPlayer();
       
    }

    bird.update(dt, listener, handler);
    background.update(dt, listener, handler);

}
void GameScene::killPlayer() {
    SceneManager* manager = SceneManager::getInstance();
    manager->setScene("SCORE");
    ScoreScene* scoreScene = (ScoreScene*)manager->getScene();
    scoreScene->init(score);

    reset();
}

void GameScene::reset() {
    bird = Bird();
    background = ParallaxBackground();

    for (auto it = pipes.begin(); it < pipes.end();) {
        
        delete it->first;
        delete it->second;

        it = pipes.erase(it);
    }
}

void GameScene::draw(SDL_Renderer* renderer)  {

    SDL_RenderClear(renderer);

    background.draw(renderer);
    for (std::pair<Pipe*, Pipe*> pair : pipes) {

        pair.first->draw(renderer);
        pair.second->draw(renderer);
    }

    bird.draw(renderer);

    font.drawText(renderer, 10, 0, "Score: " + std::to_string(score), { 255,255,255 });

    SDL_RenderPresent(renderer);
}

void GameScene::init() {
    score = 0;
    timer = 0;
    bird.initialize(75, Utilities::HEIGHT / 2 - 50, 50, 50);
    background.initialize(Utilities::WIDTH, Utilities::HEIGHT);
    font.init(45, "fonts/SHPinscher-Regular.otf");
 

}