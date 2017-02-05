#include "Scene.h"
#include "Image.h"

int main() {		
	
	string infile = "sample_input.txt";
	Scene scene(infile);
	scene.printScene();

	int done;
	cin >> done;
	while (done != 0);
	return 0;
}