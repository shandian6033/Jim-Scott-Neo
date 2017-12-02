#ifndef BOARD_H
#define BOARD_H
#include "cell.h"
#include "block.h"
#include "textdisplay.h"
#include <iostream>
#include <fstream>
#include <sstream>

//class TextDisplay;
class Observer;

class Board{
	int length, width;
    int score, level, hi_score;
	int is_slow;
	int lifetime;//for lv5

	std::vector<std::vector<Cell>> the_board;
    std::vector<Cell> horizontal_place_holders; //row -1,only used for IBlock
    std::vector<Cell> vertical_place_holders; //col -1, anchor can go out of the board
	unique_ptr<Block> cur_block;
	WhoIam next_block;

	TextDisplay td{ 11,15,*this };//this may lost
	std::unique_ptr<Observer> display;

	ifstream sequence;


public:
	bool not_over;

	CmdList changable_cmd;
	void init(int row, int col);
	void restart();
	void computeNextBlock();//set next_block
	void setCur(); //return false if no Block can be generated. Then game should be over.
	void movement(std::string valid_cmd);

	int getLevel()const;
	int getScore()const;
	int getHi()const;
	WhoIam getNext()const;
	void setLevel(int level);
	bool setSeq(string source);
	void setLife(int lifetime);
	void clearSeq();
	//~Board() = default;

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif // !BOARD_H
