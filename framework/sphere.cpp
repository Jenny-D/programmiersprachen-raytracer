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
  Ray transformed_ray{ transformRay(getWorldTransInv(), ray) };
  glm::vec3 normal_dir = glm::normalize(transformed_ray.direction);
  auto hit = glm::intersectRaySphere(transformed_ray.origin, normal_dir, center_, radius_ * radius_, t);
  glm::vec3 intersectionPoint{ 0.0f };

  if (hit) {

    intersectionPoint.x = transformed_ray.origin.x + t * normal_dir.x;
    intersectionPoint.y = transformed_ray.origin.y + t * normal_dir.y;
    intersectionPoint.z = transformed_ray.origin.z + t * normal_dir.z;

    t = t / sqrt(glm::dot(transformed_ray.direction, transformed_ray.direction));
    
    float dir_x = intersectionPoint.x - center_.x;
    float dir_y = intersectionPoint.y - center_.y;
    float dir_z = intersectionPoint.z - center_.z;
    glm::vec3 normal{ dir_x, dir_y, dir_z };

	glm::mat4 transposed = glm::transpose(getWorldTransInv());
	glm::vec3 transformed_normal(transposed * glm::vec4{ normal, 0.0f });
	normal = glm::normalize(transformed_normal);

    return HitPoint{ hit, t, getName(), getMaterial(), intersectionPoint , transformed_ray.direction, normal };
  }

  else {
    return HitPoint{};
  }
}
