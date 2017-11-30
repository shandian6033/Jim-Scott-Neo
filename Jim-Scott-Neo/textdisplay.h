#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "info.h"
#include <vector>
#include <iostream>
class Board;

class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	const int length, width;
	const Board* my_board;
public:
	TextDisplay(int width, int length, const Board& my_board);

	void notify(Subject &whoFrom) override;
	void clear();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif // !TEXTDISPLAY_H

