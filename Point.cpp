#include "Point.h"

Point Point::add(const Point &v2){
	Point v(x, y, z, w);
	v.x += v2.x;
	v.y += v2.y;
	v.z += v.z;
	return v;
}

Point Point::sub(const Point &v2){
	Point v(x, y, z, w);
	v.x -= v2.x;
	v.y -= v2.y;
	v.z -= v.z;
	return v;
}
