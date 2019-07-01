#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
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

TEST_CASE(" SphereNameColor ", "[5.3]") {
	Sphere s;
	REQUIRE(s.getName() == "Shape");
	REQUIRE(s.getColor().r == 1.0f);
	REQUIRE(s.getColor().g == 1.0f);
	REQUIRE(s.getColor().b == 1.0f);

	Sphere s2{ {1.0f, 1.0f, 2.0f}, 4.0f, "Red Sphere", {1.0f, 0.0f, 0.0f} };
	REQUIRE(s2.getName() == "Red Sphere");
	REQUIRE(s2.getColor().r == 1.0f);
	REQUIRE(s2.getColor().g == 0.0f);
	REQUIRE(s2.getColor().b == 0.0f);
}

TEST_CASE(" BoxNameColor ", "[5.3]") {
	Box b;
	REQUIRE(b.getName() == "Shape");
	REQUIRE(b.getColor().r == 1.0f);
	REQUIRE(b.getColor().g == 1.0f);
	REQUIRE(b.getColor().b == 1.0f);

	Box b2{ { 1.0f, 1.0f, 2.0f }, {3.0f, 3.0f, 5.0f}, "Blue Box", { 0.0f, 0.0f, 1.0f } };
	REQUIRE(b2.getName() == "Blue Box");
	REQUIRE(b2.getColor().r == 0.0f);
	REQUIRE(b2.getColor().g == 0.0f);
	REQUIRE(b2.getColor().b == 1.0f);
}

TEST_CASE(" SpherePrint ", "[5.5]") {
	Sphere s;
	std::cout << s;

	Sphere s2{ { 2.0f, 6.0f, 3.0f }, 5.0f, "Purple Sphere", { 1.0f, 0.0f, 1.0f } };
	std::cout << s2;

	Sphere s3{ { 2.7f, 5.2f, 4.5f }, 3.4f, "Green Sphere", { 0.0f, 0.9f, 0.0f } };
	std::cout << s3;
}

TEST_CASE(" BoxPrint ", "[5.5]") {
	Box b;
	std::cout << b;

	Box b2{ { 3.0f, 2.0f, 4.0f }, { 4.0f, 3.0f, 7.0f }, "Black Box", { 1.0f, 1.0f, 1.0f } };
	std::cout << b2;

	Box b3{ { 3.6f, 2.9f, 4.5f }, { 4.5f, 3.3f, 7.9f }, "Brown Box", { 0.9f, 0.9f, 0.0f } };
	std::cout << b3;
}

TEST_CASE(" intersect_ray_sphere ", "[5.6]"){
	// Ray
	glm::vec3 ray_origin{ 0.0f, 0.0f, 0.0f };
	// ray direction has to be normalized !
	// you can use :
	// v = glm::normalize(some_vector)
	glm::vec3 ray_direction{ 0.0f, 0.0f, 1.0f };
	glm::vec3 v = glm::normalize(ray_direction);

	// Sphere
	glm::vec3 sphere_center{ 0.0f ,0.0f, 5.0f };
	float sphere_radius{ 1.0f };

	float distance = 0.0f;
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction,
		sphere_center,
		sphere_radius * sphere_radius, // squared radius !!!
		distance);
	REQUIRE(distance == Approx(4.0f));

	//weitere Tests

	//Ray2
	glm::vec3 ray_origin2{ 5.0f, 2.0f, 3.0f };
	glm::vec3 ray_direction2{ 2.0f, 4.0f, 2.0f };
	glm::vec3 v2 = glm::normalize(ray_direction2);

	//Sphere2
	Sphere s2{ { 7.0f , 2.0f, 6.0f }, 4.0f, "Red Sphere",{ 1.0f, 0.0f, 0.0f } };

	auto result2 = s2.intersect({ ray_origin2, ray_direction2 }, distance);
	REQUIRE(distance == Approx(20.149f));
	REQUIRE(result2.hit);
	REQUIRE(result2.name == "Red Sphere");
	REQUIRE(result2.color.r == 1.0f);
	REQUIRE(result2.color.g == 0.0f);
	REQUIRE(result2.color.b == 0.0f);
	REQUIRE(result2.hitPoint.x == Approx(45.298f));
	REQUIRE(result2.hitPoint.y == Approx(82.596f));
	REQUIRE(result2.hitPoint.z == Approx(43.298f));
	REQUIRE(result2.direction.x == 2.0f);
	REQUIRE(result2.direction.y == 4.0f);
	REQUIRE(result2.direction.z == 2.0f);

	auto r = s2.intersect({ ray_origin, ray_direction }, distance);
	REQUIRE(r.hit == false);

	//Sphere 3
	Sphere s3{ { 0.0f , 1.0f, 1.0f }, 1.5f, "Blue Sphere",{ 0.0f, 0.0f, 1.0f } };

	auto result3 = s3.intersect({ ray_origin2, ray_direction2 }, distance);
	REQUIRE(result3.hit == false);

	auto result4 = s3.intersect({ ray_origin, ray_direction }, distance);
	REQUIRE(result3.hit == false);
}

TEST_CASE(" Destruktor ", "[5.8]") {
	Color red{ 255 , 0, 0 };
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	Sphere* s1 = new Sphere{ position, 1.2f, "sphere 0", red };
	Shape* s2 = new Sphere{ position, 1.2f, "sphere 1", red };
	s1->print(std::cout);
	s2->print(std::cout);
	delete s1;
	delete s2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
