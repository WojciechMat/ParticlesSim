#pragma once
#include<iostream>
class Particle {
private:
	double vx, vy;
	std::pair<double, double> coords;
	const double radius;
	const double mass;
public:
	Particle(double vx, double vy, double x, double y);
	void move(double t);
	double timeToHit(Particle p);
	double timeToHitVerticalWall();
	double timeToHitHorizontalWall();
	void bounceOffParticle(Particle p);
	void bounceOffVerticalWall();
	void bounceOffHorizontalWall();
};
