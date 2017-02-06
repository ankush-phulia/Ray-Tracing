#include "Scene.h"
Scene::Scene(){
}

Scene::Scene(const char* s){
	ifstream f_in;
	f_in.open(s);
	while (f_in.is_open()) {
		char buffer[20];
		unsigned int n;
		float a, b, c, d, r, g, bl, ka, kd, ks, krg, ktg, mu, nn;
		while (f_in >> buffer) {
			if (buffer == "Camera") {
				f_in >> a >> b >> c;
				camera.setOrigin(a, b, c);
				f_in >> a >> b >> c;
				camera.setU(a, b, c);
				f_in >> a >> b >> c;
				camera.setV(a, b, c);
				f_in >> a >> b >> c;
				camera.setN(a, b, c);
				float M[4][4];
				M[0][0] = camera.u.x;
				M[0][1] = camera.u.y;
				M[0][2] = camera.u.z;
				M[0][3] = 0;
				M[1][0] = camera.v.x;
				M[1][1] = camera.v.y;
				M[1][2] = camera.v.z;
				M[1][3] = 0;
				M[2][0] = camera.n.x;
				M[2][1] = camera.n.y;
				M[2][2] = camera.n.z;
				M[2][3] = 0;
				M[3][0] = 0;
				M[3][1] = 0;
				M[3][2] = 0;
				M[3][3] = 1;
				VCStoWCS = Matrix(M);
			}
			else if (buffer == "Display") {
				f_in >> a >> b >> c;
				display.center.set(a, b, c);
				VCSOrigin.set(a, b, c);
				f_in >> a >> b >> c >> d;
				display.dimX = b - a;
				display.dimY = c - d;
				display.bottom_left_corner.set(-display.dimX/2,-display.dimY/2,0.0);
			}
			else if (buffer == "Light") {
				f_in >> a >> b >> c >> d;
				ambient_light = a;
				bgr = b;
				bgg = c;
				bgb = d;
				display.bg.colorPixel(bgr, bgg, bgb);
				display.setBackground();
				f_in >> n;
				//light_sources.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d;
					light_sources[i] = (light_source(a, b, c, d));
				}
			}
			else if (buffer == "Spheres") {
				f_in >> n;
				//Spheres.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d >> r >> g >> bl >> ka >> kd >> ks >> krg >> ktg >> mu >> nn;
					Spheres[i].set(a, b, c, d, r, g, bl, ka, kd, ks, krg, ktg, mu, nn);
				}
			}
			else if (buffer == "Triangles") {
				float a1, b1, c1, a2, b2, c2;
				f_in >> n;
				//Triangles.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> r >> g >> bl >> ka >> kd >> ks >> krg >> ktg >> mu >> nn;
					Triangles[i].set(a,b,c,a1,b1,c1,a2,b2,c2,r,g,bl, ka, kd, ks, krg, ktg, mu, nn);
				}
			}
		}
		f_in.close();
	}
}

bool Scene::existRoot(const float &a, const float &b, const float &c, float &x0, float &x1) {
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

bool Scene::RaySphereIntersect(Ray & ray, sphere & sphere, float &t, Point &intersection){
	float a, b, c, t1, t2;
	Point temp;
	temp = ray.origin - sphere.center;
	Point tmpdir(ray.direction);
	//tmpdir.normalise();
	//tmpdir.printPoint();
	a = (tmpdir * tmpdir);
	//temp.printPoint();
	b = 2 * (tmpdir * temp);
	//temp.printPoint();
	c = temp*temp - sphere.radius*sphere.radius;
	//std::cout << a << " " << b << " " << c << " " << sphere.radius<<  std::endl;

	if (!existRoot(a, b, c, t1, t2)) {
		return false;
	}
	else {
		if (t1 > t2) {
			swap(t1, t2);
		}
		if (t1 <= 0) {
			if (t2 <= 0) {
				return false;
			}
			else {
				t = t2;
				tmpdir.Scale(t2);
				intersection = (ray.origin + tmpdir);
			}
		}
		else {
			t = t1;
			tmpdir.Scale(t1);
			intersection = (ray.origin + tmpdir);
		}
	}
	return true;
}

bool Scene::RayTriangleIntersect(Ray & ray, triangle & triangle, float &t, Point &intersection){
	Point e1, e2, p, s, q;
	Point tmpdir(ray.direction);
	float a, f, u, v;
	//tmpdir.normalise();

	e1 = triangle.v2 - triangle.v1;
	e2 = triangle.v3 - triangle.v1;
	p = ray.direction ^ e2;
	a = e1 * p;

	if (a == 0) {
		return false;
	}

	f = 1.0 / a;

	s = ray.origin - triangle.v1;
	u = (s * p) * f;
	if (u < 0.0 || u > 1.0) {
		return false;
	}

	q = s ^ e1;
	v = (ray.direction * q) * f;
	if (v < 0.0 || u+v > 1.0) {
		return false;
	}

	float t1 = (e2 * q) * f;
	if (t1 > 0) {
		t = t1;
		tmpdir.printPoint();
		tmpdir.Scale(t);
		tmpdir.printPoint();
		intersection = ray.origin + tmpdir;
		return true;
	}
	return false;
}

Pixel Scene::recursiveRayTrace(Ray &ray, float refrac_index, bool recurse){
	Pixel p;
	Point intersection,minInt;
	float t = 0, minT = 0;
	int type, pos;
	for (int i = 0; i < Spheres.size(); ++i) {
		if (RaySphereIntersect(ray, Spheres[i], t, intersection)) {
			if (minT == 0 || minT > t) {
				minT = t;
				type = 0;					// type of object 0 for sphere 1 for triangle
				pos = i;
				minInt = intersection;
			}
		}
	}
	for (int i = 0; i < Triangles.size(); ++i) {
		if (RayTriangleIntersect(ray, Triangles[i], t, intersection)) {
			if (minT == 0 || minT > t) {
				minT = t;
				type = 1;					// type of object 0 for sphere 1 for triangle
				pos = i;
				minInt = intersection;
			}
		}
	}
	if (minT > 0 && recurse) {
		float intense = 0.0;
		Point normal;
		if(type == 0){
			intense += Spheres[pos].ka*ambient_light;
			normal = minInt - Spheres[pos].center;
			normal.normalise();
			if(ray.direction * normal > 0)
				normal.Scale(-1);
		}
		else{
			intense += Triangles[pos].ka*ambient_light;
			Point e1;
			e1 = Triangles[pos].v1 - Triangles[pos].v2;
			e1.normalise();
			normal = Triangles[pos].v3 - Triangles[pos].v2;
			normal.normalise();
			normal = normal ^ e1;
			if (ray.direction * normal > 0) {
				normal.Scale(-1);
			}
			normal.normalise();
		}
		for (int i = 0; i < light_sources.size(); ++i){
			Point tmpdir;
			tmpdir = light_sources[i].location - minInt;
			tmpdir.normalise();
			Ray tolighsources(minInt,tmpdir);
			Pixel pp;
			pp = recursiveRayTrace(tolighsources,1.0,false);
			if(pp.r != 1.0 && pp.g != 1.0 && pp.b != 1.0){
				Point H;
				H = tmpdir - ray.direction;
				H.normalise();   // if no obstacle between light source and intersection point
				if(type == 0){
				intense += Spheres[pos].kd * light_sources[i].intensity * (tmpdir*normal);
					intense += Spheres[pos].ks * light_sources[i].intensity * pow((H*normal),Spheres[pos].n);
				}
				else{
					intense += Triangles[pos].kd * light_sources[i].intensity * (tmpdir*normal);
					intense += Spheres[pos].ks * light_sources[i].intensity * pow((H*normal),Triangles[pos].n);
				}
			}
		}
		if(type==0){
			p = Spheres[pos].color;
			p.Scale(intense);
		}
		else{
			p = Triangles[pos].color;
			p.Scale(intense);
		}
		Point tmpdir;
		tmpdir = ray.direction;
		tmpdir.Scale(-1);

		Point R = normal;
		R.Scale(2*(tmpdir * normal));
		R = R - tmpdir;
		R.normalise();
		Ray nRay(minInt,R);
		//Pixel Precref = recursiveRayTrace(nRay, 1.0f, true);
		if(type==0){
			p = Spheres[pos].color;
			//Precref.Scale(Spheres[pos].krg);
		}
		else{
			p = Triangles[pos].color;
			//Precref.Scale(Triangles[pos].krg);
		}
		p.Scale(intense);
		//p = p + Precref;
	}
	else if (!recurse && minT > 0) {
		p.colorPixel(1.0, 1.0, 1.0);
	}
	return p;
}

void Scene::writeImage() {
	//VCStoWCS.print();
	Point eyeinWCS;
	eyeinWCS = VCStoWCS.transform(camera.origin) + VCSOrigin;
	//eyeinWCS.printPoint();
	Point x = display.bottom_left_corner;
	Point direction;
	//std::cout << floor(display.dimX)*factor1 << " " << floor(display.dimY)*factor2;
	for (int i = 0; i < floor(display.dimX)*factor1; i++) {
		for (int j = 0; j < floor(display.dimY)*factor2; j++) {
			direction = x - camera.origin;
			direction = VCStoWCS.transform(direction);
			//direction.printPoint();
			direction.normalise();
			Ray R(eyeinWCS, direction);
			//display.grid[i][j] = recursiveRayTrace(R, 1.0, true);
			x = x + Point(0.0, 1.0/factor2, 0.0);
		}
		x = x + Point(1.0/factor1, 0.0, 0.0);
	}
}

void Scene::printImage() {
	display.bitmap(display.dimX*factor1, display.dimY*factor2, display.grid);
}
