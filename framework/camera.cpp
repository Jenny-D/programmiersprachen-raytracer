#define _USE_MATH_DEFINES
#include "camera.hpp"
#include <iostream>

float Camera::distance() const {
  // Breite der Ebene auf 1 normieren
  float c = 1;
  // ÷ffnungswinkel in Bogenmaﬂ umrechnen
  float Y = ((2 * M_PI) / 360) * fov_x_;
  // Seitenl‰ngen berechnen
  float a = (c / (std::sin(Y / 2))) / 2;
  // Entfernung zwischen Koordinatenursprung und Bildebene berechnen
  float d = 0.5 * (std::sqrt((4 * a * a) - (c * c)));

  return d;
}

glm::mat4 Camera::cam_transformation() {
	
	glm::vec3 e = eye_;
	glm::vec3 n = glm::normalize(dir_);
	glm::vec3 up = up_;
	glm::vec3 u = glm::normalize(glm::cross(n, up));
	glm::vec3 v = glm::normalize(glm::cross(u, n));

	glm::mat4 transformed_cam;
	transformed_cam[0] = glm::vec4(u, 0.0f);
	transformed_cam[1] = glm::vec4(v, 0.0f);
	transformed_cam[2] = glm::vec4(-1.0f * n, 0.0f);
	transformed_cam[3] = glm::vec4(e, 1.0f);
	
	return transformed_cam;
}