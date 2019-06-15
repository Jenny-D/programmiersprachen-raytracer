#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {

public:		Sphere();
			Sphere(glm::vec3 const& center_, float radius_);
			Sphere(glm::vec3 const& center_, float radius_, std::string const& name_, Color const& color_);
			glm::vec3 getCenter() const;
			float getRadius() const;
			virtual float area() const override;
			virtual float volume() const override;

private:	glm::vec3 center_;
			float radius_;

};

#endif // !SPHERE_HPP