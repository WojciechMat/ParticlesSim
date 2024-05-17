#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "particle.h"
#include "Event.h"

class Simulation {
public:
    Simulation(Particle* particles, int n);
    void simulate(double limit);
    void runSimulation();

    std::mutex mtx;
    std::condition_variable cv;

private:
    int n;
    Particle* particles;
    std::priority_queue<Event> pq;
    double t = 0.0;

    void predict(Particle& p);
    void redraw(double limit);
};