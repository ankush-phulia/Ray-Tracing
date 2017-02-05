#include "Scene.h"

Scene::Scene(){
}

Scene::Scene(string s){
	ifstream f_in;
	f_in.open(s);
	while (f_in.is_open()) {
		string buffer;
		int a, b, c, d, n;
		while (f_in >> buffer) {
			if (buffer == "Camera:") {
				f_in >> a >> b >> c;
				Camera.setOrigin(a, b, c);
				f_in >> a >> b >> c;
				Camera.setDirection(a, b, c);
			}
			else if (buffer == "Light-sources:") {
				f_in >> n;
				light_sources.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d;
					light_sources[i] = (light_source(a, b, c, d));
				}
			}
			else if (buffer == "Spheres:") {
				f_in >> n;
				objects.resize(n);
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d;
					objects[i] = (object(0, a, b, c, d));
				}
			}
			else if (buffer == "Triangles:") {
				f_in >> n;
				for (int i = 0; i < n; i++) {
					f_in >> a >> b >> c >> d;
					objects.push_back(object(1, a, b, c, d));
				}
			}
		}
		f_in.close();
	}
}

void Scene::printScene(){
	cout << light_sources.size() << endl;
	cout << objects.size() << endl;
}
