#include "cell.h"

//public

Cell::Cell(int row, int col) :r{ row }, c{ col }, living_time{ isNull }, worth{ 0 }, id{ WhoIam::Null },
left{ nullptr }, right{ nullptr }, up{ nullptr }, down{ nullptr } {}

void Cell::setUp(Cell &up) {
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

Cell* Cell::getLeft()const {
	return left;
}
Cell* Cell::getRight()const {
	return right;
}
Cell* Cell::getUp()const {
	return up;
}
Cell* Cell::getDown()const {
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

		while (p->id != WhoIam::Placeholder) { //clear left
			score += p->upCopy();
			p = p->left;
		}

		p = right;

		while (p != nullptr) { //clear right
			score += p->upCopy();
			p = p->right;
		}

	}
	return score;

}


//private
bool Cell::isRightClear()const {
	if (right == nullptr) {
		return true;
	}
	else if (right->id == WhoIam::Null) {
		return false;
	}
	else {
		return right->isRightClear();
	}
}

bool Cell::isLeftClear()const {
	if (left->id == WhoIam::Placeholder) {
		return true;
	}
	else if (left->id == WhoIam::Null) {
		return false;
	}
	else {
		return left->isLeftClear();
	}
}

int abs(int x) {
	if (x < 0)return -x;
	return x;
}

bool Cell::isLast()const {
	bool result = true;
	for (int r = -3; r < 4; r++) {
		for (int c = abs(r) - 3; c < 4 - abs(r); c++) {
			const Cell* cur = this;
			for (int x = 0; x < r; x++) {
				if (cur->up != nullptr)cur = cur->up;
			}
			for (int x = 0; x > r; x--) {
				if (cur->down != nullptr)cur = cur->down;
			}
			for (int y = 0; y < c; y++) {
				if (cur->right != nullptr)cur = cur->right;
			}
			for (int y = 0; y > c; y--) {
				if (cur->left != nullptr)cur = cur->left;
			}
			if (cur != this)result = result && (cur->age() != living_time);
		}
	}
	return result;
}

int Cell::upCopy() {
	int score = 0;

	if (isLast()) {
		score += worth * worth;
	}


	if (up == nullptr) {
		setPiece(WhoIam::Null, isNull);
		living_time = isNull;
	}
	else {
		setPiece(up->id, up->worth - 1);
		living_time = up->age();
		up->upCopy();
	}

	return score;
}

int Cell::age()const {
	return living_time;
}

void Cell::grow() {
	living_time++;
}