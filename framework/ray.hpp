#ifndef RAY_HPP
#define RAY_HPP
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>

struct Ray {
  
	glm::vec3 origin = {0.0, 0.0, 0.0};
	glm::vec3 direction = {0.0, 0.0, -1.0};

	friend Ray transformRay(glm::mat4 const& m, Ray const& r) { //friend, damit es keine Memberfunktion ist, aber Zugriff auf alle Membervariablen hat

		glm::vec4 o{ r.origin , 1.0f };
		glm::vec4 d{ r.direction , 0.0f };

		glm::vec3 transformed_origin(m * o);
		glm::vec3 transformed_direction(m * d);

		return Ray{ transformed_origin , transformed_direction };
	}
};

#endif // !RAY_HPP