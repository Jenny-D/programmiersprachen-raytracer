#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <cmath>

struct Camera {

	std::string name_ = "Cam";
	float fov_x_ = 0.0f;
	glm::vec3 eye_ = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dir_ = { 0.0f, 0.0f, -1.0f };
	glm::vec3 up_ = { 0.0f, 0.0f, 0.0f };

  float distance()const;

};

#endif // !CAMERA_HPP