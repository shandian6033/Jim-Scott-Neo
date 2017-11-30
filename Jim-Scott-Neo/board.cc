#include "board.h"

void Board::init(int row, int col) {
	the_board.clear();
	for (int r = 0; r < row; r++) {
		std::vector<Cell> new_row;
		for (int c = 0; c < row; c++) {
			new_row.emplace_back(Cell(r, c));
		}
		the_board.emplace_back(new_row);
	}
	score = 0;
	hi_score = 0;
	//unique_ptr<Observer>ob = dynamic_cast<unique_ptr<Observer>>(td);
	//td = new TextDisplay{ row,col };

	for (int r = 0; r < row; r++) {
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
				the_board.at(r).at(c).setLeft(the_board.at(r).at(c + 1));
			}
		}
	}
}

void Board::movement(std::string valid_cmd) {
	if (valid_cmd == changable_cmd.left) {//considering abbreviation
		cur_block->left();
	}
	else if (valid_cmd == changable_cmd.right) {
		cur_block->right();
	}
	else if (valid_cmd == changable_cmd.down) {
		cur_block->down();
	}
	else if (valid_cmd == changable_cmd.rRotate) {
		cur_block->rRotate();
	}
	else if (valid_cmd == changable_cmd.lRotate) {
		cur_block->lRotate();
	}
	else(valid_cmd == changable_cmd.drop){
		my_block->drop();
	}
}

bool Board::newBlock(int level) {
	//cur_block = new LBlock{ &the_board.at(0).at(4) };
	cur_block{}
}