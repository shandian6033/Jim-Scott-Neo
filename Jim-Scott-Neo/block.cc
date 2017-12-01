#include "block.h"
#include "cell.h"

// Block
// public
Block::Block(int level, Cell* anchor, WhoIam my_type) :level{level}, anchor { anchor }, my_type{ my_type } {}

void Block::rRotate() {
    modifyCellsUnderGrid(true); //erase original WhoIam
    vector<vector<WhoIam>> temp = ifRotated(true); // rotate clockwise
    if (canFit(anchor,temp)) {
        small_grid.clear();
        small_grid = temp;
        
    }
    modifyCellsUnderGrid(false); //write original WhoIam
}
void Block::lRotate() {
    modifyCellsUnderGrid(true);
    vector<vector<WhoIam>> temp = ifRotated(false); // rotate counter clockwise
    if (canFit(anchor,temp)) {
        small_grid.clear();
        small_grid = temp;
    }
    modifyCellsUnderGrid(false);
}
void Block::left() {
    modifyCellsUnderGrid(true);
    if (canFit(anchor->getLeft(), small_grid)) {
        anchor = anchor->getLeft();
    }
    modifyCellsUnderGrid(false);
}
void Block::right() {
    modifyCellsUnderGrid(true);
    if (canFit(anchor->getRight(), small_grid)) {
        anchor = anchor->getRight();
    }
    modifyCellsUnderGrid(false);
}
void Block::down() {
    modifyCellsUnderGrid(true);
    if (canFit(anchor->getDown(), small_grid)) {
        anchor = anchor->getDown();
    }
    modifyCellsUnderGrid(true);
}
int Block::drop() {
	int score = 0;
	int count = 0;
	int temp;
    modifyCellsUnderGrid(true);
    while (canFit(anchor->getDown(),small_grid)){
        anchor = anchor->getDown();
    }//droped to the lowest position.
    modifyCellsUnderGrid(false);

	temp = anchor->eraseRow(); //erase row if possible
	if (temp > -1) {
		score += temp;
		count++;
	}
	temp = anchor->getDown()->eraseRow();
	if (temp > -1) {
		score += temp;
		count++;
	}
	temp = anchor->getDown()->getDown()->eraseRow();
	if (temp > -1) {
		score += temp;
		count++;
	}
    //notifyObservers();

	score += (count + level) ^ 2;
	return score;
}
bool Block::isSuccessful() {
    return is_successful;
}
// protected
void Block::modifyCellsUnderGrid(bool is_erase)const {

    for (int r = 0;r < (int) small_grid.capacity(); r++) {
        for (int c = 0;c < (int) small_grid.at(0).capacity(); c++) {
            if (small_grid.at(r).at(c) == my_type) {
                if (is_erase)cellAt(anchor, c, r)->setPiece(WhoIam::Null, isNull);
                else cellAt(anchor, c, r)->setPiece(my_type, level);
            }
        }
    }
}
// private
vector<vector<WhoIam>>& Block::ifRotated(bool is_clockwise) {

    vector<vector<WhoIam>> ans;
    ans.clear();

    if (is_clockwise) {

        vector<WhoIam> new_row0{ small_grid[2][0],small_grid[1][0] ,small_grid[0][0] };
        vector<WhoIam> new_row1{ small_grid[2][1],small_grid[1][1] ,small_grid[0][1] };
        vector<WhoIam> new_row2{ small_grid[2][2],small_grid[0][2] ,small_grid[0][2] };

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

// LBlock
// public
LBlock::LBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::L } {

    vector<WhoIam> row0{ WhoIam::L,WhoIam::L ,WhoIam::L };
    vector<WhoIam> row1{ WhoIam::Null,WhoIam::Null ,WhoIam::L};
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}


// IBlock
// public
IBlock::IBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::I } {
    
    //a bug will appear when initializing I block,it is created on the second row. may cause unwanted termination of the game.

    /*
        - - - - - - - -  <- should be created on this row ???
        - - I I I I - -  <- actual creation
        - - - - - - - -
        - - - - - - - -
    
    */
    vector<WhoIam> row0{ WhoIam::Null,WhoIam::Null ,WhoIam::Null,WhoIam::Null };
    vector<WhoIam> row1{ WhoIam::I,WhoIam::I ,WhoIam::I,WhoIam::I };
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null,WhoIam::Null };
    vector<WhoIam> row3{ WhoIam::Null,WhoIam::Null ,WhoIam::Null,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);
    small_grid.emplace_back(row3);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false);
}
void IBlock::lRotate() {
    modifyCellsUnderGrid(true);
    iRotate();
    if (!canFit(anchor, small_grid)) iRotate();
    modifyCellsUnderGrid(false);
}
void IBlock::rRotate() {
    modifyCellsUnderGrid(true);
    iRotate();
    if (!canFit(anchor, small_grid)) iRotate();
    modifyCellsUnderGrid(false);
}

// private
void IBlock::iRotate() {
    if (small_grid.at(0).at(1) == my_type && small_grid.at(2).at(1) == my_type && small_grid.at(3).at(1) == my_type) {
        small_grid.at(0).at(1) == WhoIam::Null;
        small_grid.at(2).at(1) == WhoIam::Null;
        small_grid.at(3).at(1) == WhoIam::Null;

        small_grid.at(1).at(0) == my_type;
        small_grid.at(1).at(2) == my_type;
        small_grid.at(1).at(3) == my_type;
    }
    else if(small_grid.at(1).at(0) == my_type || small_grid.at(1).at(2) == my_type || small_grid.at(1).at(3) == my_type){
        small_grid.at(1).at(0) == WhoIam::Null;
        small_grid.at(1).at(2) == WhoIam::Null;
        small_grid.at(1).at(3) == WhoIam::Null;
        
        small_grid.at(0).at(1) == my_type;
        small_grid.at(2).at(1) == my_type;
        small_grid.at(3).at(1) == my_type;
    }
}

// OBlock
// public
OBlock::OBlock(int level, Cell* anchor):Block{ level,anchor,WhoIam::O} {

    vector<WhoIam> row0{ WhoIam::O,WhoIam::O};
    vector<WhoIam> row1{ WhoIam::O,WhoIam::O};

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}
void OBlock::rRotate() {}
void OBlock::lRotate() {}

// utility
Cell* cellAt(Cell* start,int row_offset, int col_offset) {

    // in this fucion row_offset is positive means travel down, negative means travel up.
    // col_offset is positive means travel right and col_offset is negative means travel left. 
    Cell* ans = start;
    if(row_offset > 0){
        while (row_offset > 0 && ans !=nullptr) {
            ans = start->getDown();
            row_offset--;
        }
    }
    else if (row_offset < 0) {
        while (row_offset < 0 && ans != nullptr) {
            ans = start->getUp();
            row_offset++;
        }
    }

    if (col_offset > 0) {
        while (col_offset > 0 && ans != nullptr) {
            ans = start->getRight();
            col_offset--;
        }
    }
    else if(col_offset < 0){
        while (col_offset < 0 && ans != nullptr) {
            ans = start->getLeft();
            col_offset++;
        }
    }

    return ans;
}

bool canFit(Cell* anchor,const vector<vector<WhoIam>>& compare_with) { //waring, may need more thinking about boundary case

    bool ans = true;
    //iterate row and then column
    for (int r = 0;r < compare_with.capacity(); r++) {
        for (int c = 0;c < compare_with.at(0).capacity(); c++) {
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