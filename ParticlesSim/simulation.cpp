#include "simulation.h"
#include "settings.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

// Constructor
Simulation::Simulation(std::vector<Particle>& particles, sf::RenderWindow* window): particles(particles){
    this->window = window;
    this->n = particles.size();
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

// Simulation method with a time limit
void Simulation::simulate(double limit) {
    std::cout << "Starting simulation with limit: " << limit << std::endl;
    for (int i = 0; i < n; ++i) predict(particles[i]);
    pq.push(Event(0, nullptr, nullptr));
    while (!pq.empty() && t < limit && this->window->isOpen()) {
        
        Event event = pq.top();
        pq.pop();
        if (!event.isValid()) continue;
        Particle* a = event.p1;
        Particle* b = event.p2;

        // Critical section for updating particles
        {
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
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
        {
            this->window->close();
            exit(0);
        }
    }
    
    this->window->clear();
    {
        for (const auto& particle : particles) {
            sf::CircleShape shape(particle.radius);
            shape.setPosition(particle.x - particle.radius, particle.y - particle.radius);
            shape.setFillColor(sf::Color::Green);
            window->draw(shape);
        }
    }
    this->window->display();

    if (t < limit) {
        pq.push(Event(t + 1.0 / HZ, nullptr, nullptr));  // Adjusting event time
    }
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000/HZ)));
    
}

// Run simulation continuously with limit
void Simulation::runSimulation() {
    double limit = 100000.0;  // Example limit, adjust as necessary
        simulate(limit);
}