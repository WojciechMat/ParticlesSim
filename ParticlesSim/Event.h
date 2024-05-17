#pragma once
#include "particle.h"

class Event {
public:
    double time;
    Particle* p1;
    Particle* p2;
    int countA, countB;

    Event(double t, Particle* a, Particle* b) : time(t), p1(a), p2(b) {
        countA = a != nullptr ? a->count : -1;
        countB = b != nullptr ? b->count : -1;
    }

    bool operator<(const Event& that) const {
        return this->time > that.time;
    }

    bool isValid() {
        if (p1 != nullptr && p1->count != countA) return false;
        if (p2 != nullptr && p2->count != countB) return false;
        return true;
    }
};