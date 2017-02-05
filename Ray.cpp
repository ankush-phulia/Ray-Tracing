#include "Ray.h"

Ray::Ray(){
	origin.set(0, 0, 0);
}

Ray::Ray(float x, float y, float z){
	origin.set(0, 0, 0);
	direction.set(x, y, z);
}

Ray::Ray(float x1, float y1, float z1, float x2, float y2, float z2){
	origin.set(x1, y1, z1);
	direction.set(x2, y2, z2);
}

Ray::Ray(Point &dir){
	origin.set(0, 0, 0);
	direction = dir;
}

Ray::Ray(Point &ori, Point &dir){
	origin = ori;
	direction = dir;
}
