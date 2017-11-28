#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "info.h"
#include <vector>
#include <iostream>

class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	const int length, width;
public:
	TextDisplay(int l, int w);

	void notify(Subject &whoFrom) override;

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif // !TEXTDISPLAY_H

