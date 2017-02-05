#include "Point.h"

Point Point::addSub(Point v2, bool op) {
	Point v(x, y, z, w);
	if (op) {
		v.x += v2.x;
		v.y += v2.y;
		v.z += v.z;
	}
}

