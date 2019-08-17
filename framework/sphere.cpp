#define _USE_MATH_DEFINES
#include <cmath>
#include "sphere.hpp"

Sphere::Sphere() :
	Shape{},
	center_{ 0.0f, 0.0f, 0.0f },
	radius_{ 0.0f } {
	//std::cout << "Default-Konstruktor-Aufruf Klasse Sphere \n";
}

Sphere::Sphere(glm::vec3 const& center_, float radius_):
	Shape{},
	center_{ center_ },
	radius_{ radius_ } {
	//std::cout << "Konstruktor-Aufruf Klasse Sphere \n";
}

Sphere::Sphere(glm::vec3 const& center_, float radius_, std::string const& name_, std::shared_ptr<Material> const& material_) :
	Shape{name_, material_},
	center_{ center_ },
	radius_{ radius_ } {
	//std::cout << "Konstruktor-Aufruf Klasse Sphere \n";
}

Sphere::~Sphere() {
	//std::cout << "Destruktor-Aufruf Klasse Sphere \n";
}

glm::vec3 Sphere:: getCenter() const {
	return center_;
}

float Sphere::getRadius() const {
	return radius_;
}

float Sphere::area() const {
	return 4.0f * M_PI * pow(radius_, 2);
}

float Sphere::volume() const {
	return (4.0f/3.0f) * M_PI * pow(radius_, 3);
}

std::ostream& Sphere::print(std::ostream& os) const {
	Shape::print(os);
	os << "Mittelpunkt: (" << center_.x << ", " << center_.y << ", " << center_.z << ") \nRadius: " << radius_ << "\n \n";
	return os;
}


HitPoint Sphere::intersect(Ray const& ray, float& t) const {
	auto hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, radius_ * radius_, t);
	glm::vec3 intersectionPoint{ 0.0f };
	if (hit) {
		intersectionPoint.x = ray.origin.x + t * ray.direction.x;
		intersectionPoint.y = ray.origin.y + t * ray.direction.y;
		intersectionPoint.z = ray.origin.z + t * ray.direction.z;
	}
  //std::cout << hit << std::endl;
  return HitPoint{ hit, t, getName(), getMaterial(), intersectionPoint , ray.direction };
}

