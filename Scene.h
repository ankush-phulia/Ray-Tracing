#ifndef Scene_H
#define Scene_H

#include "Ray.h"
#include "Camera.h"
#include "Image.h"
#include "Matrix.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

class sphere {
public:
	Point center;
	Pixel color;
	double ka, kd, ks, krg, ktg, mu, n;
	double radius;			// lusture

	sphere() {
		center.set(0.0f, 0.0f, 0.0f);
		radius = 0;
	}

	sphere(double x, double y, double z, double r) {
		center.set(x, y, z);
		radius = r;
	}

	sphere(sphere &s)
	{	center = s.center;
		color = s.color;
		ka = s.ka;
		kd = s.kd;
		ks = s.ks;
		krg = s.krg;
		ktg = s.ktg;
		mu = s.mu;
		n = s.n;
		radius = s.radius;
	}

	void set(double x, double y, double z, double r, double red, double g, double b, double ka1, double kd1, double ks1, double krg1, double ktg1, double mu1, double n1) {
		center.set(x, y, z);
		radius = r;
		color.colorPixel(red, g, b);
		ka = ka1;
		ks = ks1;
		kd = kd1;
		krg = krg1;
		ktg = ktg1;
		mu = mu1;
		n = n1;
	}
};

class triangle {
public:
	Point v1,v2,v3;
	Pixel color;
	double ka, kd, ks, krg, ktg, mu, n;

	triangle() {
	}

	triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
		v1.set(x1, y1, z1);
		v2.set(x2, y2, z2);
		v3.set(x3, y3, z3);
	}

	triangle(triangle &s)
	{	v1 = s.v1;
		v2 = s.v2;
		v3 = s.v3;
		color = s.color;
		ka = s.ka;
		kd = s.kd;
		ks = s.ks;
		krg = s.krg;
		ktg = s.ktg;
		mu = s.mu;
		n = s.n;
	}

	void set(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double r, double g, double b, double ka1, double kd1, double ks1, double krg1, double ktg1, double mu1, double n1) {
		v1.set(x1, y1, z1);
		v2.set(x2, y2, z2);
		v3.set(x3, y3, z3);
		color.colorPixel(r, g, b);
		ka = ka1;
		ks = ks1;
		kd = kd1;
		krg = krg1;
		ktg = ktg1;
		mu = mu1;
		n = n1;
	}
};

class light_source {
public:
	Point location;
	double intensity;

	light_source() {
		location.set(0.0f, 0.0f, 0.0f);
		intensity = 1;
	}

	light_source(double x, double y, double z, double i) {
		location.set(x, y, z);
		intensity = i;
	}
	light_source(light_source &l)
	{	location = l.location;
		intensity = l.intensity;
	}
};

class Scene {

public:

	Camera camera;
	Point VCSOrigin;
	Matrix VCStoWCS;
	Image display; //location of the display
	light_source *light_sources;
	double ambient_light, bgr, bgg, bgb;
	sphere *Spheres;
	triangle *Triangles;
	int sn,tn,ln;

	Scene();
	~Scene();
	Scene(const char *);

	bool existRoot(const double &a, const double &b, const double &c, double &x0, double &x1);
	bool RaySphereIntersect(Ray &ray, sphere &sphere, double &t, Point &intersection);
	bool RayTriangleIntersect(Ray &ray, triangle &triangle, double &t, Point &intersection);
	bool recursiveRayTrace(Ray &ray, double refractive_index, bool recurse, Pixel &, int);
	void writeImage();
	void printImage();
};


#endif
