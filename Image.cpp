#include "Image.h"

Image::Image(float x, float y, float z, float xc, float yc, float zc, float Xdim, float Ydim){
	center = Point(xc, yc, zc);
	bottom_left_corner = Point(x, y, z);
	dimX = Xdim;
	dimY = Ydim;
	grid = new Pixel*[floor(dimX)];
	for (int i = 0; i<floor(dimX); i++) {
		grid[i] = new Pixel[floor(dimY)];
	}
}

Image::Image(Point &blcorner, Point & cent, float Xdim, float Ydim){
	bottom_left_corner = blcorner;
	center = cent;
	dimX = Xdim;
	dimY = Ydim;
}
