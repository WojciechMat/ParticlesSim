#pragma once
#include "particle.h"

class Event {
private:
	double time;
	int count1, count2;
public:
	Particle *p1, *p2;
	Event(const Event& e) :
		time(e.time), count1(e.count1), count2(e.count2), p1(e.p1), p2(e.p2) {}
	Event(double t, Particle& const p1, Particle& const p2) :
		time(t), count1(p1.count), count2(p2.count), p1(&p1), p2(&p2) {}

	bool isValid() {
		return count1 == p1->count && count2 == p2->count;
	}
	double getTime() const {
		return time;
	}
};