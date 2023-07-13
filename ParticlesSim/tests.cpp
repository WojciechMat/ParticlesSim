#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "simulation.h"
#include<iostream>

namespace particle_tests {
	BOOST_AUTO_TEST_CASE(bouncingOffTheWallsTest)
	{
		Particle p1(0.2, -0.2, 320.0, 320.0, 1.0, 1.0);
		p1.move(1.0);
		BOOST_TEST(p1.getPosition().first == 320.2);
		BOOST_TEST(p1.getPosition().second == 319.8);
		p1.move(9.0);
		BOOST_TEST(p1.getPosition().first == 322.0);
		BOOST_TEST(p1.getPosition().second == 318.0);
		p1.bounceOffHorizontalWall();
		BOOST_TEST(p1.getVelocity().second == 0.2);
		p1.bounceOffVerticalWall();
		BOOST_TEST(p1.getVelocity().first == -0.2);
		p1.move(10.0);
		BOOST_TEST(p1.getPosition().first == 320.0);
		BOOST_TEST(p1.getPosition().second == 320.0);
	}

	BOOST_AUTO_TEST_CASE(bouncingOffTheParticlesTest)
	{
		Particle p1(0, 1.0, 320.0, 320.0, 1.0, 1.0),
			p2(0, -1.0, 320.0, 322.0, 1.0, 1.0);
		p1.bounceOffParticle(p2);
		BOOST_TEST(p1.getVelocity().first == 0.0);
		BOOST_TEST(p1.getVelocity().second == -1.0);
		BOOST_TEST(p2.getVelocity().first == 0.0);
		BOOST_TEST(p2.getVelocity().second == 1.0);

	}
	BOOST_AUTO_TEST_CASE(timerTest) {
		Particle p(1.0, 2.0, 320.0, 320.0, 1.0, 1.0);
		BOOST_TEST(p.timeToHitHorizontalWall() == 160.0);
		BOOST_TEST(p.timeToHitVerticalWall() == 320.0);

		Particle p1(1.0, 0.0, 5.0, 0.0, 1.0, 1.0);
		Particle p2(-2.0, 0.0, 307.0, 0.0, 1.0, 1.0);
		BOOST_TEST(p1.timeToHit(p2) == p2.timeToHit(p1));
		BOOST_TEST(p1.timeToHit(p2) == 100.0);

	}
}

namespace simulation_tests {
	Particle a(1.0, 2.0, 320, 320, 1.0, 1.0);
	Particle b(1.0, 3.0, 321, 320, 1.0, 8.0);
	Particle c(-1.3, 2.3, 320, 30, 1.0, 2.0);
	Particle d(1.2, 0.0, 0, 20, 5, 1.0);
	Particle e(1.2, -2.0, 32, 30, 1.0, 1.0);
	Particle f(1.0, 0, 20, 20, 1.0, 1.0);
	Particle g(5.0, 5.0, 334, 331, 1.0, 1.0);
	Particle h(1.0, -1.0, 87, 31, 1.0, 1.0);
	Particle particles[8] = { a, b, c, d, e, f, g, h };
	Simulation sim(particles, 8);
	BOOST_AUTO_TEST_CASE(constructorTest) {
		BOOST_TEST(particles);
		BOOST_TEST(particles[2].id == 3);

	}


}