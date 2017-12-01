#include "board.h"
#include <cstdlib>

void Board::init(int row, int col) {

    length = row;
    width = col;

    the_board.clear();
    for (int r = 0; r < row + 1; r++) { //setup the_board
        std::vector<Cell> new_row;
        for (int c = 0; c < col; c++) {
            new_row.emplace_back(Cell(r, c));
        }
        the_board.emplace_back(new_row);
    }

    for (int c = 0; c < col; c++) { //setup place_hoders
        place_hoders.emplace_back(Cell(-1, c));
    }

    score = 0;
    hi_score = 0;
    td.clear();

    for (int r = 0; r < row; r++) {// setup ptr relationship in the_board
        for (int c = 0; c < col; c++) {
            the_board.at(r).at(c).attach(&td);
            if (r > 0) {
                the_board.at(r).at(c).setUp(the_board.at(r - 1).at(c));
            }
            if (r < row - 1) {
                the_board.at(r).at(c).setDown(the_board.at(r + 1).at(c));
            }
            if (c > 0) {
                the_board.at(r).at(c).setLeft(the_board.at(r).at(c - 1));
            }
            if (c < col - 1) {
                the_board.at(r).at(c).setRight(the_board.at(r).at(c + 1));
            }
        }
    }

    for (int c = 0; c < col; c++) {// setup prt relationship in place_holder
        place_hoders.at(c).setDown(the_board.at(0).at(c));
        if (c > 0) {
            place_hoders.at(c).setLeft(place_hoders.at(c - 1));
        }
        if (c < col - 1) {
            place_hoders.at(c).setRight(place_hoders.at(c + 1));
        }
    }

}

void Board::movement(std::string valid_cmd) {
	if (valid_cmd == changable_cmd.left) {//considering abbreviation
		cur_block.get()->left();
	}
	else if (valid_cmd == changable_cmd.right) {
		cur_block.get()->right();
	}
	else if (valid_cmd == changable_cmd.down) {
		cur_block.get()->down();
	}
	else if (valid_cmd == changable_cmd.rRotate) {
		cur_block.get()->rRotate();
	}
	else if (valid_cmd == changable_cmd.lRotate) {
		cur_block.get()->lRotate();
	}
	else{
		score += cur_block->drop();
		if (score > hi_score) {
			hi_score = score;
		}
		for (int r = 0; r < length; r++) {
			for (int c = 0; c < width; c++) {
				if (the_board.at(r).at(c).getInfo().id != WhoIam::Null) {
					the_board.at(r).at(c).grow();
				}
			}
		}
	}
}

void Board::nextBlock() {
	//cur_block = new LBlock{ &the_board.at(0).at(4) };
	string type;
	if (source >> type) {
		if (type == "L") {
			next_block = WhoIam::L;
		}
		else if (type == "O") {
			next_block = WhoIam::O;
		}
		else if (type == "T") {
			next_block = WhoIam::T;
		}
	}
	else {
		int random = rand() % 36;//random is 0~35
		if (level == 0 || level == 1) {
			if (random < 3) {//[0,2] 3
				next_block = WhoIam::S;
			}
			else if (random < 6) {//[3,5] 3
				next_block = WhoIam::Z;
			}
			else if (random < 12) {//[6,11] 6 
				next_block = WhoIam::L;
			}
			else if (random < 18) {//[11,17] 6
				next_block = WhoIam::J;
			}
			else if (random < 24) {//[18,23] 6
				next_block = WhoIam::O;
			}
			else if (random < 30) {//[24,29] 6
				next_block = WhoIam::I;
			}
			else if (random < 36) {//[30,35] 6
				next_block = WhoIam::T;
			}
		}
	}
}

bool Board::setCur() {
	cur_block = make_unique<IBlock>(level,&place_hoders.at(4));
	nextBlock();
	return cur_block->isSuccessful();
}

int Board::getLevel()const {
	return level;
}

int Board::getScore()const {
	return score;
}

int Board::getHi()const {
	return hi_score;
}

WhoIam Board::getNext()const{
	return next_block;
}

void Board::setLevel(int level) {
	this->level = level;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
	//out << "Level: " << b.level << endl;
	//out << "Score: " << b.score << endl;
	//out << "Hi Score: " << b.hi_score << endl;
	//out << "-----------" << endl; //upper bound, hard code
	out << b.td;
	//out << "-----------" << endl; //lower bound, hard code
	//out << "Next:" << endl;
	//out << *(b.cur_block);
	return out;
}