#include "subject.h"

void Subject::attach(Observer* p) {
	who_looks_at_me.emplace_back(p);
}

void Subject::notifyObservers() {
	for (auto &it : who_looks_at_me) it->notify(*this);
}
