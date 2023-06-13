#pragma once
#include<iostream>
#include "event.h"
class Particle {
private:
	double vx, vy;
	double x, y;
	const bool exists;
	const double radius;
	const double mass;
	int count; 
public:
	Particle() : 
		exists(false), radius(0), mass(0){};
	Particle(double vx, double vy, double x, double y, double mass, double radius) :
		vx(vx), vy(vy), x(x), y(y), mass(mass), radius(radius), count(0), exists(true) {};
	void move(double t);
	void draw();

	double timeToHit(Particle& p);
	double timeToHitVerticalWall();
	double timeToHitHorizontalWall();

	void bounceOffParticle(Particle& p);
	void bounceOffVerticalWall();
	void bounceOffHorizontalWall();

	std::pair<double, double> const getPosition() { return std::make_pair(x, y); }
	std::pair<double, double> const getVelocity() { return std::make_pair(vx, vy); }
	double const getMass() { return mass; }
	double const getRadius() { return radius; }
	const bool exists() { return exists; }
	friend Event;
};
