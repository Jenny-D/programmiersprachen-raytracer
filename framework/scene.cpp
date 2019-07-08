#include "scene.hpp"

Scene sdf(std::string const& sdfName) {
	Scene scene;

	std::ifstream input;
	input.open(sdfName);
	std::string buffer;

	while (std::getline(input, buffer))
	{
		std::stringstream line_stream(buffer);
		//liest Zeichen der Zeile als einzelne Strings 
		std::string keyword;

		line_stream >> keyword;
		if ("define" == keyword)
		{
			line_stream >> keyword;
			if ("material" == keyword)
			{
				std::shared_ptr<Material> material_ptr = std::make_shared<Material>();

				line_stream >> material_ptr->name;
				//bei Pointern dereferenzieren ->
				line_stream >> material_ptr->ka_.r;
				line_stream >> material_ptr->ka_.g;
				line_stream >> material_ptr->ka_.b;
				line_stream >> material_ptr->kd_.r;
				line_stream >> material_ptr->kd_.g;
				line_stream >> material_ptr->kd_.b;
				line_stream >> material_ptr->ks_.r;
				line_stream >> material_ptr->ks_.g;
				line_stream >> material_ptr->ks_.b;
				line_stream >> material_ptr->m_;
				//Hier wird jedes durch ein whitespace getrenntes string/float etc. (wird selbstst�ndig interpretiert)
				//in den jeweiligen Variablen gespeichert 

				std::cout << material_ptr->name << ", " << endl;
				std::cout << material_ptr->ka_.r << ", " << material_ptr->ka_.g << ", " << material_ptr->ka_.b << endl;
				std::cout << material_ptr->kd_.r << ", " << material_ptr->kd_.g << ", " << material_ptr->kd_.b << endl;
				std::cout << material_ptr->ks_.r << ", " << material_ptr->ks_.g << ", " << material_ptr->ks_.b << endl;
				std::cout << material_ptr->m_ << endl;

				(scene.materialMap).insert(make_pair(material_ptr->name, material_ptr));
			}
		}
	}
	return scene;
}

std::shared_ptr<Material> vec_find_material(std::string const& input, std::vector<std::string, std::shared_ptr<Material>> const& materialVec) {
	auto i = find_if(materialVec.begin(), materialVec.end(),
		[&input] (std::shared_ptr<Material> const& material)
		{return (material->name) == input;});
}

std::shared_ptr<Material> set_find_material(std::string const& input, std::set<std::string, std::shared_ptr<Material>> const& materialSet) {
	auto i = find_if(materialSet.begin(), materialSet.end(),
		[&input](std::shared_ptr<Material> const& material)
		{return (material->name) == input;});
}

std::shared_ptr<Material> map_find_material(std::string const& input, std::map<std::string, std::shared_ptr<Material>> materialMap) {
	auto i = materialMap.find(input);
	if (i != materialMap.end()) {
		return i->second;
	}
	else {
		return nullptr;
	}
}