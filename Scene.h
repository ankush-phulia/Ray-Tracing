#ifndef Scene_H
#define Scene_H

#include "Ray.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

enum objectType {
	Sphere = 0, Triangle = 1
};

struct object {
	objectType type;
	Point center;
	float extent;

	object() {
		type = Sphere;
		center = Point(0.0f, 0.0f, 0.0f);
		extent = 0;
	}

	object(int type, float x, float y, float z, float ext) {
		center = Point(x, y, z);
		extent = ext;
		if (type == 0) {
			type = Sphere;			
		}
		else {
			type = Triangle;
		}
	}
};

struct light_source {
	Point location;
	float intensity;

	light_source() {
		location = Point(0.0f, 0.0f, 0.0f);
		intensity = 1;
	}

	light_source(float x, float y, float z, float i) {
		location = Point(x, y, z);
		intensity = i;
	}
};

class Scene {

public:
	vector<object> objects;
	vector<light_source> light_sources;
	Ray Camera;

	Scene();
	Scene(string s);

	void printScene();
};


#endif
