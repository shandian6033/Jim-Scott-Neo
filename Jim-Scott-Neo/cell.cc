#include "cell.h"

//public

Cell::Cell(int row, int col) :r{ row }, c{ col }, living_time{ immortality }, id{ WhoIam::Null }, 
	left{ nullptr }, right{nullptr}, up{nullptr}, down{nullptr}{}

void Cell::setUp(Cell &up){
	this->up = &up;
}

void Cell::setDown(Cell &down) {
	this->down = &down;
}

void Cell::setRight(Cell &right) {
	this->right = &right;
}

void Cell::setLeft(Cell &left) {
	this->left = &left;
}

void Cell::setPiece(WhoIam new_id) {
	this->id = new_id;
	notifyObservers();
}

Cell* Cell::getLeft()const{
    return left;
}
Cell* Cell::getRight()const{
    return right;
}
Cell* Cell::getUp()const{
    return up;
}
Cell* Cell::getDown()const{
    return down;
}

Info Cell::getInfo() const {
    Info result;
    result.col = this->c;
    result.row = this->r;
    result.living_time = this->living_time;
    result.id = this->id;
    return result;
}

void Cell::eraseRow() {

    if (isRowClear()) {

        upCopy();
        Cell* p = left;

        while (p != nullptr) {
            p->upCopy();
            p = p->left;
        }

        p = right;

        while (p != nullptr) {
            p->upCopy();
            p = p->right;
        }

    }



}


//private
bool Cell::isRightClear()const {
    if (this->right == nullptr) {
        return true;
    }
    else if (this->right->id == WhoIam::Null) {
        return false;
    }
    else {
        return this->right->isRightClear();
    }
}

bool Cell::isLeftClear()const {
    if (this->left == nullptr) {
        return true;
    }
    else if (this->left->id == WhoIam::Null) {
        return false;
    }
    else {
        return this->left->isLeftClear();
    }
}

void Cell::upCopy() {

    if (up == nullptr) {
        setPiece(WhoIam::Null);
    }
    else {
        setPiece(up->id);
        up->upCopy();
    }
}