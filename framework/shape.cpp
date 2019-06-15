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