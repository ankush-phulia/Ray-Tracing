#include "Scene.h"

Scene::Scene(){
}

Scene::Scene(string s){
	ifstream f_in;
	f_in.open(s);
	while (f_in.is_open()) {
		string buffer;
		float a, b, c, d, n, r, g, bl, ka, kd, ks, krg, ktg, mu;
		while (f_in >> buffer) {
			if (buffer == "Camera") {
				f_in >> a >> b >> c;
				Camera.setOrigin(a, b, c);
				f_in >> a >> b >> c;
				Camera.setU(a, b, c);
				f_in >> a >> b >> c;
				Camera.setV(a, b, c);
				f_in >> a >> b >> c;
				Camera.setN(a, b, c);				
			}
			else if (buffer == "Display") {
				f_in >> a >> b >> c;
				display.center.set(a, b, c);
				VCSOrigin.set(a, b, c);
				f_in >> a >> b >> c >> d;
				display.dimX = b - a;
				display.dimY = c - d;
			}
			else if (buffer == "Light-sources") {
				f_in >> a >> b >> c >> d;
				ambient_light = a;
				bgr = b;
				bgg = c;
				bgb = d;
				f_in >> n;
				light_sources.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d;
					light_sources[i] = (light_source(a, b, c, d));
				}
			}
			else if (buffer == "Spheres") {
				f_in >> n;
				Spheres.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d >> r >> g >> bl >> ka >> kd >> ks >> krg >> ktg >> mu;
					Spheres[i] = (sphere(a, b, c, d, r, g, bl, ka, kd, ks, krg, ktg, mu));
				}
			}
			else if (buffer == "Triangles") {
				float a1, b1, c1, a2, b2, c2;
				f_in >> n;
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> r >> g >> bl >> ka >> kd >> ks >> krg >> ktg >> mu;
					Triangles.push_back(triangle(a,b,c,a1,b1,c1,a2,b2,c2,r,g,bl, ka, kd, ks, krg, ktg, mu));
				}
			}
		}
		f_in.close();
	}
}

bool existRoot(const float &a, const float &b, const float &c, float &x0, float &x1) {
	float discr = b * b - 4 * a * c;
	if (discr < 0) {
		return false;
	}
	else if (discr == 0) {
		x0 = x1 = -0.5 * b / a;
	}
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1)
		swap(x0, x1);
	return true;
}

bool Scene::RaySphereIntersect(Ray & ray, sphere & sphere, Point &intersection){
	float a, b, c, d, t1, t2;
	Point temp = ray.origin - sphere.center;
	Point tmpdir = ray.direction;
	tmpdir.normalise();
	
	a = (tmpdir*tmpdir);
	b = 2 * (tmpdir * temp);
	c = temp*temp - sphere.radius*sphere.radius;
	
	if (!existRoot(a, b, c, t1, t2)) {
		return false;
	}
	else {
		if (t1 > t2) {
			swap(t1, t2);
		}
		if (t1 < 0) {
			if (t2 < 0) {
				return false;
			}
			else {
				tmpdir.Scale(t2);
				intersection = (ray.origin + tmpdir);
			}
		}
		else {
			tmpdir.Scale(t1);
			intersection = (ray.origin + tmpdir);
		}
	}
	return true;
}

bool Scene::RayTriangleIntersect(Ray & ray, triangle & triangle, Point &intersection){
	Point e1, e2, h, s, q, tmpdir;
	float a, f, u, v;
	tmpdir.normalise();

	e1 = triangle.v2 - triangle.v1;
	e2 = triangle.v3 - triangle.v1;
	h = ray.direction ^ e2;
	a = e1 * h;
	f = 1.0f / a;

	s = ray.origin - triangle.v1;
	u = (s * h) * f;
	if (u < 0.0 || u > 1.0) {
		return false;
	}

	q = s ^ triangle.v2;
	v = (ray.direction * q) * f;
	if (v < 0.0 || v > 1.0) {
		return false;
	}

	float t = (triangle.v3 * q) * f;
	if (t > 0) {
		tmpdir.Scale(t);
		intersection = ray.origin + tmpdir;
		return true;
	}
	return false;
}

void Scene::printScene(){
	cout << light_sources.size() << endl;
	//cout << objects.size() << endl;
}
