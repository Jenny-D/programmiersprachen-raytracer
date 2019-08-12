#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <ostream>
#include <memory>
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include "material.hpp"

class Shape {

  public:		
    Shape();
	  Shape(std::string name_, std::shared_ptr<Material> material_);
	  virtual ~Shape();
	  std::string getName() const;
	  std::shared_ptr<Material> getMaterial() const;
	  virtual float area() const = 0;
	  virtual float volume() const = 0;
	  virtual std::ostream& print(std::ostream& os) const;
	  virtual HitPoint intersect(Ray const& ray, float& t) const = 0;

  private:	
    std::string name_;
	  std::shared_ptr<Material> material_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // !SHAPE_HPP
