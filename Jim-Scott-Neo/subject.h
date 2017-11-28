#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "info.h"
#include "observer.h"

class Subject {
	std::vector<Observer*> who_looks_at_me;
protected:
	void setState(Shape newS);
public:
    void attach(Observer *p);
    void notifyObservers();
    void detach(Observer*); // not sure if needed
    virtual Info getInfo() = 0; //not NVI
};



void Subject::attach(Observer* p) {
    who_looks_at_me.emplace_back(p);
}

void Subject::notifyObservers() {
    for (auto &it : who_looks_at_me) it->notify(*this);
}

#endif