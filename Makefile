compile : 
	g++ Matrix.cpp Image.cpp Ray.cpp Point.cpp Scene.cpp main.cpp -o main

clear : 
	rm main out.bmp
