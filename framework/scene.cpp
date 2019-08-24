#include "scene.hpp"

glm::mat4 translate(glm::vec3 tv){
 
	glm::mat4 m;
	m[0] = glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
	m[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
	m[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
	m[3] = glm::vec4{ tv.x, tv.y, tv.z, 1 };

	return m;
}

glm::mat4 scale(glm::vec3 sv) {

	glm::mat4 m;
	m[0] = glm::vec4{ sv.x, 0.0f, 0.0f, 0.0f };
	m[1] = glm::vec4{ 0.0f, sv.y, 0.0f, 0.0f };
	m[2] = glm::vec4{ 0.0f, 0.0f, sv.z, 0.0f };
	m[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

	return m;
}

glm::mat4 rotate(glm::vec3 rv, float angle) {

	glm::mat4 m;

	if (rv.x == 1.0f) {
		m[0] = glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
		m[1] = glm::vec4{ 0.0f, cos(angle), sin(angle), 0.0f };
		m[2] = glm::vec4{ 0.0f, -sin(angle), cos(angle), 0.0f };
		m[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

		return m;
	}

	if (rv.y == 1.0f) {
		m[0] = glm::vec4{ cos(angle), 0.0f, -sin(angle), 0.0f };
		m[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
		m[2] = glm::vec4{ sin(angle), 0.0f, cos(angle), 0.0f };
		m[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

		return m;
	}

	if (rv.z == 1.0f) {
		m[0] = glm::vec4{ cos(angle), sin(angle), 0.0f, 0.0f };
		m[1] = glm::vec4{ -sin(angle), cos(angle), 0.0f, 0.0f };
		m[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
		m[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

		return m;
	}
}

void sdf(std::string const& sdfName, Scene& scene, Camera& cam) {
	
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
        float mirror = 0;
        
				// bef�lle Variablen
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
        line_string_stream >> mirror;

				// gib Variablen aus
				std::cout << "material " << material_name << " " 
				<< ka_r << " " << ka_g << " " << ka_b << " " 
				<< kd_r << " " << kd_g << " " << kd_b << " " 
				<< ks_r << " " << ks_g << " " << ks_b << " " 
				<<  m  << " " << mirror << std::endl;

				// erstelle Objekt
				Material mat { material_name, {ka_r, ka_g, ka_b}, {kd_r, kd_g, kd_b}, {ks_r, ks_g, ks_b}, m, mirror };
				auto material = std::make_shared<Material>(mat);

				// f�ge Objekt zu Container hinzu
				std::pair<std::string, std::shared_ptr<Material>> pair{ material_name, material };
				scene.materialMap.insert(pair);
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

					// bef�lle Variablen
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
					auto material = find_material(material_name, scene.materialMap);
					//auto material = materialMap.find(material_name)->second;
					Box bo = { {min_x, min_y, min_z}, {max_x, max_y, max_z}, box_name, material };
					auto box = std::make_shared<Box>(bo);

					// f�ge Objekt zu Container hinzu
					scene.shapeVec.push_back(box);
				}

				if ("sphere" == identifier)
				{
					// erstelle Variablen
					std::string sphere_name;
					float center_x, center_y, center_z;
					float radius;
					std::string material_name;

					// bef�lle Variablen
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
					auto material = find_material(material_name, scene.materialMap);
					//auto material = materialMap.find(material_name)->second;
					Sphere sphe{ { center_x, center_y, center_z }, radius, sphere_name, material };
					auto sphere = std::make_shared<Sphere>(sphe);
          
					// f�ge Objekt zu Container hinzu
					scene.shapeVec.push_back(sphere);
				}
			}
		
			if ("light" == identifier) 
			{
				// erstelle Variablen
				std::string light_name;
				float pos_x, pos_y, pos_z;
				float color_r, color_g, color_b;
				float brightness;

				// bef�lle Variablen
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

				// f�ge Objekt zu Container hinzu
				scene.lightVec.push_back(light);
			}
		
			if ("ambient" == identifier) 
			{
				// erstelle Variablen
				float color_r, color_g, color_b;

				// bef�lle Variablen
				line_string_stream >> color_r;
				line_string_stream >> color_g;
				line_string_stream >> color_b;

				// gib Variablen aus
				std::cout << "ambient "
				<< color_r << " " << color_g << " " << color_b <<
				std::endl;

				// f�ge Werte ein
				scene.ambient = { color_r, color_g, color_b };
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
					<< up_x << " " << up_y << " " << up_z 
					<< std::endl;

				cam = Camera{ name, fov_x, { eye_x, eye_y, eye_z }, { dir_x, dir_y, dir_z }, { up_x, up_y, up_z } };
			}
		}

		if ("transform" == identifier) {
			std::string name;
			line_string_stream >> name;

			if (cam.name_ == name) {

				std::string transformation;
				line_string_stream >> transformation;

				if ("scale" == transformation) {
					glm::vec3 scale_vec;
					line_string_stream >> scale_vec.x;
					line_string_stream >> scale_vec.y;
					line_string_stream >> scale_vec.z;

					std::cout << transformation << " " << name << " " <<
						scale_vec.x << " " << scale_vec.y << " " << scale_vec.z << std::endl;

					glm::mat4 m = scale(scale_vec);
					cam.world_transformation_ *= m;
				}

				if ("translate" == transformation) {
					glm::vec3 translate_vec;
					line_string_stream >> translate_vec.x;
					line_string_stream >> translate_vec.y;
					line_string_stream >> translate_vec.z;

					std::cout << transformation << " " << name << " " <<
						translate_vec.x << " " << translate_vec.y << " " << translate_vec.z << std::endl;

					glm::mat4 m = translate(translate_vec);
					cam.world_transformation_ *= m;
				}

				if ("rotate" == transformation) {
					float a;
					glm::vec3 rotation;
					line_string_stream >> a;
					line_string_stream >> rotation.x;
					line_string_stream >> rotation.y;
					line_string_stream >> rotation.z;

					std::cout << transformation << " " << name << " " << a <<  " " <<
						rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

					glm::mat4 m = rotate(rotation, a);
					cam.world_transformation_ *= m;
				}
			}

			for (std::shared_ptr<Shape> shape : scene.shapeVec )
				if (shape->getName() == name) {

					std::string transformation;
					line_string_stream >> transformation;

					if ("scale" == transformation) {

						glm::vec3 scale_vec;
						line_string_stream >> scale_vec.x;
						line_string_stream >> scale_vec.y;
						line_string_stream >> scale_vec.z;

						std::cout << name << " " << transformation << " " <<
							scale_vec.x << " " << scale_vec.y << " " << scale_vec.z << std::endl;

						glm::mat4 m = scale(scale_vec);
						glm::mat4 transformation_m = shape->getWorldTrans();
						transformation_m *= m;
						shape->setWorldTrans(transformation_m);
					}

					if ("translate" == transformation) {

						glm::vec3 translate_vec;
						line_string_stream >> translate_vec.x;
						line_string_stream >> translate_vec.y;
						line_string_stream >> translate_vec.z;

						std::cout << name << " " << transformation << " " <<
							translate_vec.x << " " << translate_vec.y << " " << translate_vec.z << std::endl;

						glm::mat4 m = translate(translate_vec);
						glm::mat4 transformation_m = shape->getWorldTrans();
						transformation_m *= m;
						shape->setWorldTrans(transformation_m);
					}

					if ("rotate" == transformation) {

						float angle;
						glm::vec3 rotation_vec;

						line_string_stream >> angle;
						line_string_stream >> rotation_vec.x;
						line_string_stream >> rotation_vec.y;
						line_string_stream >> rotation_vec.z;
						
						std::cout << name << " " << transformation << " "  << angle << " " <<
							rotation_vec.x << " " << rotation_vec.y << " " << rotation_vec.z << std::endl;

						glm::mat4 m = rotate(rotation_vec, angle);
						glm::mat4 transformation_m = shape->getWorldTrans();
						transformation_m *= m;
						shape->setWorldTrans(transformation_m);
					}
				}
		}
		
		if ("render" == identifier)
		{
			unsigned width;
			unsigned height;
			std::string filename;

			line_string_stream >> filename;
			line_string_stream >> width;
			line_string_stream >> height;

			Renderer renderer{ width, height, filename };
			renderer.render(cam, scene.shapeVec, scene.lightVec, scene.ambient);

			Window window{ {width, height} };

			while (!window.should_close())
			{
				if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
				{
					window.close();
				}
				window.show(renderer.color_buffer());
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