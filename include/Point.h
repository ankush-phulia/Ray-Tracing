#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <iostream>

class Point {
   public:
    double x, y, z, w;

    Point(void) : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

    Point(double a, double b, double c) : x(a), y(b), z(c), w(1.0f) {}

    Point(double a, double b, double c, double d) : x(a), y(b), z(c), w(d) {}

    Point(Point &p) {
        x = p.x;
        y = p.y;
        z = p.z;
        w = p.w;
    }

    void set(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }

    inline bool operator==(const Point &v2) {
        return ((v2.x == x) && (v2.y == y) && (v2.z == z) && (v2.w == w));
    }

    inline double Magnitude() { return sqrt(x * x + y * y + z * z); }

    inline void normalise() {
        double m = Magnitude();
        x /= m;
        y /= m;
        z /= m;
    }

    inline double sum() { return x + y + z; }

    inline void Scale(double factor) {
        x *= factor;
        y *= factor;
        z *= factor;
    }

    inline double operator*(const Point &v2) {
        return (x * v2.x + y * v2.y + z * v2.z);
    }

    inline void printPoint() {
        std::cout << x << " " << y << " " << z << std::endl;
    }

    Point operator+(const Point &v2);
    Point operator-(const Point &v2);
    Point operator^(const Point &v2);  // cross product
};

#endif
