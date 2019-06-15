#define _USE_MATH_DEFINES
#include <cmath>
#include "sphere.hpp"

Sphere::Sphere() :
	Shape{},
	center_{ 0.0f, 0.0f, 0.0f },
	radius_{ 0.0f } {}

Sphere::Sphere(glm::vec3 const& center_, float radius_):
	Shape{},
	center_{ center_ },
	radius_{ radius_ } {}

Sphere::Sphere(glm::vec3 const& center_, float radius_, std::string const& name_, Color const& color_) :
	Shape{name_, color_},
	center_{ center_ },
	radius_{ radius_ } {}

glm::vec3 Sphere:: getCenter() const {
	return center_;
}

float Sphere::getRadius() const {
	return radius_;
}

float Sphere::area() const {
	return 4.0f * M_PI * pow(radius_, 2);
}

float Sphere::volume() const {
	return (4.0f/3.0f) * M_PI * pow(radius_, 3);
}