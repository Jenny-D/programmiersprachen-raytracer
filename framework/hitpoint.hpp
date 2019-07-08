#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include <glm/vec3.hpp>
#include <ostream>
#include "ray.hpp"
#include "material.hpp"


struct HitPoint {
	bool hit = false;
	float distance = 0.0f;
	std::string name = "Sphere";
	std::shared_ptr<Material> material;
	glm::vec3 hitPoint = { 0.0f, 0.0f, 0.0f };
	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };
};

#endif // !HITPOINT_HPP
