#include "SFXHandler.h"


SFXHandler::SFXHandler() {

    //Initialize SDL_Mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("SDL2_mixer could not be initialized!\n"
            "SDL_Error: %s\n", SDL_GetError());
    }
}

SFXHandler::~SFXHandler() {
    //Deallocate the memory.
    std::map<std::string, Mix_Chunk*>::iterator it;
    for (it = sounds.begin(); it != sounds.end(); it++) {
        Mix_FreeChunk(it->second);

    }

    Mix_CloseAudio();
}

void SFXHandler::loadSfx(const std::string path, const std::string tag) {
    Mix_Chunk* sfx = Mix_LoadWAV(path.c_str());

    if (!sfx) {
        //TODO Improve.
        std::cout << ".WAV sound at" << path << " could not be loaded." << std::endl;

        throw std::invalid_argument(".WAV sound could not be loaded.");
        return;
    }

    sounds[tag] = sfx;

}

int SFXHandler::playSfx(const std::string tag) {

    if (sounds.find(tag) == sounds.end()) {
        throw std::invalid_argument("Tag is invalid. Sound was not found.");

    }

    return Mix_PlayChannel(-1, sounds[tag], 0);

}


