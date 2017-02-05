#include "Ray.h"

Ray::Ray(){
	origin = Point(0, 0, 0);
}

Ray::Ray(float x, float y, float z){
	origin = Point(0, 0, 0);
	direction = Point(x, y, z);
}

Ray::Ray(float x1, float y1, float z1, float x2, float y2, float z2){
	origin = Point(x1, y1, z1);
	direction = Point(x2, y2, z2);
}

Ray::Ray(Point &dir){
	origin = Point(0, 0, 0);
	direction = dir;
}

Ray::Ray(Point &ori, Point &dir){
	origin = ori;
	direction = dir;
}
