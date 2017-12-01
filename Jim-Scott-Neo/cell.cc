#include "cell.h"

//public

Cell::Cell(int row, int col) :r{ row }, c{ col }, living_time{ isNull }, worth{ 0 }, id { WhoIam::Null },
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

void Cell::setPiece(WhoIam new_id, int level) {
	this->id = new_id;
	this->worth = level + 1;
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

int Cell::eraseRow() {
	int score = -1;
    if (isRowClear()) {
		score = 0;
		score += upCopy();
        Cell* p = left;

        while (p != nullptr) {
			score += p->upCopy();
            p = p->left;
        }

        p = right;

        while (p != nullptr) {
			score += p->upCopy();
            p = p->right;
        }

    }
	return score;

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

int Cell::upCopy() {
	int score = 0;
	bool isLast = true;
	if (left != nullptr) {
		isLast = isLast && (left->living_time != living_time);
		if (left->up) {
			isLast = isLast && (left->up->living_time != living_time);
		}
		if (left->down) {
			isLast = isLast && (left->down->living_time != living_time);
		}
	}
	if (right != nullptr) {
		isLast = isLast && (right->living_time != living_time);
		if (right->up) {
			isLast = isLast && (right->up->living_time != living_time);
		}
		if (right->down) {
			isLast = isLast && (right->down->living_time != living_time);
		}
	}
	if (up != nullptr) {
		isLast = isLast && (up->living_time != living_time);
	}
	if (down != nullptr) {
		isLast = isLast && (down->living_time != living_time);
	}

	if (isLast) {
		score += worth ^ 2;
	}


    if (up == nullptr) {
		setPiece(WhoIam::Null, isNull);
		living_time = isNull;
    }
    else {
        setPiece(up->id, up->worth - 1);
        up->upCopy();
    }

	return score;
}

void Cell::grow() {
	living_time++;
}