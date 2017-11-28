#ifndef BOARD_H
#define BOARD_H
#include "cell.h"
#include "block.h"
#include "textdisplay.h"
#include <iostream>

//class TextDisplay;
class Observer;

class Board{
	std::vector<std::vector<Cell>> the_board;
	std::unique_ptr<Block> my_block;
	TextDisplay *td = nullptr;
	std::unique_ptr<Observer> display;
public:
	void init(int row, int col);
	bool isOver() const;
	void newBlock(int level);
	void movement(std::string direction);

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif // !BOARD_H
