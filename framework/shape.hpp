#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <ostream>
#include "color.hpp"

class Shape {

public:		Shape();
			Shape(std::string name_, Color color_);
			std::string getName() const;
			Color getColor() const;
			virtual float area() const = 0;
			virtual float volume() const = 0;

private:	std::string name_;
			Color color_;
};

#endif // !SHAPE_HPP