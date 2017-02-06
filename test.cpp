#include "Scene.h"
#include "Image.h"
using namespace std;
int main() {

	/*Point p0(0, 0, 0);
	Point p1(1, 0, 0);
	Point p2(0, 1, 0);
	Point p3(0, 0, 1);
	Point p4(1, 1, 0);
	Point p5(1, 0, 1);
	Point p6(0, 1, 1);
	Point p7(1, 1, 1);

	p1 = p1 + p2;
	p1.printPoint();
	cout << p3*p4 << endl;

	Ray r1(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	Ray r2(1,1,1, 0,0,-1);
	r1.printRay();
	r2.printRay();

	Scene s;
	float a, b, c, x0, x1;
	a = 1; b = 2; c = 1; x0 = 0; x1 = 0;
	cout << s.existRoot(a, b, c, x0, x1) << " ";
	cout <<"Roots " << x0 <<" "<< x1 << endl;

	sphere sph(2, 2, 2, 1);
	Point int1,int2;
	float t = 0;
	cout << s.RaySphereIntersect(r1, sph, t, int1) << " ";
	int1.printPoint();

	triangle tri(0,0,0, 2,0,0, 0,2,0);
	cout << s.RayTriangleIntersect(r2, tri, t, int2) << " ";
	int2.printPoint();

	Image i = s.display;
	i.bg.colorPixel(255, 255, 255);
	i.setBackground();
	i.bitmap(20 * 20, 20 * 20, i.grid);*/

	Scene s("sample_input.txt");
	s.writeImage();	
	s.printImage();

	int done;
	cin >> done;
	while (done != 0);
	return 0;
}
