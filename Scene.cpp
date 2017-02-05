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
				display.bottom_left_corner.set(-dimX/2,-dimY/2,0.0f);
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

void Scene::printScene(){
	cout << light_sources.size() << endl;
	Point eyeinWCS = VCStoWCS.transform(camera.origin) + VCSOrigin;
	Point x = display.bottom_left_corner;
	Point direction;
	for(int i; i<floor(display.dimX); i++)
	{   for(int j; j<floor(display.dimY); j++)
			{	direction = x - camera.origin;
				direction = VCStoWCS.transform(direction);
				Ray R = Ray(eyeinWCS,direction);
				Pixel p = recursiveRayTrace(R);
				display.grid[i][j] = p;
				x = x + Point(0.0,1.0,0.0);
			}
			x = x + Point(1.0,0.0,0.0);
	}
	//cout << objects.size() << endl;
}
