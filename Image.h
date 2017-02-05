#ifndef Image_H
#define Image_H

#include "Pixel.h"
#include "Ray.h"

class Image {

public:
	
	Point center;
	Point bottom_left_corner;
	float dimX;
	float dimY;
	Pixel **grid;

	Image();
	Image(float x, float y, float z, float xc, float yc, float zc, float Xdim, float Ydim);
	Image(Point &blcorner, Point &cent, float Xdim, float Ydim);


};


#endif