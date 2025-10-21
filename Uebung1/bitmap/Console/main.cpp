#include <iostream>

#include "Bitmap.h"

int main() {
	Bitmap bmp{};

	if (bmp.read("../../Images/rgb1.bmp")) {
		std::cout << "Bitmap successfully read" << std::endl;
		//bmp.invert(); // ok
		bmp.horFlip(); // ok
		//bmp.verFlip(); // ok
		//Bitmap bmp2 = bmp.cvtToRGB(); // ok
		//Bitmap bmp2 = bmp.cvtToARGB(); // ok
		if (bmp.write("../../Images/out.bmp")) {
			std::cout << "Bitmap successfully written" << std::endl;
		}
	}
}