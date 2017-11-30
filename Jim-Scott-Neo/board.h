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
	Block cur_block;
	Block next_block;

	TextDisplay td{ 11,15 };//this may lost
	std::unique_ptr<Observer> display;

	int score, level, hi_score;

public:
	CmdList changable_cmd;
	void init(int row, int col);
	//bool isOver() const;
	bool newBlock(int level); //return false if no Block can be generated. Then game should be over.
	void movement(std::string valid_cmd);

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif // !BOARD_H
