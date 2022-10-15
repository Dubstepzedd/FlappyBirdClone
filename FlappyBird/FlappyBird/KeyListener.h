#ifndef KEYLISTENER_H
#define KEYLISTENER_H
#include <SDL.h>

class KeyListener final
{	//TODO Fix documentation.
	public:
		KeyListener();

		void listen();

		bool isRunning() {
			return running;
		}

		bool isKeyPressed(const int key) {
			return keys[key];
		}

		void setIsRunning(const bool value) {
			running = value;
		}

	private:
		bool keys[322];
		bool running;

};


#endif
