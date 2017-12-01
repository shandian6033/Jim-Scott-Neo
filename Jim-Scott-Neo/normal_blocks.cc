#include "normal_blocks.h"

// LBlock
LBlock::LBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::L } {

    vector<WhoIam> row0{ WhoIam::L,WhoIam::L ,WhoIam::L };
    vector<WhoIam> row1{ WhoIam::L,WhoIam::Null ,WhoIam::Null };
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}