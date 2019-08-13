#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>

struct Camera {

	std::string name_ = "Cam";
	float fov_x_ = 0.0f;
	glm::vec3 eye_ = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dir_ = { 0.0f, 0.0f, -1.0f };
	glm::vec3 up_ = { 0.0f, 0.0f, 0.0f };

};

#endif // !CAMERA_HPP