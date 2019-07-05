#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>
#include <ostream>
#include "material.hpp"
#include "color.hpp"

struct Material {

	Material():
		name_{"Irgendein Material"},
		ka_{ 0.0f, 0.0f, 0.0f },
		kd_{ 0.0f, 0.0f, 0.0f },
		ks_{ 0.0f, 0.0f, 0.0f },
		m_{ 0.0f } {}

	Material(std::string name_, Color ka_, Color kd_, Color ks_, float m_) :
		name_{ name_ },
		ka_{ ka_ },
		kd_{ kd_ },
		ks_{ ks_ },
		m_{ m_ } {}

	friend std::ostream& operator<<(std::ostream& os, Material const& m) {
		os << "Material: " << m.name_ <<
			"\nMaterialkoeffizient ka: " << m.ka_ << "\nMaterialkoeffizient kd: " << m.kd_ << "\nMaterialkoeffizient ks: " << m.ks_ <<
			"\nSpekularreflexionsexponent m: " << m.m_ << "\n";
		return os;
	}

	std::string name_;
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;
};

#endif // !MATERIAL_HPP