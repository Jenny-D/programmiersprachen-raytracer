#include "box.hpp"
#include <cmath>

Box::Box() :
	Shape{},
	min_{ 0.0f },
	max_{ 0.0f } {
	//std::cout << "Default-Konstruktor-Aufruf Klasse Box \n";
}

Box::Box(glm::vec3 const& min_, glm::vec3 const& max_):
	Shape{},
	min_{ min_ },
	max_{ max_ } {
	//std::cout << "Konstruktor-Aufruf Klasse Box \n";
}

Box::Box(glm::vec3 const& min_, glm::vec3 const& max_, std::string const& name_, std::shared_ptr<Material> const& material_) :
	Shape{name_, material_},
	min_{ min_ },
	max_{ max_ } {
	//std::cout << "Konstruktor-Aufruf Klasse Box \n";
}

Box::~Box() {
	//std::cout << "Destruktor-Aufruf Klasse Box \n";
}

glm::vec3 Box:: getMin() const {
	return min_;
}

glm::vec3 Box::getMax() const {
	return max_;
}

float Box:: area() const {
	auto i = max_ - min_;
	return 2 * (i.x * i.y) + 2 * (i.y * i.z) + 2 * (i.x * i.z);
}

float Box:: volume() const {
	auto i = max_ - min_;
	return i.x * i.y * i.z;
}

std::ostream& Box::print(std::ostream& os) const {
	Shape::print(os);
	os << "Minimum: (" << min_.x << ", " << min_.y << ", " << min_.z << ") \nMaximum: (" << max_.x << ", " << max_.y << ", " << max_.z << ") \n \n";
	return os;
}


HitPoint Box::intersect(Ray const& ray, float& t) const {
  HitPoint hp{ false, std::numeric_limits<float>::max(), getName(), getMaterial(), {0,0,0}, ray.direction };
  if (ray.direction.x != 0 || ray.direction.y != 0 || ray.direction.z != 0)
  {
    std::vector<float> distanceVec;
    float minimal_X = (min_.x - ray.origin.x) / ray.direction.x;
    distanceVec.push_back(minimal_X);
    float maximal_X = (max_.x - ray.origin.x) / ray.direction.x;
    distanceVec.push_back(maximal_X);
    float minimal_Y = (min_.y - ray.origin.y) / ray.direction.y;
    distanceVec.push_back(minimal_Y);
    float maximal_Y = (max_.y - ray.origin.y) / ray.direction.y;
    distanceVec.push_back(maximal_Y);
    float minimal_Z = (min_.z - ray.origin.z) / ray.direction.z;
    distanceVec.push_back(minimal_Z);
    float maximal_Z = (max_.z - ray.origin.z) / ray.direction.z;
    distanceVec.push_back(minimal_Z);

    std::sort(distanceVec.begin(), distanceVec.end());

    for (float i : distanceVec)
    {
      if (i != std::numeric_limits<float>::max())
      {
        hp.hitPoint = ray.origin + (i * ray.direction);
        if ((hp.hitPoint.x <= max_.x && hp.hitPoint.x >= min_.x) && 
            (hp.hitPoint.y <= max_.y && hp.hitPoint.y >= min_.y) && 
            (hp.hitPoint.z <= max_.z && hp.hitPoint.z >= min_.z))
        {
          t = i;
          hp.distance = t;
          hp.hit = true;
          return hp;
        }
      }
    }
  }
  return hp;
}


HitPoint Box::intersect_old(Ray const& ray, float& t) const {

  t = (min_.x - ray.origin.x) / ray.direction.x;
  HitPoint hitPoint;
  glm::vec3 p = ray.origin + t * ray.direction;

  if (p.y > min_.y && p.y < max_.y && p.z > min_.z && p.z < max_.z) {
    hitPoint.hit = true;
    hitPoint.distance = t;
    hitPoint.name = getName();
    hitPoint.material = getMaterial();
    hitPoint.hitPoint = ray.origin + t * ray.direction;
    hitPoint.direction = ray.direction;
    return hitPoint;
  }
  else {
    hitPoint.hit = false;
    return hitPoint;
  }
}
