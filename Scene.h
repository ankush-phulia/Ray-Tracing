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
	float ka, kd, ks, krg, ktg, mu, n;
	float radius;			// lusture

	sphere() {
		center.set(0.0f, 0.0f, 0.0f);
		radius = 0;
	}

	sphere(float x, float y, float z, float r) {
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

	void set(float x, float y, float z, float r, float red, float g, float b, float ka1, float kd1, float ks1, float krg1, float ktg1, float mu1, float n1) {
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
	float ka, kd, ks, krg, ktg, mu, n;

	triangle() {
	}

	triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
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

	void set(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float r, float g, float b, float ka1, float kd1, float ks1, float krg1, float ktg1, float mu1, float n1) {
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
	float intensity;

	light_source() {
		location.set(0.0f, 0.0f, 0.0f);
		intensity = 1;
	}

	light_source(float x, float y, float z, float i) {
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
	light_source light_sources[10];
	float ambient_light, bgr, bgg, bgb;
	sphere Spheres[10];
	triangle Triangles[10];
	int sn,tn,ln;

	Scene();
	Scene(const char *);

	bool existRoot(const float &a, const float &b, const float &c, float &x0, float &x1);
	bool RaySphereIntersect(Ray &ray, sphere &sphere, float &t, Point &intersection);
	bool RayTriangleIntersect(Ray &ray, triangle &triangle, float &t, Point &intersection);
	bool recursiveRayTrace(Ray &ray, float refractive_index, bool recurse, Pixel &);
	void writeImage();
	void printImage();
};


#endif
