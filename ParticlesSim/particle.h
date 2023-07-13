#pragma once
#include<iostream>
class Particle {
private:
	double vx, vy;
	double x, y;
	
	static int particle_count;
	const bool exists;
	const double radius;
	const double mass;
	int count; 
public:
	int id;
	friend class Event;
	Particle() : 
		exists(false), radius(0), mass(0), id(0), count(0), vx(0), vy(0), x(0), y(0){};
	Particle(double vx, double vy, double x, double y, double mass, double radius) :
		vx(vx), vy(vy), x(x), y(y), mass(mass), radius(radius), count(0), exists(true), id{++particle_count} {};
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
	const bool exist() { return exists; }
	
};
