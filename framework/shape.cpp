#include "shape.hpp"

Shape::Shape() :
	name_{ "Shape" },
	material_{},
	world_transformation_{	1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0},
	world_transformation_inv_{glm::inverse(world_transformation_)} {
	//std::cout << "Default-Konstruktor-Aufruf Basis-Klasse Shape \n";
}

Shape::Shape(std::string name_, std::shared_ptr<Material> material_):
	name_{name_},
	material_{material_} {
	//std::cout << "Konstruktor-Aufruf Basis-Klasse Shape \n";
}


Shape::~Shape() {
	//std::cout << "Destruktor-Aufruf Basis-Klasse Shape \n";
}

std::string Shape::getName() const {
	return name_;
}

std::shared_ptr<Material> Shape::getMaterial() const {
	return material_;
}

void Shape::setWorldTrans(glm::mat4 m) {
	world_transformation_ = m;
}

glm::mat4 Shape::getWorldTrans() const {
	return world_transformation_;
}

glm::mat4 Shape::getWorldTransInv() const {
	return world_transformation_inv_;
}

std::ostream& Shape::print(std::ostream& os) const {
	os << "Name: " << name_ << "\nMaterial: " << material_<< "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return s.print(os);
}