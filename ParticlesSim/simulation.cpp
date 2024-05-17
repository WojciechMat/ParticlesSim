#include "simulation.h"
#include "settings.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

// Constructor
Simulation::Simulation(Particle* particles, int n) : n(n) {
    this->particles = particles;
    if (!particles) throw "error when constructing simulation";
    std::cout << "Simulation constructed with " << n << " particles." << std::endl;
}

// Prediction method
void Simulation::predict(Particle& p) {
    if (!p.exist()) return;
    for (int i = 0; i < n; ++i) {
        double dt = p.timeToHit(particles[i]);
        pq.push(Event(t + dt, &p, &particles[i]));
    }
    pq.push(Event(t + p.timeToHitVerticalWall(), &p, nullptr));
    pq.push(Event(t + p.timeToHitHorizontalWall(), nullptr, &p));
}

// Event-driven simulation
void Simulation::simulate(double limit) {
    std::cout << "Starting simulation with limit: " << limit << std::endl;
    for (int i = 0; i < n; ++i) predict(particles[i]);
    pq.push(Event(0, nullptr, nullptr));
    while (!pq.empty() && t < limit) {
        Event event = pq.top();
        pq.pop();
        if (!event.isValid()) continue;
        Particle* a = event.p1;
        Particle* b = event.p2;

        // Critical section for updating particles
        {
            std::lock_guard<std::mutex> lock(mtx);
            for (int i = 0; i < n; ++i) {
                particles[i].move(event.time - t);
            }
        }

        t = event.time;

        if (a != nullptr && b != nullptr) a->bounceOffParticle(*b);
        else if (a != nullptr && b == nullptr) a->bounceOffVerticalWall();
        else if (a == nullptr && b != nullptr) b->bounceOffHorizontalWall();
        else if (a == nullptr && b == nullptr) redraw(limit);  // Redraw the particles

        if (a != nullptr) predict(*a);
        if (b != nullptr) predict(*b);
    }
}

// Redraw method
void Simulation::redraw(double limit) {
    std::lock_guard<std::mutex> lock(mtx);
    // Signal the main thread to refresh the window
    cv.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    if (t < limit) {
        pq.push(Event(t + 1.0 / HZ, nullptr, nullptr));  // Adjusting event time
    }
}

// Run simulation continuously with limit
void Simulation::runSimulation() {
    double limit = 100000.0;
    simulate(limit);
}
