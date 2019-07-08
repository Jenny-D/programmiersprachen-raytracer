#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>
#include <ostream>
#include "material.hpp"
#include "color.hpp"

struct Material {

	friend std::ostream& operator<<(std::ostream& os, Material const& m) {
		os << "Material: " << m.name_ <<
			"\nMaterialkoeffizient ka: " << m.ka_ << "\nMaterialkoeffizient kd: " << m.kd_ << "\nMaterialkoeffizient ks: " << m.ks_ <<
			"\nSpekularreflexionsexponent m: " << m.m_ << "\n";
		return os;
	}

	std::string name_ = "Irgendein Material";
	Color ka_ = { 0.0f, 0.0f, 0.0f };
	Color kd_ = { 0.0f, 0.0f, 0.0f };
	Color ks_ = { 0.0f, 0.0f, 0.0f };
	float m_ = 0.0f;
};

#endif // !MATERIAL_HPP