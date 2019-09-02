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
	int a = -1; //für Schneeflocken
	//int b = 0; //für Wolke
	int c = 25; //für Kamera
	while(i < 121) {
		file.open(("image_" + std::to_string(i) + ".sdf"), std::ios::out); 

		if (file.is_open()) {
			file << "define material black 0 0 0 0 0 0 0 0 0 20 \n";
			file << "define material red 1 0 0 1 0 0 1 0 0 10 \n";
			file << "define material green 0 1 0 0 1 0 0 1 0 20 \n";
			file << "define material blue 0 0 1 0 0 1 0 0 1 15 \n";
			file << "define material yellow 1 1 0 1 1 0 1 1 0 30 \n";
			file << "define material magenta 1 0 1 1 0 1 1 0 1 50 \n";
			file << "define material cyan 0 1 1 0 1 1 0 1 1 20 \n";
			file << "define material white 1 1 1 1 1 1 1 1 1 20 \n";
			file << "define material orange 1 0.2 0.2 1 0.2 0.2 1 0.2 0.2 20 \n";

			file << "define shape box green_ground_box -1500 -35 -300 1500 -30 -1 green \n";
			file << "define shape box blue_sky_box -1500 -30 -305 1500 4000 -300 blue \n";
			file << "define shape box blue_sky_box_left -1505 -30 -300 -1500 4000 -1 blue \n";
			file << "define shape box blue_sky_box_right 1500 -30 -300 1505 4000 -1 blue \n";
			file << "define shape sphere snowman_1 0 -18 -100 12 white \n";
			file << "define shape sphere snowman_2 0 2 -100 10 white \n";
			file << "define shape sphere snowman_3 0 19 -100 8 white \n";
			file << "define shape sphere black_button_1 0 -19 -89 1.5 black \n";
			file << "define shape sphere black_button_2 0 -12 -90.7 1.5 black \n";
			file << "define shape sphere black_button_3 0 2 -91 1.5 black \n";
			file << "define shape sphere eye_1 -2 21 -93.5 1.5 black \n";
			file << "define shape sphere eye_2 2 21 -93.5 1.5 black \n";
			file << "define shape box mouth -3.7 16 -93.2 3.7 17 -92.2 black \n";
			file << "define shape box carrot -0.8 17.7 -93 0.8 19.3 -88 orange \n";
			file << "define shape box hat_1 -7 26 -107 7 29 -93 black \n";
			file << "define shape box hat_2 -5 29 -105 5 35 -95 black \n";
			file << "define shape sphere cloud_1 55 85 -200 10 white \n";
			file << "define shape sphere cloud_2 65 77 -192 13 white \n";
			file << "define shape sphere cloud_3 80 79 -191 17 white \n";
			file << "define shape sphere cloud_4 99 85 -200 15 white \n";
			file << "define shape sphere cloud_5 68 95 -205 12 white \n";
			file << "define shape sphere cloud_6 89 96 -206 16 white \n";
			file << "define shape sphere snowflake_1 -5 70 -190 1 white \n";
			file << "define shape sphere snowflake_2 -16 50 -127 1 white \n";
			file << "define shape sphere snowflake_3 -7 67 -152 1 white \n";
			file << "define shape sphere snowflake_4 61 42 -182 1 white \n";
			file << "define shape sphere snowflake_5 56 37 -196 1 white \n";
			file << "define shape sphere snowflake_6 45 42 -132 1 white \n";
			file << "define shape sphere snowflake_7 35 44 -187 1 white \n";
			file << "define shape sphere snowflake_8 -41 62 -142 1 white \n";
			file << "define shape sphere snowflake_9 -32 71 -154 1 white \n";
			file << "define shape sphere snowflake_10 -49 55 -194 1 white \n";
			file << "define shape sphere snowflake_11 15 47 -187 1 white \n";
			file << "define shape sphere snowflake_12 73 52 -144 1 white \n";
			file << "define shape sphere snowflake_13 7 61 -155 1 white \n";
			file << "define shape sphere snowflake_14 21 56 -67 1 white \n";
			file << "define shape sphere snowflake_15 -6 48 -63 1 white \n";
			file << "define shape sphere snowflake_16 11 75 -149 1 white \n";
			file << "define shape sphere snowflake_17 26 62 -169 1 white \n";
			file << "define shape sphere snowflake_18 -51 42 -142 1 white \n";
			file << "define shape sphere snowflake_19 77 41 -128 1 white \n";
			file << "define shape sphere snowflake_20 69 40 -141 1 white \n";
			file << "define shape sphere snowflake_21 -16 95 -176 1 white \n";
			file << "define shape sphere snowflake_22 17 110 -165 1 white \n";
			file << "define shape sphere snowflake_23 -19 86 -134 1 white \n";
			file << "define shape sphere snowflake_24 -45 111 -144 1 white \n";
			file << "define shape sphere snowflake_25 7 117 -69 1 white \n";
			file << "define shape sphere snowflake_26 -51 97 -188 1 white \n";
			file << "define shape sphere snowflake_27 31 89 -164 1 white \n";
			file << "define shape sphere snowflake_28 0 101 -155 1 white \n";
			file << "define shape sphere snowflake_29 25 107 -172 1 white \n";
			file << "define shape sphere snowflake_30 -15 109 -161 1 white \n";
			file << "define shape sphere snowflake_31 0 108 -144 1 white \n";
			file << "define shape sphere snowflake_32 -39 70 -118 1 white \n";
			file << "define shape sphere snowflake_33 25 61 -131 1 white \n";
			file << "define shape sphere snowflake_34 48 114 -198 1 white \n";
			file << "define shape sphere snowflake_35 72 126 -196 1.6 white \n";
			file << "define shape sphere snowflake_36 95 131 -193 1.2 white \n";
			file << "define shape sphere snowflake_37 83 145 -201 1.5 white \n";
			file << "define shape sphere snowflake_38 108 117 -205 1.6 white \n";
			file << "define shape sphere snowflake_39 54 123 -186 1.2 white \n";
			file << "define shape sphere snowflake_40 51 149 -178 1 white \n";
			file << "define shape sphere snowflake_41 77 96 -197 1 white \n";
			file << "define shape sphere snowflake_42 82 84 -201 1.1 white \n";
			file << "define shape sphere snowflake_43 58 154 -210 1.8 white \n";
			file << "define shape sphere snowflake_44 68 109 -194 1.4 white \n";
			file << "define shape sphere snowflake_45 55 87 -197 1.5 white \n";
			file << "define shape sphere snowflake_46 -37 134 -179 1.2 white \n";

			//Transformationen mit while-Schleife
			file << "transform snowflake_1 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_2 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_3 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_4 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_5 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_6 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_7 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_8 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_9 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_10 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_11 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_12 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_13 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_14 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_15 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_16 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_17 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_18 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_19 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_20 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_21 translate 0 " + std::to_string(a) + " 0 \n"; 
			file << "transform snowflake_22 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_23 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_24 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_25 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_26 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_27 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_28 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_29 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_30 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_31 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_32 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_33 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_34 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_35 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_36 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_37 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_38 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_39 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_40 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_41 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_42 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_43 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_44 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_45 translate 0 " + std::to_string(a) + " 0 \n";
			file << "transform snowflake_46 translate 0 " + std::to_string(a) + " 0 \n";

			/*file << "transform cloud_1 translate " + std::to_string(b) + " 0 0 \n";
			file << "transform cloud_2 translate " + std::to_string(b) + " 0 0 \n";
			file << "transform cloud_3 translate " + std::to_string(b) + " 0 0 \n";
			file << "transform cloud_4 translate " + std::to_string(b) + " 0 0 \n";
			file << "transform cloud_5 translate " + std::to_string(b) + " 0 0 \n";
			file << "transform cloud_6 translate " + std::to_string(b) + " 0 0 \n";*/

			file << "define light sun_left -50 30 0 1 1 1 1 \n";
			file << "define ambient .1 .1 .1 \n";

			//Kamera mit while-Schleife bewegen
			file << "define camera eye " + std::to_string(c) + " 15 10 0 0 0 -1 0 1 0 \n";
			//file << "define camera eye 55 15 10 0 0 0 -1 0 1 0 \n";

			//Rendern mit while-Schleife wegen Dateinamen
			file << "define render image_" + std::to_string(i) + ".ppm 500 500 \n";
		}
		file.close();
		i++;
		a--;
		//b--;
		c++;
	}

	return 0;
}