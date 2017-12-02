#include <cstdlib>
#include "board.h"
#include "normal_blocks.h"
#include "special_blocks.h"

void Board::init(int row, int col) {
	hi_score = 0;
	width = col;
	length = row;
	setLevel(0);
	is_slow = 0;
	lifetime = 10;
	not_over = true;
}

void Board::restart() {
	not_over = true;
    score = 0;

    the_board.clear();
    horizontal_place_holders.clear();
    vertical_place_holders.clear();

    for (int r = 0; r < length; r++) { //setup the_board
        std::vector<Cell> new_row;
        for (int c = 0; c < width; c++) {
            new_row.emplace_back(Cell(r, c));
        }
        the_board.emplace_back(new_row);
    }

    for (int c = 0; c < width; c++) { //setup row -1
        horizontal_place_holders.emplace_back(Cell(-1, c));
    }

    for (int r = 0; r < length; r++) { //setup col -1
        vertical_place_holders.emplace_back(Cell(r, -1));
    }


    td.clear();
    //gd.clear();

    for (int r = 0; r < length; r++) {// setup ptr relationship in the_board
        for (int c = 0; c < width; c++) {
            the_board.at(r).at(c).attach(&td);
            //the_board.at(r).at(c).attach(&gd);
            if (r > 0) {
                the_board.at(r).at(c).setUp(the_board.at(r - 1).at(c));
            }
            if (r < length - 1) {
                the_board.at(r).at(c).setDown(the_board.at(r + 1).at(c));
            }
            if (c > 0) {
                the_board.at(r).at(c).setLeft(the_board.at(r).at(c - 1));
            }
            else if(c == 0)
            {
                the_board.at(r).at(c).setLeft(vertical_place_holders.at(r));
            }
            if (c < width - 1) {
                the_board.at(r).at(c).setRight(the_board.at(r).at(c + 1));
            }
        }
    }

    for (int c = 0; c < width; c++) {// setup prt relationship in row -1
        horizontal_place_holders.at(c).setPiece(WhoIam::Placeholder,-1);
        horizontal_place_holders.at(c).setDown(the_board.at(0).at(c));
        if (c > 0) {
            horizontal_place_holders.at(c).setLeft(horizontal_place_holders.at(c - 1));
        }
        if (c < width - 1) {
            horizontal_place_holders.at(c).setRight(horizontal_place_holders.at(c + 1));
        }
    }

    for (int r = 0; r < length; r++) {// setup prt relationship in col -1
        vertical_place_holders.at(r).setPiece(WhoIam::Placeholder, -1);
        vertical_place_holders.at(r).setRight(the_board.at(r).at(0));
        if (r > 0) {
            vertical_place_holders.at(r).setUp(vertical_place_holders.at(r - 1));
        }
        if (r < length - 1) {
            vertical_place_holders.at(r).setDown(vertical_place_holders.at(r + 1));
        }
    }

	computeNextBlock();
	setCur();

	if (level == 0)setLevel(0);
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
	else{//drop here
		int temp;
		temp = cur_block->drop();
		score += temp;

		if (level == 4) {
			if (temp == 0)is_slow++;
			else is_slow = 0;

			if (is_slow == 5) {
				if (the_board.at(0).at(5).getInfo().id != WhoIam::Null) {//game over //must temp == 0
					not_over = false;
				}
				for (int r = 1; r < length; ++r) {
					if(the_board.at(r).at(5).getInfo().id != WhoIam::Null){
						the_board.at(r - 1).at(5).setPiece(WhoIam::X, isNull);
						temp = the_board.at(r - 1).at(5).eraseRow();

						if (temp > 0)score += (level + 1) * (level + 1);
						break;
					}
				}
				is_slow = 0;
			}
		}

		if (score > hi_score) {
			hi_score = score;
		}
		for (int r = 0; r < length; r++) {
			for (int c = 0; c < width; c++) {
				if (the_board.at(r).at(c).getInfo().id != WhoIam::Null && the_board.at(r).at(c).getInfo().id != WhoIam::X) {
					if(level != 5)the_board.at(r).at(c).grow();
					else{ the_board.at(r).at(c).grow(lifetime); }
				}
			}
		}
	}
}

void Board::computeNextBlock() {
	//cur_block = new LBlock{ &the_board.at(0).at(4) };
	string type;
	if (sequence >> type) {
		if (type == "L") {
			next_block = WhoIam::L;
		}
		else if (type == "O") {
			next_block = WhoIam::O;
		}
		else if (type == "T") {
			next_block = WhoIam::T;
		}
		else if (type == "S") {
			next_block = WhoIam::S;
		}
		else if (type == "I") {
			next_block = WhoIam::I;
		}
		else if (type == "J") {
			next_block = WhoIam::J;
		}
		else if (type == "Z") {
			next_block = WhoIam::Z;
		}
		else {
			computeNextBlock();
		}
	}
	else {
		if (level == 0 || level == 1) {
			int random = rand() % 12;//random is 0~11
			if (random < 1) {//1
				next_block = WhoIam::S;
			}
			else if (random < 2) {//1
				next_block = WhoIam::Z;
			}
			else if (random < 4) {//2 
				next_block = WhoIam::L;
			}
			else if (random < 6) {//2
				next_block = WhoIam::J;
			}
			else if (random < 8) {//2
				next_block = WhoIam::O;
			}
			else if (random < 10) {//2
				next_block = WhoIam::I;
			}
			else {//2
				next_block = WhoIam::T;
			}
		}
		else if (level == 2) {
			int random = rand() % 7;//random is 0~6
			if (random < 1) {//1
				next_block = WhoIam::S;
			}
			else if (random < 2) {//1
				next_block = WhoIam::Z;
			}
			else if (random < 3) {//1 
				next_block = WhoIam::L;
			}
			else if (random < 4) {//1
				next_block = WhoIam::J;
			}
			else if (random < 5) {//1
				next_block = WhoIam::O;
			}
			else if (random < 6) {//1
				next_block = WhoIam::I;
			}
			else {//1
				next_block = WhoIam::T;
			}
		}
		else  {
			int random = rand() % 9;//random is 0~8
			if (random < 2) {//2
				next_block = WhoIam::S;
			}
			else if (random < 4) {//2
				next_block = WhoIam::Z;
			}
			else if (random < 5) {//1 
				next_block = WhoIam::L;
			}
			else if (random < 6) {//1
				next_block = WhoIam::J;
			}
			else if (random < 7) {//1
				next_block = WhoIam::O;
			}
			else if (random < 8) {//1
				next_block = WhoIam::I;
			}
			else {//1
				next_block = WhoIam::T;
			}
		}
	}
}

void Board::setCur() {
	
    Cell* iblock_prt = &horizontal_place_holders.at(4);
    Cell* otherblock_prt = &the_board.at(0).at(4);
    
    //cur_block = make_unique<IBlock>(level, iblock_prt);

    if(next_block == WhoIam::S)cur_block = make_unique<SBlock>(level, otherblock_prt);
    else if (next_block == WhoIam::Z)cur_block = make_unique<ZBlock>(level, otherblock_prt);
    else if (next_block == WhoIam::L)cur_block = make_unique<LBlock>(level, otherblock_prt);
    else if (next_block == WhoIam::J)cur_block = make_unique<JBlock>(level, otherblock_prt);
    else if (next_block == WhoIam::T)cur_block = make_unique<TBlock>(level, otherblock_prt);
    else if (next_block == WhoIam::I)cur_block = make_unique<IBlock>(level, iblock_prt);
    else if (next_block == WhoIam::O)cur_block = make_unique<OBlock>(level, otherblock_prt);

	computeNextBlock();
	not_over = cur_block->isSuccessful();
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
	if (level > -1 && level < 6)this->level = level;
}

bool Board::setSeq(string source) {
	sequence.open(source);
	return sequence.is_open();
}

void Board::setLife(int lifetime) {
	this->lifetime = lifetime;
}

void Board::clearSeq() {
	sequence.clear();
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