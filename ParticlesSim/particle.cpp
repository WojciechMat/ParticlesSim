#include "particle.h"
#include "settings.h"
#include <cmath>

int Particle::particle_count = 0;

Particle::Particle() : exists(false), radius(0), mass(0), id(0), count(0), vx(0), vy(0), x(0), y(0) {}

Particle::Particle(double vx, double vy, double x, double y, double mass, double radius) :
    vx(vx), vy(vy), x(x), y(y), mass(mass), radius(radius), count(0), exists(true), id{++particle_count} {}

void Particle::move(double t) {
    x += vx * t;
    y += vy * t;
}

double Particle::timeToHit(Particle& p) {
    if (this == &p) return INFINITY;
    double dx = p.x - x, dy = p.y - y;
    double dvx = p.vx - vx, dvy = p.vy - vy;
    double dvdr = dx * dvx + dy * dvy;
    if (dvdr > 0) return INFINITY;
    double dvdv = dvx * dvx + dvy * dvy;
    double drdr = dx * dx + dy * dy;
    double sigma = radius + p.radius;
    double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
    if (d < 0) return INFINITY;
    return -(dvdr + sqrt(d)) / dvdv;
}

double Particle::timeToHitVerticalWall() {
    if (vx > 0) return (window_width - x - radius) / vx;
    else if (vx < 0) return (x - radius) / -vx;
    else return INFINITY;
}

double Particle::timeToHitHorizontalWall() {
    if (vy > 0) return (window_height - y - radius) / vy;
    else if (vy < 0) return (y - radius) / -vy;
    else return INFINITY;
}

void Particle::bounceOffParticle(Particle& p) {
    double dx = p.x - x, dy = p.y - y;
    double dvx = p.vx - vx, dvy = p.vy - vy;
    double dvdr = dx * dvx + dy * dvy;
    double dist = radius + p.radius;

    double magnitude = 2 * mass * p.mass * dvdr / ((mass + p.mass) * dist);
    double fx = magnitude * dx / dist;
    double fy = magnitude * dy / dist;

    vx += fx / mass;
    vy += fy / mass;
    p.vx -= fx / p.mass;
    p.vy -= fy / p.mass;

    count++;
    p.count++;
}

void Particle::bounceOffVerticalWall() {
    vx = -vx;
    count++;
}

void Particle::bounceOffHorizontalWall() {
    vy = -vy;
    count++;
}

std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << "Particle(id=" << p.id
       << ", position=(" << p.x << ", " << p.y << ")"
       << ", velocity=(" << p.vx << ", " << p.vy << ")"
       << ", mass=" << p.mass
       << ", radius=" << p.radius
       << ", exists=" << p.exists
       << ", count=" << p.count << ")";
    return os;
}
