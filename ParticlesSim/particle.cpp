#include "particle.h"
#include "settings.h"
#include <amp_graphics.h>

void Particle::move(double t) {
	x += t * vx;
	y += t * vy;
}
double Particle::timeToHitHorizontalWall() {
	return (abs(window_height - y)) / vy;
}
double Particle::timeToHitVerticalWall() {
	return (abs(window_width - x)) / vx;
}
double Particle::timeToHit(Particle& p) {
	if (&p == this) return INFINITY;
	double dx = x - p.x, dy = y - p.y;
	double dvx = vx - p.vx, dvy = vy - p.vy;
	double dvdr = dx * dvx + dy * dvy;
	if (dvdr > 0) return INFINITY;
	double dvdv = dvx * dvx + dvy * dvy;
	double drdr = dx * dx + dy * dy;
	double dist = radius + p.radius;
	double d = (dvdr * dvdr) - dvdv * (drdr - dist * dist);
	if (d < 0) return INFINITY;
	return -(dvdr + sqrt(d)) / dvdv;
}

void Particle::bounceOffHorizontalWall() { vy = -vy; }
void Particle::bounceOffVerticalWall() { vx = -vx; }
void Particle::bounceOffParticle(Particle& p) {
	double dx = p.x - x, dy = p.y - y;
	double dvx = p.vx - vx, dvy = p.vy - vy;
	double dvdr = dx * dvx + dy * dvy;
	double dist = radius + p.radius;
	double F = 2 * mass * p.mass * dvdr / ((mass + p.mass) * dist);
	double Fx = F * dx / dist;
	double Fy = F * dy / dist;
	vx += Fx / mass;
	vy += Fy / mass;
	p.vx -= Fx / p.mass;
	p.vy -= Fy / p.mass;
	count++;
	p.count++;
}
void Particle::draw() {
	
}