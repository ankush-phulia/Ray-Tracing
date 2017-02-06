#ifndef PIXEL_H
#define PIXEL_H

class Pixel {

public:
	float r, g, b;

	Pixel(){
		r = (0.0f); g = (0.0f); b = (0.0f);
	}

	Pixel(Pixel &P)
	{	r = P.r;
		g = P.g;
		b = P.b;
	}

	inline void colorPixel(float x ,float y, float z) {
		r = x; g = y; b = z;
	}

	inline void clearPixel() {
		r = 0; g = 0; b = 0;
	}

	inline void Scale(float x)
	{	r *= x;
		g *= x;
		b *= x;
	}

	Pixel operator+(const Pixel &v2){
		Pixel v;
		v.colorPixel(r,g,b);
		v.r += v2.r;
		v.g += v2.g;
		v.b += v2.b;
		return v;
	}


};


#endif
