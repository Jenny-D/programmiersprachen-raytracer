#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include <glm/vec3.hpp>
#include <ostream>
#include "ray.hpp"
#include "sphere.hpp"

struct HitPoint {
	bool hit;
	float distance;
	std::string name;
	Color color;
	glm::vec3 hitPoint;
	glm::vec3 direction;
};

#endif // !HITPOINT_HPP