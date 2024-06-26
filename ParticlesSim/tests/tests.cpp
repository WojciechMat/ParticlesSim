#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "simulation.h"
#include <iostream>
#include <thread>

const double TOLERANCE = 1e-5;

namespace particle_tests {
    BOOST_AUTO_TEST_CASE(bouncingOTheWallsTest) {
        Particle p1(0.2, -0.2, 320.0, 320.0, 1.0, 1.0);
        p1.move(1.0);
        BOOST_TEST(std::abs(p1.x - 320.2) < TOLERANCE);
        BOOST_TEST(std::abs(p1.y - 319.8) < TOLERANCE);
        p1.move(9.0);
        BOOST_TEST(std::abs(p1.x - 322.0) < TOLERANCE);
        BOOST_TEST(std::abs(p1.y - 318.0) < TOLERANCE);
        p1.bounceOffHorizontalWall();
        BOOST_TEST(std::abs(p1.vy - 0.2) < TOLERANCE);
        p1.bounceOffVerticalWall();
        BOOST_TEST(std::abs(p1.vx + 0.2) < TOLERANCE);
        p1.move(10.0);
        BOOST_TEST(std::abs(p1.x - 320.0) < TOLERANCE);
        BOOST_TEST(std::abs(p1.y - 320.0) < TOLERANCE);
    }

    BOOST_AUTO_TEST_CASE(bouncingOTheParticlesTest) {
        Particle p1(0.0, 1.0, 320.0, 320.0, 1.0, 1.0);
        Particle p2(0.0, -1.0, 320.0, 322.0, 1.0, 1.0);
        p1.bounceOffParticle(p2);
        BOOST_TEST(std::abs(p1.vx - 0.0) < TOLERANCE);
        BOOST_TEST(std::abs(p1.vy + 1.0) < TOLERANCE);
        BOOST_TEST(std::abs(p2.vx - 0.0) < TOLERANCE);
        BOOST_TEST(std::abs(p2.vy - 1.0) < TOLERANCE);
    }

	BOOST_AUTO_TEST_CASE(timerTest) {
        Particle p(1.0, 2.0, 320.0, 320.0, 1.0, 1.0);
        BOOST_TEST(std::abs(p.timeToHitHorizontalWall() - 159.5) < TOLERANCE);
        BOOST_TEST(std::abs(p.timeToHitVerticalWall() - 319.0) < TOLERANCE);

        Particle p1(1.0, 0.0, 5.0, 0.0, 1.0, 1.0);
        Particle p2(-2.0, 0.0, 307.0, 0.0, 1.0, 1.0);
        BOOST_TEST(std::abs(p1.timeToHit(p2) - p2.timeToHit(p1)) < TOLERANCE);
        BOOST_TEST(std::abs(p1.timeToHit(p2) - 302/3) < TOLERANCE);
    }
}

namespace event_tests{
	BOOST_AUTO_TEST_CASE(event_initialization) {
		Particle p1(1.0, 2.0, 320.0, 320.0, 1.0, 1.0);
		Particle p2(-1.0, -2.0, 100.0, 100.0, 1.0, 1.0);

		Event e(5.0, &p1, &p2);
		BOOST_TEST(e.time == 5.0);
		BOOST_TEST(e.p1 == &p1);
		BOOST_TEST(e.p2 == &p2);
		BOOST_TEST(e.countA == p1.count);
		BOOST_TEST(e.countB == p2.count);
	}

	BOOST_AUTO_TEST_CASE(event_priority) {
		Particle p1(1.0, 2.0, 320.0, 320.0, 1.0, 1.0);
		Particle p2(-1.0, -2.0, 100.0, 100.0, 1.0, 1.0);

		Event e1(5.0, &p1, &p2);
		Event e2(3.0, &p1, &p2);
		BOOST_TEST(e1 < e2); // e1 should be less than e2 because its time is greater
	}

	BOOST_AUTO_TEST_CASE(event_is_valid) {
		Particle p1(1.0, 2.0, 320.0, 320.0, 1.0, 1.0);
		Particle p2(-1.0, -2.0, 100.0, 100.0, 1.0, 1.0);

		Event e(5.0, &p1, &p2);
		BOOST_TEST(e.isValid());

		p1.count++;
		BOOST_TEST(!e.isValid());

		p2.count++;
		Event e2(5.0, &p1, &p2);
		BOOST_TEST(e2.isValid());
}

BOOST_AUTO_TEST_CASE(event_priority_queue) {
    Particle p1(1.0, 2.0, 320.0, 320.0, 1.0, 1.0);
    Particle p2(-1.0, -2.0, 100.0, 100.0, 1.0, 1.0);

    std::priority_queue<Event> pq;
    pq.push(Event(5.0, &p1, &p2));
    pq.push(Event(3.0, &p1, &p2));
    pq.push(Event(4.0, &p1, &p2));

    Event e = pq.top();
    BOOST_TEST(e.time == 3.0);
    pq.pop();
    e = pq.top();
    BOOST_TEST(e.time == 4.0);
    pq.pop();
    e = pq.top();
    BOOST_TEST(e.time == 5.0);
    pq.pop();
}
}
