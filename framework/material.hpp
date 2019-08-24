#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>
#include <ostream>
#include "material.hpp"
#include "color.hpp"

struct Material {

	friend std::ostream& operator<<(std::ostream& os, Material const& m) {
		os << "Material: " << m.name_ <<
			"\nMaterialkoeffizient ka: " << m.ka_ << "Materialkoeffizient kd: " << m.kd_ << "Materialkoeffizient ks: " << m.ks_ <<
			"Spekularreflexionsexponent m: " << m.m_ << "\n";
		return os;
	}

	std::string name_ = "Irgendein Material";
	Color ka_ = { 0.0f, 0.0f, 0.0f };
	Color kd_ = { 0.0f, 0.0f, 0.0f };
	Color ks_ = { 0.0f, 0.0f, 0.0f };
	float m_ = 0.0f;
  float mirror_ = 0;
};

#endif // !MATERIAL_HPP