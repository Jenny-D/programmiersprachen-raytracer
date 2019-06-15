#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

TEST_CASE(" SphereKonstrAreaVolume ", "[5.2]") {
	Sphere s;
	REQUIRE(s.getCenter().x == 0.0f);
	REQUIRE(s.getCenter().y == 0.0f);
	REQUIRE(s.getCenter().z == 0.0f);
	REQUIRE(s.getRadius() == 0.0f);
	REQUIRE(s.area() == 0.0f);
	REQUIRE(s.volume() == 0.0f);

	Sphere s2{ {1.0f, 2.0f, 3.0f}, 2.0f };
	REQUIRE(s2.getCenter().x == 1.0f);
	REQUIRE(s2.getCenter().y == 2.0f);
	REQUIRE(s2.getCenter().z == 3.0f);
	REQUIRE(s2.getRadius() == 2.0f);
	REQUIRE(s2.area() == Approx(50.2655f));
	REQUIRE(s2.volume() == Approx(33.5103f));
}

TEST_CASE(" BoxKonstrAreaVolume ", "[5.2]") {
	Box b;
	REQUIRE(b.getMin().x == 0.0f);
	REQUIRE(b.getMin().y == 0.0f);
	REQUIRE(b.getMin().z == 0.0f);
	REQUIRE(b.getMax().x == 0.0f);
	REQUIRE(b.getMax().y == 0.0f);
	REQUIRE(b.getMax().z == 0.0f);
	REQUIRE(b.area() == 0.0f);
	REQUIRE(b.volume() == 0.0f);

	Box b2{ {2.0f, 5.0f, 3.0f}, {6.0f, 7.0f, 4.0f} };
	REQUIRE(b2.getMin().x == 2.0f);
	REQUIRE(b2.getMin().y == 5.0f);
	REQUIRE(b2.getMin().z == 3.0f);
	REQUIRE(b2.getMax().x == 6.0f);
	REQUIRE(b2.getMax().y == 7.0f);
	REQUIRE(b2.getMax().z == 4.0f);
	REQUIRE(b2.area() == Approx(28.0f));
	REQUIRE(b2.volume() == Approx(8.0f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
