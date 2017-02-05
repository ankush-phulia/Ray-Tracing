#include "Vector.h"

Vector Vector::operator+(const Vector &v2){
	Vector v(x, y, z, w);
	v.x += v2.x;
	v.y += v2.y;
	v.z += v.z;
}

Vector Vector::operator-(const Vector &v2){
	Vector v(x, y, z, w);
	v.x -= v2.x;
	v.y -= v2.y;
	v.z -= v.z;
}
