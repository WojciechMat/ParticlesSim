#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "particle.h"
#include "event.h"

class Simulation {
public:
    Simulation(Particle* particles, int n);
    void simulate(double limit);
    void runSimulation();
	void predict(Particle& p);

    std::mutex mtx;
    std::condition_variable cv;
	std::priority_queue<Event> pq;

private:
    int n;
    Particle* particles;
    
    double t = 0.0;

    
    void redraw(double limit);
};