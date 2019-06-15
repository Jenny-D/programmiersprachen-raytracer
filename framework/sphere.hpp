#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {

public:		Sphere();
			Sphere(glm::vec3 const& center_, float radius_);
			glm::vec3 getCenter();
			float getRadius();
			virtual float area() const override;
			virtual float volume() const override;

private:	glm::vec3 center_;
			float radius_;
};

#endif // !SPHERE_HPP