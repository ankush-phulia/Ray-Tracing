#ifndef Ray_H
#define Ray_H

#include "Point.h"

class Ray {

public:
	
	Point origin, direction;

	Ray(float x, float y, float z);
	Ray(float x1, float y1, float z1, float x2, float y2, float z2);
	Ray(Point &dir);
	Ray(Point &ori, Point &dir);

};


#endif