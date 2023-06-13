#pragma once
#include "particle.h"

class Event {
private:
	double time;
	
	int count1, count2;
public:
	Particle& p1, p2;
	Event(double t, Particle& p1, Particle& p2) :
		time(t), p1(p1), p2(p2), count1(p1.count), count2(p2.count) {}
	bool isValid() {
		return count1 == p1.count && count2 == p2.count;
	}
	double getTime() const {
		return time;
	}
};