#ifndef Camera_H
#define Camera_H

#include "Point.h"

class Camera {

public:
	
	//all in VCS
	Point origin;
	Point u, v, n;

	Camera() {
	}

	Camera(float xe, float ye, float ze, float dx, float dy, float dz,
		float ux, float uy, float uz, float vx, float vy, float vz,
		float nx, float ny, float nz) {
		origin.set(xe, ye, ze);
		//direction.set(dx, dy, dz);
		u.set(ux, uy, uz);
		v.set(vx, vy, vz);
		n.set(nx, ny, nz);
	}

	inline void setOrigin(float x, float y, float z) {
		origin.set(x, y, z);
	}

	inline void setU(float x, float y, float z) {
		u.set(x, y, z);
	}

	inline void setV(float x, float y, float z) {
		v.set(x, y, z);
	}

	inline void setN(float x, float y, float z) {
		n.set(x, y, z);
	}

};


#endif