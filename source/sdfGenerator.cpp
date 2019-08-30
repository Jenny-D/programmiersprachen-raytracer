#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {

	std::fstream file;

	int i = 1; //für Dateibenennung
	//int a = 1; //für Transformation
	int c = -60; //für Kamerabewegung
	while(i < 121 && /*a < 122 &&*/ c < 61) {
		file.open(("image_" + std::to_string(i) + ".sdf"), std::ios::out); //Dateibenennung durch While-Schleife

		if (file.is_open()) {
			file << "define material red 1 0 0 1 0 0 1 0 0 10 \n";
			file << "define material green 0 1 0 0 1 0 0 1 0 20 \n";
			file << "define material blue 0 0 1 0 0 1 0 0 1 15 \n";
			file << "define material yellow 1 1 0 1 1 0 1 1 0 30 \n";
			file << "define material magenta 1 0 1 1 0 1 1 0 1 50 \n";
			file << "define material cyan 0 1 1 0 1 1 0 1 1 20 \n";
			file << "define material white 1 1 1 1 1 1 1 1 1 20 \n";

			file << "define shape box cyan_box -8 10 -88 8 26 -72 cyan \n";
			file << "define shape box white_box -180 -180 -301 180 180 -300 white \n";
			file << "define shape box yellow_box 20 -14 -85 33 -1 -68 yellow \n";
			file << "define shape box red_box -28 -15 -85 -10 3 -62 red \n";
			file << "define shape sphere blue_sphere 30 0 -75 6 blue \n";
			file << "define shape sphere green_sphere 0 -15 -60 7 green \n";

			//Transformationen mit while-Schleife
			//file << "transform cyan_box rotate " + std::to_string(a) + " 0 0 1 \n";

			file << "define light sun_right 50 0 0 1 1 1 1 \n";
			file << "define ambient .1 .1 .1 \n";

			//Kamera mit while-Schleife bewegen
			file << "define camera eye 70 " + std::to_string(c) + " 0 0 0 0 -1 0 1 0 \n";

			//Rendern mit while-Schleife wegen Dateinamen
			file << "define render image_" + std::to_string(i) + ".ppm 500 500 \n";
		}
		file.close();
		i++;
		//a++;
		c++;
	}

	return 0;
}