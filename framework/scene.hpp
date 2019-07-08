#ifndef SCENE_HPP
#define SCENE_HPP
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <string>
#include <algorithm>
#include "material.hpp"

struct Scene {

	std::string name = "Scene";

	std::vector<std::shared_ptr<Material>> materialVec;
	std::set<std::shared_ptr<Material>> materialSet;
	std::map<std::string, std::shared_ptr<Material>> materialMap;

};

Scene sdf(std::string const& sdfName);

std::shared_ptr<Material> vec_find_material(std::string const& input, std::vector<std::string, std::shared_ptr<Material>> const& materialVec);
std::shared_ptr<Material> set_find_material(std::string const& input, std::set<std::string, std::shared_ptr<Material>> const& materialSet);
std::shared_ptr<Material> map_find_material(std::string const& input, std::map<std::string, std::shared_ptr<Material>> const& materialMap);

#endif // !SCENE_HPP