#include "normal_blocks.h"

SBlock::SBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::S } {

    vector<WhoIam> row0{ WhoIam::Null,WhoIam::S ,WhoIam::S };
    vector<WhoIam> row1{ WhoIam::S,WhoIam::S ,WhoIam::Null };
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}

ZBlock::ZBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::Z } {

    vector<WhoIam> row0{ WhoIam::Z,WhoIam::Z ,WhoIam::Null };
    vector<WhoIam> row1{ WhoIam::Null,WhoIam::Z ,WhoIam::Z };
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}

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

JBlock::JBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::J } {

    vector<WhoIam> row0{ WhoIam::J,WhoIam::J ,WhoIam::J };
    vector<WhoIam> row1{ WhoIam::Null,WhoIam::Null ,WhoIam::J };
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}

TBlock::TBlock(int level, Cell* anchor) :Block{ level, anchor, WhoIam::T } {

    vector<WhoIam> row0{ WhoIam::T,WhoIam::T ,WhoIam::T };
    vector<WhoIam> row1{ WhoIam::Null,WhoIam::T ,WhoIam::Null };
    vector<WhoIam> row2{ WhoIam::Null,WhoIam::Null ,WhoIam::Null };

    small_grid.emplace_back(row0);
    small_grid.emplace_back(row1);
    small_grid.emplace_back(row2);

    is_successful = canFit(anchor, small_grid);
    if (is_successful) modifyCellsUnderGrid(false); //print the block to display;
}