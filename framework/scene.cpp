#include "scene.hpp"

void Scene::sdf(std::string const& sdfName) {
	
	std::ifstream input(sdfName);
	std::string line_buffer;

	while (std::getline(input, line_buffer))
	{
		std::istringstream line_string_stream(line_buffer);
		std::string identifier;

		//std::vector<std::shared_ptr<Material>> materials_vec;
    //std::vector<Shape> shapes_vec;
    //std::vector<LightSource> lights_vec;

		line_string_stream >> identifier;

		if ("define" == identifier)
		{
			line_string_stream >> identifier;
			if ("material" == identifier)
			{
				std::string material_name;
				line_string_stream >> material_name;

				float ka_r, ka_g, ka_b;
				float kd_r, kd_g, kd_b;
				float ks_r, ks_g, ks_b;
				float m;

				line_string_stream >> ka_r;
				line_string_stream >> ka_g;
				line_string_stream >> ka_b;
				line_string_stream >> kd_r;
				line_string_stream >> kd_g;
				line_string_stream >> kd_b;
				line_string_stream >> ks_r;
				line_string_stream >> ks_g;
				line_string_stream >> ks_b;
				line_string_stream >> m;

				std::cout << "material " << material_name << " " << ka_r << " " << ka_g << " " << ka_b << " " << kd_r << " " << kd_g << " " << kd_b << " " <<  ks_r << " " << ks_g << " " << ks_b << " " <<  m << std::endl;

				Material mat { material_name, {ka_r,ka_g,ka_b}, {kd_r,kd_g,kd_b}, {ks_r,ks_g,ks_b}, m };
				auto material = std::make_shared<Material>(mat);

        std::pair<std::string, std::shared_ptr<Material>> pair{ material_name, material };
        materialMap.insert(pair);
			}
      if ("shape" == identifier)
      {
        line_string_stream >> identifier;
        if ("box" == identifier)
        {
          std::string box_name;
          line_string_stream >> box_name;

          float min_x, min_y, min_z;
          float max_x, max_y, max_z;

          line_string_stream >> min_x;
          line_string_stream >> min_y;
          line_string_stream >> min_z;
          line_string_stream >> max_x;
          line_string_stream >> max_y;
          line_string_stream >> max_z;

          std::string material_name;
          line_string_stream >> material_name;

          std::cout << "box " << box_name << " " << min_x << " " << min_y << " " << min_z << " " << max_x << " " << max_y << " " << max_z << " " << material_name << std::endl;

          auto material = materialMap.find(material_name)->second;

          Box box = { {min_x,min_y,min_z}, {max_x,max_y,max_z}, box_name, material };

          shapeVec.push_back(&box);
        }
        if ("sphere" == identifier)
        {
          std::string sphere_name;
          line_string_stream >> sphere_name;

          float center_x, center_y, center_z;
          float radius;

          line_string_stream >> center_x;
          line_string_stream >> center_y;
          line_string_stream >> center_z;
          line_string_stream >> radius;

          std::string material_name;
          line_string_stream >> material_name;

          std::cout << "sphere " << sphere_name << " " << center_x << " " << center_y << " " << center_z << " " << radius << " " << material_name << std::endl;

          auto material = materialMap.find(material_name)->second;

          glm::vec3 center{ center_x,center_y,center_z };
          Sphere sphere{ center, radius, sphere_name, material };
          
          shapeVec.push_back(&sphere);
        }
      }
		}
	}
	input.close();
}

std::shared_ptr<Material> vec_find_material(std::string const& input, std::vector<std::shared_ptr<Material>> const& materialVec) {
	for (int i = 0; i < materialVec.size(); i++) {
		if (materialVec[i]->name_ == input) {
			return materialVec[i];
		}
	}
	return nullptr;
}

std::shared_ptr<Material> set_find_material(std::string const& input, std::set<std::shared_ptr<Material>> const& materialSet) {
	auto dummy = std::make_shared<Material>();
	dummy->name_ = input;
	std::cout << (dummy == *materialSet.begin()) << std::endl;
	auto result = materialSet.find(dummy);
	std::cout << *result << "  " << *materialSet.end();
	if (result == materialSet.end()) {
		return nullptr;
	}
	return *result;
}

std::shared_ptr<Material> map_find_material(std::string const& input, std::map<std::string, std::shared_ptr<Material>> const& materialMap) {
	auto i = materialMap.find(input);
	if (i != materialMap.end()) {
		return i->second;
	}
	else {
		return nullptr;
	}
}