#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <ostream>
#include "color.hpp"
//#include "hitpoint.hpp"
//#include "ray.hpp"

class Shape {

public:		Shape();
			Shape(std::string name_, Color color_);
			virtual ~Shape();
			std::string getName() const;
			Color getColor() const;
			virtual float area() const = 0;
			virtual float volume() const = 0;
			virtual std::ostream& print(std::ostream& os) const;
			//virtual bool intersect(Ray const& ray, float& t) = 0;

private:	std::string name_;
			Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // !SHAPE_HPP