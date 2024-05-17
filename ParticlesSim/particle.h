#pragma once
#include <SFML/System.hpp>

class Particle {
public:
    double vx, vy;
    double x, y;
	int id;
    static int particle_count;
    const bool exists;
    const double mass;
    int count;
    const float radius;

    Particle();
    Particle(double vx, double vy, double x, double y, double mass, double radius);
    void move(double t);
    void draw();
    double timeToHit(Particle& p);
    double timeToHitVerticalWall();
    double timeToHitHorizontalWall();
    void bounceOffParticle(Particle& p);
    void bounceOffVerticalWall();
    void bounceOffHorizontalWall();
    const bool exist() const { return exists; }

	friend std::ostream& operator<<(std::ostream& os, const Particle& p);
};
