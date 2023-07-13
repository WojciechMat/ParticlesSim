#pragma once
#include <queue>
#include "Event.h"
#include "particle.h"
#include "settings.h"

class Simulation {
private:
	class Compare {
	public:
		double operator()(Event& const e1, Event& const e2) {
			return e1.getTime() - e2.getTime();
		}
	};
	std::priority_queue<Event, std::vector<Event>, Compare> queue;
	double t = 0.0;
	int n;
	Particle* particles;
public:
	Simulation(Particle* particles, int n);
	void predict(Particle& p);

	void simulate();
};