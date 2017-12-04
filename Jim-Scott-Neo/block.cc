#include "block.h"
#include "cell.h"

// Block
// public
Block::Block(int level, Cell* anchor, WhoIam my_type) :anchor { anchor }, my_type{ my_type },level{ level }{}
void Block::rRotate() {
    //modifyCellsUnderGrid(true); //erase original WhoIam
    vector<vector<WhoIam>> temp = ifRotated(true); // rotate clockwise
    if (canFit(anchor,temp)) {
        small_grid.clear();
        small_grid = temp;
        if (level > 2) down();
    }
    //modifyCellsUnderGrid(false); //write original WhoIam
}
void Block::lRotate() {
    //modifyCellsUnderGrid(true);
    vector<vector<WhoIam>> temp = ifRotated(false); // rotate counter clockwise
    if (canFit(anchor,temp)) {
        small_grid.clear();
        small_grid = temp;
        if (level > 2) down();
    }
    //modifyCellsUnderGrid(false);
}
void Block::left() {
    //modifyCellsUnderGrid(true);
    if (canFit(anchor->getLeft(), small_grid)) {
        anchor = anchor->getLeft();
        if (level > 2) down();
    }
    //modifyCellsUnderGrid(false);
}
void Block::right() {
    //modifyCellsUnderGrid(true);
    if (canFit(anchor->getRight(), small_grid)) {
        anchor = anchor->getRight();
        if (level > 2) down();
    }
    //modifyCellsUnderGrid(false);
}
void Block::down() {
    //modifyCellsUnderGrid(true);
    if (canFit(anchor->getDown(), small_grid)) {
        anchor = anchor->getDown();
    }
   // modifyCellsUnderGrid(false);
}
int Block::drop() {
	int score = 0;
	int count = 0;
    modifyCellsUnderGrid(true);
    while (canFit(anchor->getDown(),small_grid)){
        anchor = anchor->getDown();
    }//droped to the lowest position.
    modifyCellsUnderGrid(false);

    eraseCheck(score, count);

	if (count != 0)score += (count + level) *(count + level);
	return score;
}
bool Block::isSuccessful() {
    return is_successful;
}
// protected
void Block::modifyCellsUnderGrid(bool is_erase)const {

    for (int r = 0;r < static_cast<int>(small_grid.size()); r++) {
        for (int c = 0;c < static_cast<int>(small_grid.at(0).size()); c++) {
            if (small_grid.at(r).at(c) == my_type) {
                if (is_erase) cellAt(anchor,r,c)->setPiece(WhoIam::Null, isNull);
                else {
                    Cell* temp = cellAt(anchor, r, c);
                    temp->setPiece(my_type, level);
                }
            }
        }
    }
}
// private
vector<vector<WhoIam>> Block::ifRotated(bool is_clockwise) {

    vector<vector<WhoIam>> ans;
    ans.clear();

    if (is_clockwise) {

        vector<WhoIam> new_row0{ small_grid[2][0],small_grid[1][0] ,small_grid[0][0] };
        vector<WhoIam> new_row1{ small_grid[2][1],small_grid[1][1] ,small_grid[0][1] };
        vector<WhoIam> new_row2{ small_grid[2][2],small_grid[1][2] ,small_grid[0][2] };

        ans.emplace_back(new_row0);
        ans.emplace_back(new_row1);
        ans.emplace_back(new_row2);
    }
    else {
        vector<WhoIam> new_row0{ small_grid[0][2],small_grid[1][2] ,small_grid[2][2] };
        vector<WhoIam> new_row1{ small_grid[0][1],small_grid[1][1] ,small_grid[2][1] };
        vector<WhoIam> new_row2{ small_grid[0][0],small_grid[1][0] ,small_grid[2][0] };

        ans.emplace_back(new_row0);
        ans.emplace_back(new_row1);
        ans.emplace_back(new_row2);
    }
    return ans;
}

void Block::eraseCheck(int& score, int& count) {
    for (int r = 0;r < (int)small_grid.size(); r++) {
        for (int c = 0;c < (int)small_grid.at(0).size(); c++) {
            if (small_grid.at(r).at(c) == my_type) cellAt(anchor, r, c)->born();
        }
    }
    
    for (int r = 0;r < (int)small_grid.size(); r++) {
        for (int c = 0;c < (int)small_grid.at(0).size(); c++) {
            if (small_grid.at(r).at(c) == my_type) {
                int temp = cellAt(anchor, r, c)->eraseRow();
                if (temp > -1) {
                    score += temp;
                    count++;
                }
                break;
            }
        }
    }
}


// utility
Cell* cellAt(Cell* start,int row_offset, int col_offset) {

    // in this fucion row_offset is positive means travel down, negative means travel up.
    // col_offset is positive means travel right and col_offset is negative means travel left. 
    Cell* ans = start;
    if(row_offset > 0){
        while (row_offset > 0 && ans !=nullptr) {
            ans = ans->getDown();
            row_offset--;
        }
    }
    else if (row_offset < 0) {
        while (row_offset < 0 && ans != nullptr) {
            ans = ans->getUp();
            row_offset++;
        }
    }

    if (col_offset > 0) {
        while (col_offset > 0 && ans != nullptr) {
            ans = ans->getRight();
            col_offset--;
        }
    }
    else if(col_offset < 0){
        while (col_offset < 0 && ans != nullptr) {
            ans = ans->getLeft();
            col_offset++;
        }
    }

    return ans;
}

bool canFit(Cell* anchor,const vector<vector<WhoIam>>& compare_with) { //waring, may need more thinking about boundary case

    bool ans = true;
    //iterate row and then column
    for (int r = 0;r < static_cast<int>(compare_with.size()); r++) {
        for (int c = 0;c < static_cast<int>(compare_with.at(0).size()); c++) {
            WhoIam what_on_me = compare_with.at(r).at(c);
            if (what_on_me != WhoIam::Null) { //if what I have is not null, I contain something
                Cell* p = cellAt(anchor, r, c); //p is the actual cell on board 
                if (p != nullptr) {// p is a cell
                    WhoIam what_on_cell = p->getInfo().id; //what state cell has?
                    if (what_on_cell != WhoIam::Null) { //cell also has something on it, cannot fit
                        ans = false;
                        break;
                    }
                }
                else {
                    ans = false; //p is null, hit boundary ?? may need some thinking
                    break;
                }
            }
        }
    }
    return ans;
}

WhoIam Block::getid()const {
	return my_type;
}

Cell* Block::getAnchor()const {
	return anchor;
}

void Block::setAnchor(Cell* anchor) {
	this->anchor = anchor;
}

vector<vector<WhoIam>> Block::getGrid()const {
	return small_grid;
}

void Block::setGrid(vector<vector<WhoIam>> other) {
	this->small_grid = other;
}

void Block::setH() {//only temp will call this
	my_type = WhoIam::H;
	for (auto &r : small_grid) {
		for (auto &c : r) {
			if (c != WhoIam::Null) {
				c = WhoIam::H;
			}
		}
	}
}