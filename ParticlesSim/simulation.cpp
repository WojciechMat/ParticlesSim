#include "simulation.h"
#include "particle.h"
#include "Event.h"

Simulation::Simulation(Particle* particles, int n): n(n){
	(*this).particles = particles;
	if (!particles) throw "error when constructing simulation";
}

void Simulation::predict(Particle& p) {
	if (&p == nullptr || p.exist() == false) return;
	for (int i = 0; i < n; ++i) {
		double dt = p.timeToHit(particles[i]);
		queue.push(Event(t + dt, p, particles[i]));
	}
	Particle none;
	queue.push(Event(t + p.timeToHitVerticalWall(), p, none));
	queue.push(Event(t + p.timeToHitHorizontalWall(), none, p));
}
void Simulation::simulate() {
	for (int i = 0; i < n; ++i) predict(particles[i]);
	Particle none;
	queue.push(Event(0, none, none));
	while (!std::empty(queue)) {
		Event event(queue.top());
		queue.pop();
		if (!event.isValid()) continue;
		Particle& p1 = *event.p1;
		Particle& p2 = *event.p2;
		
		for (int i = 0; i < n; ++i) {
			particles[i].move(event.getTime() - t);
		}
		t = event.getTime();

		if (p1.exist() && p2.exist()) p1.bounceOffParticle(p2);
		else if (p1.exist() && !p2.exist()) p1.bounceOffVerticalWall();
		else if (!p1.exist() && p2.exist()) p2.bounceOffHorizontalWall();
		else if (!p1.exist() && !p2.exist()) {};

		predict(p1);
		predict(p2);
	}
}

