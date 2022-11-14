#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H
#include <SDL.h>

class InputListener final
{	//TODO Fix documentation.
	public:
		InputListener();

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

		bool isButtonDown(const int button);

		float getX();
		float getY();


	private:
		bool keys[322];
		bool running;
		bool buttons[6];
		float x, y;

};


#endif
