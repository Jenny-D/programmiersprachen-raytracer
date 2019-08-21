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
  glm::vec3 normal_dir = glm::normalize(ray.direction);
  auto hit = glm::intersectRaySphere(ray.origin, normal_dir, center_, radius_ * radius_, t);
	glm::vec3 intersectionPoint{ 0.0f };
  if (hit) {

    intersectionPoint.x = ray.origin.x + t * normal_dir.x;
    intersectionPoint.y = ray.origin.y + t * normal_dir.y;
    intersectionPoint.z = ray.origin.z + t * normal_dir.z;

    t = t / sqrt(glm::dot(ray.direction, ray.direction));

    float dir_x = intersectionPoint.x - center_.x;
    float dir_y = intersectionPoint.y - center_.y;
    float dir_z = intersectionPoint.z - center_.z;
    glm::vec3 normal{ dir_x, dir_y, dir_z };

    return HitPoint{ hit, t, getName(), getMaterial(), intersectionPoint , ray.direction, normal };
  }
  else {
    return HitPoint{};
  }
}

//HitPoint Sphere::intersect(Ray const& ray, double& t) const {
//  auto hit = glm::intersectRaySphere<glm::highp_vec3>(ray.origin, glm::normalize(ray.direction), center_, radius_ * radius_, t);
//  glm::vec3 intersectionPoint{ 0.0f };
//  if (hit) {
//    intersectionPoint.x = ray.origin.x + t * ray.direction.x;
//    intersectionPoint.y = ray.origin.y + t * ray.direction.y;
//    intersectionPoint.z = ray.origin.z + t * ray.direction.z;
//  }
//  return HitPoint{ hit, t, getName(), getMaterial(), intersectionPoint , ray.direction, { 0,0,0 } };
//}

//bool intersectRaySphere(glm::vec3 const& rayStarting, glm::vec3 const& rayNormalizedDirection, glm::vec3 const& sphereCenter, float sphereRadiusSquared, float & intersectionDistance )
//{
//  float eps = 0.000001;
//  glm::vec3 diff = sphereCenter - rayStarting;
//  glm::vec3 t0 = glm::dot<glm::vec3>(diff, rayNormalizedDirection);
//  glm::vec3 dSquared = glm::dot<glm::vec3>(diff, diff) - t0 * t0;
//  if (dSquared > sphereRadiusSquared)
//  {
//    return false;
//  }
//  typename genType::value_type t1 = sqrt(sphereRadiusSquered - dSquared);
//  intersectionDistance = t0 > t1 + Epsilon ? t0 - t1 : t0 + t1;
//  return intersectionDistance > Epsilon;
//}

