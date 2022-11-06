#ifndef SFXHANDLER_H
#define SFXHANDLER_H
#include <SDL_Mixer.h>
#include <map>
#include <string>
#include <iostream>

class SFXHandler
{
	public:

		SFXHandler();
		~SFXHandler();

		void loadSfx(const std::string path, const std::string tag);
		int playSfx(const std::string tag);
	private:
		//You can add music as well, but in this clone we only need sound effects.
		std::map<std::string, Mix_Chunk*> sounds;

};

#endif

