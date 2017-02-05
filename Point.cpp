#include "Point.h"

Point Point::operator+(const Point &v2){
	Point v(x, y, z, w);
	v.x += v2.x;
	v.y += v2.y;
	v.z += v.z;
}

Point Point::operator-(const Point &v2){
	Point v(x, y, z, w);
	v.x -= v2.x;
	v.y -= v2.y;
	v.z -= v.z;
}
