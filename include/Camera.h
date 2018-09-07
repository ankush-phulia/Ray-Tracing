#ifndef Camera_H
#define Camera_H

#include "Point.h"

class Camera {
   public:
    // all in VCS
    Point origin;
    Point u, v, n;

    Camera() {}

    Camera(double xe, double ye, double ze, double dx, double dy, double dz,
           double ux, double uy, double uz, double vx, double vy, double vz,
           double nx, double ny, double nz) {
        origin.set(xe, ye, ze);
        // direction.set(dx, dy, dz);
        u.set(ux, uy, uz);
        u.normalise();
        v.set(vx, vy, vz);
        v.normalise();
        n.set(nx, ny, nz);
        n.normalise();
    }

    inline void setOrigin(double x, double y, double z) { origin.set(x, y, z); }

    inline void setU(double x, double y, double z) {
        u.set(x, y, z);
        u.normalise();
    }

    inline void setV(double x, double y, double z) {
        v.set(x, y, z);
        v.normalise();
    }

    inline void setN(double x, double y, double z) {
        n.set(x, y, z);
        n.normalise();
    }
};

#endif
