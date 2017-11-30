#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "info.h"
#include "observer.h"
const int isNull = -1;

//template<typename T, typename... Args>
//std::unique_ptr<T> make_unique(Args&&... args)
//{
//    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//}

class Subject {
	std::vector<Observer*> who_looks_at_me;

public:
    void attach(Observer* p);
    void notifyObservers();
    //void detach(Observer*); // not sure if needed
    virtual Info getInfo() const = 0; //not NVI
};



void Subject::attach(Observer* p) {
    who_looks_at_me.emplace_back(p);
}

void Subject::notifyObservers() {
    for (auto &it : who_looks_at_me) it->notify(*this);
}

#endif