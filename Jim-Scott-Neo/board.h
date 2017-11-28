#ifndef BOARD_H
#define BOARD_H
#include "observer.h"
#include "cell.h"
#include <string>

//class TextDisplay;
class Observer;

class board :public Observer{
	std::vector<std::vector<Cell>> theBoard;
	//TextDisplay *td = nullptr;
	Observer *display = nullptr;
public:
	void init();
	void newBlock(int level);
	void movement(std::string direction);
	void notify(Subject &whoFrom) override;
};

#endif // !BOARD_H
