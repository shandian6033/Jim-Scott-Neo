#ifndef BOARD_H
#define BOARD_H
#include "observer.h"
#include "cell.h"
#include <iostream>

//class TextDisplay;
class Observer;

class Board :public Observer{
	std::vector<std::vector<Cell>> theBoard;
	//TextDisplay *td = nullptr;
	Observer *display = nullptr;
public:
	void init();
	bool isOver() const;
	void newBlock(int level);
	void movement(std::string direction);
	void notify(Subject &whoFrom) override;

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif // !BOARD_H
