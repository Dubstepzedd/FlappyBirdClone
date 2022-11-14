#include "ActionListener.h"
#include <iostream>

void ActionListener::onEvent() {
	std::cout << "onEvent()" << std::endl;
}