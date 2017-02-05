#ifndef VECTOR_H
#define VECTOR_H

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

	inline bool isEqual(Vector v2) {
		return (v2.x == x)&(v2.y == y)&(v2.z == z)&(v2.w == w);
	}

	inline float magnitude() {
		return (x*x + y*y + z*z);
	}

	inline void scale(float factor) {
		x *= factor; y *= factor; z *= factor;
	}

	inline float dotProduct(Vector v2) {
		return (x*v2.x + y*v2.y + z*v2.z);
	}

	Vector addSub(Vector v2, bool op);

};


#endif