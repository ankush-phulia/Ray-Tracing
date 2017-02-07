#include "Ray.h"

Ray::Ray(){
	origin.set(0, 0, 0);
}

Ray::Ray(double x, double y, double z){
	origin.set(0, 0, 0);
	direction.set(x, y, z);
}

Ray::Ray(double x1, double y1, double z1, double x2, double y2, double z2){
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
