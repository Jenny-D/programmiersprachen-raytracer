#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <string>
#include <cmath>

struct Camera {

	std::string name_ = "Cam";
	float fov_x_ = 45.0f;
	glm::vec3 eye_ = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dir_ = { 0.0f, 0.0f, -1.0f };
	glm::vec3 up_ = { 0.0f, 1.0f, 0.0f };
	glm::mat4 world_transformation_ = { 1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0 };
	glm::mat4 world_transformation_inv_ = glm::inverse(cam_transformation());

	glm::mat4 cam_transformation();
	float distance()const;

};

#endif // !CAMERA_HPP