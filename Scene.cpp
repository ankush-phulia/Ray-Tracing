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

void Scene::printScene(){
	cout << light_sources.size() << endl;
	//cout << objects.size() << endl;
}
