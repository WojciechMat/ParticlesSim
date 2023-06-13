#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "particle.h"

BOOST_AUTO_TEST_CASE(bouncingOffTheWallsTest)
{
	Particle p1(0.2, -0.2, 320.0, 320.0, 1.0, 1.0);
	p1.move(1.0);
  BOOST_TEST(p1.getPosition() == std::make_pair(320.2, 319.8));
  p1.move(9.0);
  BOOST_TEST(p1.getPosition() == std::make_pair(322.0, 318.0));
  p1.bounceOffHorizontalWall();
  BOOST_TEST(p1.getVelocity().second == 0.2);
  p1.bounceOffVerticalWall();
  BOOST_TEST(p1.getVelocity().first == -0.2);
  p1.move(10.0);
  BOOST_TEST(p1.getPosition() == std::make_pair(320.0, 320.0));
}

BOOST_AUTO_TEST_CASE(bouncingOffTheParticlesTest)
{
	Particle p1(0, 1.0, 320.0, 320.0, 1.0, 1.0),
		p2(0, -1.0, 320.0, 321.0, 1.0, 1.0);
	p1.bounceOffParticle(p2);
	BOOST_TEST(p1.getVelocity() == std::make_pair(0.0, -1.0));
	BOOST_TEST(p2.getVelocity() == std::make_pair(0.0, 1.0));

}