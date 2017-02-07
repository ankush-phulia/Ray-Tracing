compile :
	g++ Matrix.cpp Image.cpp Ray.cpp Point.cpp Scene.cpp main.cpp -o main

run :
	./main ${input}

clear :
	rm main out.bmp
