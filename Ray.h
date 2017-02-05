#ifndef Ray_H
#define Ray_H

#include "Point.h"

class Ray {

public:
	
	Point origin, direction;

	Ray();
	Ray(float x, float y, float z);
	Ray(float x1, float y1, float z1, float x2, float y2, float z2);
	Ray(Point &dir);
	Ray(Point &ori, Point &dir);

	inline void setOrigin(float x, float y, float z) {
		origin = Point(x, y, z);
	}
	inline void setDirection(float x, float y, float z) {
		direction = Point(x, y, z);
	}

};


#endif