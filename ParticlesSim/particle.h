#pragma once
#include<iostream>
class Particle {
private:
	double vx, vy;
	std::pair<double, double> coords;
	const double radius;
	const double mass;
	int count;
public:
	Particle(double vx, double vy, double x, double y, double mass, double radius);
	void move(double t);
	double timeToHit(Particle p);
	double timeToHitVerticalWall();
	double timeToHitHorizontalWall();
	void bounceOffParticle(Particle p);
	void bounceOffVerticalWall();
	void bounceOffHorizontalWall();

	std::pair<double, double> const getPosition() { return coords; }
	std::pair<double, double> const getVelocity() { return std::make_pair(vx, vy); }
	double const getMass() { return mass; }
};
