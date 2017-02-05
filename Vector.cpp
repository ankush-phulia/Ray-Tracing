#include "Vector.h"

Vector Vector::addSub(Vector v2, bool op) {
	Vector v(x, y, z, w);
	if (op) {
		v.x += v2.x;
		v.y += v2.y;
		v.z += v.z;
	}
}

