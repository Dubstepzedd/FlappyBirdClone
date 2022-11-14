#ifndef ACTIONLISTENER_H
#define ACTIONLISTENER_H

class ActionListener {

public:
	virtual void onEvent(const std::string text) = 0;
};
#endif
