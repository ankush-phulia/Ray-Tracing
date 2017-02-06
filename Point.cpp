#include "Point.h"

Point Point::operator+(const Point &v2){
	Point v(x, y, z, w);
	v.x += v2.x;
	v.y += v2.y;
	v.z += v.z;
	return v;
}

Point Point::operator-(const Point &v2){
	Point v(x, y, z, w);
	v.x -= v2.x;
	v.y -= v2.y;
	v.z -= v.z;
	return v;
}

Point Point::operator^(const Point & v2){
	Point v(x, y, z, w);
	v.x = y * v2.z - v2.y * z;
	v.y = z * v2.x - v2.z * x;
	v.z = x * v2.y - v2.x * y;
	return v;
}
