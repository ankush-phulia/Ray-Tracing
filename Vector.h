#ifndef VECTOR_H
#define VECTOR_H
#include<math.h>
class Vector {

public:
	float x, y, z, w;

	Vector(void) :
		x(0.0f), y(0.0f), z(0.0f), w(1.0f) {
	}

	Vector(float a, float b, float c) :
		x(a), y(b), z(c), w(1.0f) {
	}

	Vector(float a, float b, float c, float d) :
		x(a), y(b), z(c), w(d) {
	}

	inline bool operator==(const Vector & v2) {
		return ((v2.x == x) && (v2.y == y) && (v2.z == z) && (v2.w == w));
	}

	inline float Magnitude() {
		return sqrt(x*x + y*y + z*z);
	}

	inline void Scale(float factor) {
		x *= factor; y *= factor; z *= factor;
	}

	inline float operator*(const Vector &v2) {
		return (x*v2.x + y*v2.y + z*v2.z);
	}

	Vector operator+(const Vector &v2);
	Vector operator-(const Vector &v2);

};


#endif
