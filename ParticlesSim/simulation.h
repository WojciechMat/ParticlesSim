#pragma once
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include "particle.h"
#include "event.h"

class Simulation {
public:
    Simulation(std::vector<Particle>&, sf::RenderWindow*);
    void simulate(double limit);
    void runSimulation();
	void predict(Particle& p);

	std::priority_queue<Event> pq;

private:
    int n;
    std::vector<Particle>& particles;
    sf::RenderWindow* window;
    
    double t = 0.0;

    
    void redraw(double limit);
};