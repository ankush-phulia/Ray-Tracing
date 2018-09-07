#ifndef Image_H
#define Image_H

#define factor1 30
#define factor2 30
#define factor3 3

#include "Pixel.h"
#include "Ray.h"

class Image {
   public:
    Point center;
    Point top_left_corner;
    double dimX;
    double dimY;
    Pixel bg;
    Pixel **grid;

    Image();
    ~Image();
    Image(double x, double y, double z, double xc, double yc, double zc,
          double Xdim, double Ydim);
    Image(Point &blcorner, Point &cent, double Xdim, double Ydim);
    void setBackground();
    void bitmap(int x, int y, Pixel **grid);
};

#endif
