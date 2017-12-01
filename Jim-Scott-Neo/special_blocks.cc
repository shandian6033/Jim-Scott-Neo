#include "special_blocks.h"
#include "cell.h"
// IBlock
// public
IBlock::IBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::I } {

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
    if (!canFit(anchor, small_grid) || anchor->getInfo().row == -1) iRotate();
    modifyCellsUnderGrid(false);
}
void IBlock::rRotate() {
    modifyCellsUnderGrid(true);
    iRotate();
    if (!canFit(anchor, small_grid) || anchor->getInfo().row == -1) iRotate();
    modifyCellsUnderGrid(false);
}

// private
void IBlock::iRotate() {
    if (small_grid.at(0).at(1) == my_type && small_grid.at(2).at(1) == my_type && small_grid.at(3).at(1) == my_type) {
        small_grid.at(0).at(1) = WhoIam::Null;
        small_grid.at(2).at(1) = WhoIam::Null;
        small_grid.at(3).at(1) = WhoIam::Null;

        small_grid.at(1).at(0) = my_type;
        small_grid.at(1).at(2) = my_type;
        small_grid.at(1).at(3) = my_type;
    }
    else if (small_grid.at(1).at(0) == my_type || small_grid.at(1).at(2) == my_type || small_grid.at(1).at(3) == my_type) {
        small_grid.at(1).at(0) = WhoIam::Null;
        small_grid.at(1).at(2) = WhoIam::Null;
        small_grid.at(1).at(3) = WhoIam::Null;

        small_grid.at(0).at(1) = my_type;
        small_grid.at(2).at(1) = my_type;
        small_grid.at(3).at(1) = my_type;
    }
}

// OBlock
// public
OBlock::OBlock(int level, Cell* anchor) :Block{ level,anchor,WhoIam::O } {

    vector<WhoIam> row0{ WhoIam::O,WhoIam::O };
    vector<WhoIam> row1{ WhoIam::O,WhoIam::O };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}
void OBlock::rRotate() {}
void OBlock::lRotate() {}