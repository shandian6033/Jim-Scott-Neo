#include "cell.h"

Cell::Cell(int row, int col) :r{ row }, c{ col }, living_time{ immortality }, id{ WhoIam::Null } {}

