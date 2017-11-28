#ifndef BOARD_H
#define BOARD_H
#include "cell.h"
#include "block.h"
#include <iostream>

//class TextDisplay;
class Observer;

class Board{
	std::vector<std::vector<Cell>> the_board;
	Block* the_block;
	//TextDisplay *td = nullptr;
	Observer *display = nullptr;
public:
	void init();
	bool isOver() const;
	void newBlock(int level);
	void movement(std::string direction);

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif // !BOARD_H
