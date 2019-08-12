#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>
#include <ostream>
#include "color.hpp"
#include "material.hpp"


struct Light {
	std::string name = "Helios";
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
  Color color = { 0.0f, 0.0f, 0.0f };
  float brightness = 0.0f;
};

#endif // !LIGHT_HPP
