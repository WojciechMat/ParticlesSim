#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include "particle.h"
#include "simulation.h"
#include "settings.h"

const float RADIUS = 5.0f;

float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <number_of_particles> <v_min> <v_max>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    float v_min = std::atof(argv[2]);
    float v_max = std::atof(argv[3]);

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Particle Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < n; ++i) {
        float posX = randomFloat(RADIUS, window_width - RADIUS);
        float posY = randomFloat(RADIUS, window_height - RADIUS);
        float velX = randomFloat(v_min, v_max) * (rand() % 2 == 0 ? 1 : -1);
        float velY = randomFloat(v_min, v_max) * (rand() % 2 == 0 ? 1 : -1);
        particles.emplace_back(Particle(velX, velY, posX, posY, 1.0, RADIUS));
    }

    Simulation simulation(particles, &window);

    simulation.runSimulation();

    return 0;
}