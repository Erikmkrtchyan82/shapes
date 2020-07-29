#include <iostream>
#include <string>
#include "shape.h"

std::string generate() {
	std::string text {};

	text += "C 5 -9 1\n";
	text += "C 8 -88 9.1\n";
	text += "C 5 -9 6\n";
	//	text += "C 1 0 -2\n";
	//	text += "C 1 0 0\n";
	text += "R -4.5 6 3 -1\n";
	text += "R 8 -5.26 9 -7\n";
	text += "R -1 1 2 -3\n";
	//	text += "R 5 6 1 2 \n";
	text += "P 5 2.85\n";
	text += "P 4 2\n";
	text += "P 8 5\n";
	text += "P -94 5\n";
	//	text += "Po 1 3\n";
	text += "T 4 5 -99 4 12 5\n";
	text += "T 9 -7 4 -2 2 5\n";
	text += "T 6 4 6 8 7 4\n";
	text += "T 0 9.4 2 1 1 0\n";
	text += "T 3 0 0 -10 100 0\n";
	//	text += "T 1a 2 1 2 3 4\n";
	//	text += "T 1 2 3 4 5\n";
	//	text += "T 1 2 3 3 4 5 6\n";
	//	text += "T 1 2 3 4 5 6\n";
	//	text += "T 1 1 6 6 -9 -9\n";
	return text;
}

int main() {

	std::string text = generate();
	constexpr int polymorphism_mechanism = 0;

	std::cout << sort_shape_areas( text, polymorphism_mechanism ) << std::endl;

	return 0;
}
