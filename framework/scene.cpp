#include "scene.hpp"

void Scene::sdf(std::string const& sdfName, Camera cam, Renderer render) {
	
	std::ifstream input(sdfName);
	std::string line_buffer;

	while (std::getline(input, line_buffer))
	{
		std::istringstream line_string_stream(line_buffer);
		std::string identifier;

		line_string_stream >> identifier;

		if ("define" == identifier)
		{
			line_string_stream >> identifier;

			if ("material" == identifier)
			{
				// erstelle Variablen
				std::string material_name;
				float ka_r, ka_g, ka_b;
				float kd_r, kd_g, kd_b;
				float ks_r, ks_g, ks_b;
				float m;
        
				// befülle Variablen
				line_string_stream >> material_name;
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

				// gib Variablen aus
				std::cout << "material " << material_name << " " 
				<< ka_r << " " << ka_g << " " << ka_b << " " 
				<< kd_r << " " << kd_g << " " << kd_b << " " 
				<< ks_r << " " << ks_g << " " << ks_b << " " 
				<<  m  << std::endl;

				// erstelle Objekt
				Material mat { material_name, {ka_r, ka_g, ka_b}, {kd_r, kd_g, kd_b}, {ks_r, ks_g, ks_b}, m };
				auto material = std::make_shared<Material>(mat);

				// füge Objekt zu Container hinzu
				std::pair<std::string, std::shared_ptr<Material>> pair{ material_name, material };
				materialMap.insert(pair);
			}

			if ("shape" == identifier)
			{
				line_string_stream >> identifier;

				if ("box" == identifier)
				{
					// erstelle Variablen
					std::string box_name;
					float min_x, min_y, min_z;
					float max_x, max_y, max_z;
					std::string material_name;

					// befülle Variablen
					line_string_stream >> box_name;
					line_string_stream >> min_x;
					line_string_stream >> min_y;
					line_string_stream >> min_z;
					line_string_stream >> max_x;
					line_string_stream >> max_y;
					line_string_stream >> max_z;
					line_string_stream >> material_name;

					// gib Variablen aus
					std::cout << "box " << box_name << " " 
					<< min_x << " " << min_y << " " << min_z << " " 
					<< max_x << " " << max_y << " " << max_z << " " 
					<< material_name << std::endl;

					// erstelle Objekt
					auto material = find_material(material_name, materialMap);
					//auto material = materialMap.find(material_name)->second;
					Box bo = { {min_x, min_y, min_z}, {max_x, max_y, max_z}, box_name, material };
					auto box = std::make_shared<Box>(bo);

					// füge Objekt zu Container hinzu
					shapeVec.push_back(box);
				}

				if ("sphere" == identifier)
				{
					// erstelle Variablen
					std::string sphere_name;
					float center_x, center_y, center_z;
					float radius;
					std::string material_name;

					// befülle Variablen
					line_string_stream >> sphere_name;
					line_string_stream >> center_x;
					line_string_stream >> center_y;
					line_string_stream >> center_z;
					line_string_stream >> radius;
					line_string_stream >> material_name;

					// gib Variablen aus
					std::cout << "sphere " << sphere_name << " " 
					<< center_x << " " << center_y << " " << center_z << " " 
					<< radius << " " << material_name << std::endl;

					// erstelle Objekt
					auto material = find_material(material_name, materialMap);
					//auto material = materialMap.find(material_name)->second;
					Sphere sphe{ { center_x, center_y, center_z }, radius, sphere_name, material };
					auto sphere = std::make_shared<Sphere>(sphe);
          
					// füge Objekt zu Container hinzu
					shapeVec.push_back(sphere);
				}
			}
		
			if ("light" == identifier) 
			{
				// erstelle Variablen
				std::string light_name;
				float pos_x, pos_y, pos_z;
				float color_r, color_g, color_b;
				float brightness;

				// befülle Variablen
				line_string_stream >> light_name;
				line_string_stream >> pos_x;
				line_string_stream >> pos_y;
				line_string_stream >> pos_z;
				line_string_stream >> color_r;
				line_string_stream >> color_g;
				line_string_stream >> color_b;
				line_string_stream >> brightness;

				// gib Variablen aus
				std::cout << "light " << light_name << " "
				<< pos_x << " " << pos_y << " " << pos_z << " "
				<< color_r << " " << color_g << " " << color_b << " "
				<< brightness << std::endl;

				// erstelle Objekt
				Light light{ light_name, { pos_x, pos_y, pos_z }, { color_r, color_g, color_b }, brightness };

				// füge Objekt zu Container hinzu
				lightVec.push_back(light);
			}
		
			if ("ambient" == identifier) 
			{
				// erstelle Variablen
				float color_r, color_g, color_b;

				// befülle Variablen
				line_string_stream >> color_r;
				line_string_stream >> color_g;
				line_string_stream >> color_b;

				// gib Variablen aus
				std::cout << "ambient "
				<< color_r << " " << color_g << " " << color_b <<
				std::endl;

				// füge Werte ein
				ambient = { color_r, color_g, color_b };
			}

			if ("camera" == identifier) 
			{
        std::string name;
        float fov_x;
        float eye_x, eye_y, eye_z;
        float dir_x, dir_y, dir_z;
        float up_x, up_y, up_z;
        
        line_string_stream >> name;
				line_string_stream >> fov_x;
				line_string_stream >> eye_x;
				line_string_stream >> eye_y;
				line_string_stream >> eye_z;
				line_string_stream >> dir_x;
				line_string_stream >> dir_y;
				line_string_stream >> dir_z;
				line_string_stream >> up_x;
				line_string_stream >> up_y;
				line_string_stream >> up_z;

				std::cout << "camera " << name << " " << fov_x << " "
					<< eye_x << " " << eye_y << " " << eye_z << " "
					<< dir_x << " " << dir_y << " " << dir_z << " "
					<< up_x << " " << up_y << " " << up_z << std::endl;

        cam = Camera{ name, fov_x, { eye_x, eye_y, eye_z }, { dir_x, dir_y, dir_z }, { up_x, up_y, up_z } };
			}
      if ("render" == identifier) 
      {
        unsigned width;
        unsigned height;
        std::string filename;
        
        line_string_stream >> width;
        line_string_stream >> height;
        line_string_stream >> filename;

        render = Renderer(width, height, filename);
      }
		}
	}
	input.close();
}

/*std::shared_ptr<Material> vec_find_material(std::string const& input, std::vector<std::shared_ptr<Material>> const& materialVec) {
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
}*/

std::shared_ptr<Material> find_material(std::string const& input, std::map<std::string, std::shared_ptr<Material>> const& materialMap) {
	auto i = materialMap.find(input);
	if (i != materialMap.end()) {
		return i->second;
	}
	else {
		return nullptr;
	}
}