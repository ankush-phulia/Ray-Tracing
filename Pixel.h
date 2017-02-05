#ifndef Pixel_H
#define Pixel_H

class Pixel {

public:
	float r, g, b;

	Pixel(void) :
		r(0.0f), g(0.0f), b(0.0f) {
	}

	inline void colorPixel(float x ,float y, float z) {
		r = x; g = y; b = z;
	}

	inline void clearPixel() {
		r = 0; g = 0; b = 0;
	}

	
};


#endif