CC = g++
CXXFLAGS = -std=c++11 -O3 -I include/

all : src/*.cpp
	$(CC) src/*.cpp $(CXXFLAGS) -o fpm

run :
	./main ${input}

clean : 
	rm main out.bmp