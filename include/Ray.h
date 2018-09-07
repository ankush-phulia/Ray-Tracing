#ifndef Ray_H
#define Ray_H

#include "Point.h"

class Ray {
   public:
    Point origin, direction;

    Ray();
    Ray(double x, double y, double z);
    Ray(double x1, double y1, double z1, double x2, double y2, double z2);
    Ray(Point &dir);
    Ray(Point &ori, Point &dir);

    inline void setOrigin(double x, double y, double z) { origin.set(x, y, z); }
    inline void setDirection(double x, double y, double z) {
        direction.set(x, y, z);
    }

    inline void printRay() {
        std::cout << "Origin " << origin.x << " " << origin.y << " " << origin.z
                  << std::endl;
        std::cout << "Direction " << direction.x << " " << direction.y << " "
                  << direction.z << std::endl;
    }
};

#endif
