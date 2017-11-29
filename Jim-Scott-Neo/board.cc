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
	
	//display = std::make_unique<TextDisplay>(row, col);
	td = new TextDisplay{ row,col };

	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			the_board.at(r).at(c).attach(td);
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
		my_block->left();
	}
	else if (valid_cmd == changable_cmd.right) {
		my_block->right();
	}
	else if (valid_cmd == changable_cmd.down) {
		my_block->down();
	}
	else if (valid_cmd == changable_cmd.rRotate) {
		my_block->rRotate;
	}
	else if (valid_cmd == changable_cmd.lRotate) {
		my_block->lRotate;
	}
	else(valid_cmd == changable_cmd.drop){
		my_block->drop;
	}
}