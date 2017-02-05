#ifndef Point_H
#define Point_H

#include <math.h>

class Point {

public:
	float x, y, z, w;

	Point(void) :
		x(0.0f), y(0.0f), z(0.0f), w(1.0f) {
	}

	Point(float a, float b, float c) :
		x(a), y(b), z(c), w(1.0f) {
	}

	Point(float a, float b, float c, float d) :
		x(a), y(b), z(c), w(d) {
	}

	void set(float a, float b, float c) {
		x = a; y = b; z = c;
	}

	inline bool operator==(const Point & v2) {
		return ((v2.x == x) && (v2.y == y) && (v2.z == z) && (v2.w == w));
	}

	inline float Magnitude() {
		return sqrt(x*x + y*y + z*z);
	}

	inline void normalise() {
		float m = Magnitude();
		x /= m; y /= m; z /= m;
	}

	inline float sum() {
		return x + y + z;
	}

	inline void Scale(float factor) {
		x *= factor; y *= factor; z *= factor;
	}

	inline float operator*(const Point &v2) {
		return (x*v2.x + y*v2.y + z*v2.z);
	}
	
	Point operator+(const Point &v2);
	Point operator-(const Point &v2);
	Point operator^(const Point &v2); //cross product
	
};


#endif
