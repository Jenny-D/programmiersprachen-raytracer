#ifndef SCENE_HPP
#define SCENE_HPP
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <glm/gtx/transform.hpp>
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
  
  // void sdf(std::string const& sdfName, Camera& cam);
};
//void render(Scene const& scene, Camera const& cam);
glm::mat4 translate(glm::vec3 tv);
glm::mat4 scale(glm::vec3 sm);
glm::mat4 rotate(glm::vec3 rv, float angle);

void sdf(std::string const& sdfName, Scene& scene, Camera& cam, bool animation);

std::shared_ptr<Material> find_material(std::string const& input, std::map<std::string, std::shared_ptr<Material>> const& materialMap);

#endif // !SCENE_HPP