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