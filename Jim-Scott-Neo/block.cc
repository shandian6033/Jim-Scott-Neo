#include "Block.h"
#include "Cell.h"

// Block
// public
Block::Block(Cell* anchor, WhoIam my_type) :anchor{ anchor }, my_type{my_type} {}
void Block::rRotate() {

    vector<vector<WhoIam>> temp = ifRotated(true); // rotate clockwise
    if (canFit(anchor,temp)) {
        small_grid.clear();
        small_grid = temp;
        notifyObservers();
    }
}
void Block::lRotate() {

    vector<vector<WhoIam>> temp = ifRotated(false); // rotate counter clockwise
    if (canFit(anchor,temp)) {
        small_grid.clear();
        small_grid = temp;
        notifyObservers();
    }
}
void Block::left() {
    if (canFit(anchor->getLeft(), small_grid)) {
        anchor = anchor->getLeft();
        notifyObservers();
    }
}
void Block::right() {
    if (canFit(anchor->getRight(), small_grid)) {
        anchor = anchor->getRight();
        notifyObservers();
    }
}
void Block::down() {
    if (canFit(anchor->getDown(), small_grid)) {
        anchor = anchor->getDown();
        notifyObservers();
    }
}
void Block::drop() {
    while (canFit(anchor->getDown(),small_grid)){
        anchor = anchor->getDown();
    }//droped to the lowest position.
    
    for (int r = 0;r < small_grid.capacity; r++) { //set states into actual cells
        for (int c = 0;c < small_grid[0].capacity; c++) {
            if (small_grid.at(r).at(c) != WhoIam::Null) {
                cellAt(anchor, c, r)->setPiece(small_grid.at(r).at(c));
            }
        }
    }

    anchor->eraseRow(); //erase row if possible
    anchor->getDown()->eraseRow;
    anchor->getDown()->getDown()->eraseRow();
    //notifyObservers();
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
LBlock::LBlock(Cell* anchor) :Block{ anchor, WhoIam::L } {

    vector<WhoIam> row0{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };
    vector<WhoIam> row1{ WhoIam::Null,WhoIam::Null ,WhoIam::L};
    vector<WhoIam> row2{ WhoIam::L,WhoIam::L ,WhoIam::L };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);
}

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
            WhoIam try_rotate = compare_with.at(r).at(c);
            Cell* p = cellAt(anchor, r, c); //p is the actual cell on board 
            if (p != nullptr) {
                WhoIam what_on_board = p->getInfo().id;
                if (try_rotate != WhoIam::Null && what_on_board != WhoIam::Null) {
                    ans = false;
                    break;
                }
            }
            else ans = false; //p is null, hit boundary ?? may need some thinking
        }
    }
    return ans;
}