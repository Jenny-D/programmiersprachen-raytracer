#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

class Sphere : public Shape {

public:		Sphere();
			Sphere(glm::vec3 const& center_, float radius_);
			Sphere(glm::vec3 const& center_, float radius_, std::string const& name_, Color const& color_);
			~Sphere() override;
			glm::vec3 getCenter() const;
			float getRadius() const;
			virtual float area() const override;
			virtual float volume() const override;
			virtual std::ostream& print(std::ostream& os) const override;
			virtual HitPoint intersect(Ray const& ray, float& distance) const;

private:	glm::vec3 center_;
			float radius_;

};

#endif // !SPHERE_HPP