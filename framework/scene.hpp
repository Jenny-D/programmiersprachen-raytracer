#ifndef SCENE_HPP
#define SCENE_HPP
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>
#include "material.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "window.hpp"

struct Scene {

	std::string name = "Scene";
	std::map<std::string, std::shared_ptr<Material>> materialMap;
	std::vector<std::shared_ptr<Shape>> shapeVec;
	std::vector<Light> lightVec;
	Color ambient{ 0,0,0 };
  
  void sdf(std::string const& sdfName, Camera& cam);
  // void sdf(std::string const& sdfName, Camera& cam, Renderer& render);
};

//void sdf(std::string const& sdfName); // soll die unabhängig sein?

std::shared_ptr<Material> find_material(std::string const& input, std::map<std::string, std::shared_ptr<Material>> const& materialMap);

#endif // !SCENE_HPP