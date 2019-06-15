#include "shape.hpp"

Shape::Shape() :
	name_{ "Shape" },
	color_{ 1.0f, 1.0f, 1.0f } {}

Shape::Shape(std::string name_, Color color_):
	name_{name_},
	color_{color_} {}

std::string Shape::getName() const {
	return name_;
}

Color Shape::getColor() const {
	return color_;
}

std::ostream& Shape::print(std::ostream& os) const {
	os << "Name: " << name_ << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return s.print(os);
}