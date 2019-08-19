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

bool sortbyFirst(const std::pair<float, glm::vec3>& a, const std::pair<float, glm::vec3>& b) {
  return a.first < b.first;
}

HitPoint Box::intersect(Ray const& ray, float& t) const {
  HitPoint hp{ false, std::numeric_limits<float>::max(), getName(), getMaterial(), {0,0,0}, ray.direction , { 1,1,1 } };
  float eps = 0.00001;
  if (ray.direction.x != 0 || ray.direction.y != 0 || ray.direction.z != 0)
  {
    std::vector<std::pair<float, glm::vec3>> distanceVec;
    float minimal_X = (min_.x - ray.origin.x) / ray.direction.x;
    if (minimal_X > 0) { 
      glm::vec3 normal{ -1,0,0 };
      distanceVec.push_back(std::pair<float, glm::vec3>{ minimal_X,normal });
    }
    float maximal_X = (max_.x - ray.origin.x) / ray.direction.x;
    if (maximal_X > 0) {
      glm::vec3 normal{ 1,0,0 };
      distanceVec.push_back(std::pair<float, glm::vec3>{maximal_X, normal });
    }
    float minimal_Y = (min_.y - ray.origin.y) / ray.direction.y;
    if (minimal_Y > 0) {
      glm::vec3 normal{ 0,-1,0 };
      distanceVec.push_back(std::pair<float, glm::vec3>{ minimal_Y, normal });
    }
    float maximal_Y = (max_.y - ray.origin.y) / ray.direction.y;
    if (maximal_Y > 0) {
      glm::vec3 normal{ 0,1,0 };
      distanceVec.push_back(std::pair<float, glm::vec3>{ maximal_Y, normal });
    }
    float minimal_Z = (min_.z - ray.origin.z) / ray.direction.z;
    if (minimal_Z > 0) {
      glm::vec3 normal{ 0,0,-1 };
      distanceVec.push_back(std::pair<float, glm::vec3>{ minimal_Z, normal });
    }
    float maximal_Z = (max_.z - ray.origin.z) / ray.direction.z;
    if (maximal_Z > 0) {
      glm::vec3 normal{ 0,0,1 };
      distanceVec.push_back(std::pair<float, glm::vec3>{ maximal_Z, normal });
    }

    std::sort(distanceVec.begin(), distanceVec.end(), sortbyFirst);

    for (int i = 0; i < distanceVec.size(); i++)
    {
      std::pair<float, glm::vec3> p = distanceVec[i];
      if (p.first != std::numeric_limits<float>::max())
      {
        hp.hitPoint = ray.origin + (p.first * ray.direction);
        if ((hp.hitPoint.x <= max_.x+eps && hp.hitPoint.x >= min_.x-eps) && 
            (hp.hitPoint.y <= max_.y+eps && hp.hitPoint.y >= min_.y-eps) && 
            (hp.hitPoint.z <= max_.z+eps && hp.hitPoint.z >= min_.z-eps))
        {
          t = p.first;
          hp.distance = t;
          hp.hit = true;
          hp.normal = p.second;
          return hp;
        }
      }
    }
  }
  return hp;
}


//HitPoint Box::intersect_old(Ray const& ray, float& t) const {
//
//  t = (min_.x - ray.origin.x) / ray.direction.x;
//  HitPoint hitPoint;
//  glm::vec3 p = ray.origin + t * ray.direction;
//
//  if (p.y > min_.y && p.y < max_.y && p.z > min_.z && p.z < max_.z) {
//    hitPoint.hit = true;
//    hitPoint.distance = t;
//    hitPoint.name = getName();
//    hitPoint.material = getMaterial();
//    hitPoint.hitPoint = ray.origin + t * ray.direction;
//    hitPoint.direction = ray.direction;
//    return hitPoint;
//  }
//  else {
//    hitPoint.hit = false;
//    return hitPoint;
//  }
//}
