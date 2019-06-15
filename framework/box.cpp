#include "box.hpp"
#include <cmath>

Box::Box() :
	Shape{},
	min_{ 0.0f },
	max_{ 0.0f } {}

Box::Box(glm::vec3 const& min_, glm::vec3 const& max_) :
	Shape{},
	min_{ min_ },
	max_{ max_ } {}

glm::vec3 Box:: getMin() {
	return min_;
}

glm::vec3 Box::getMax() {
	return max_;
}

float Box:: area() const {
	auto i = max_ - min_;
	return 2 * (i.x * i.y) + 2 * (i.y * i.z) + 2 * (i.x * i.z);
}

float Box:: volume() const {
	auto i = max_ - min_;
	return i.x * i.y * i.z;
}