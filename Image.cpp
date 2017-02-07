#include "Image.h"
#include <stdio.h>
#include <stdlib.h>

Image::Image(){
	center.set(0, 0, 0);
	top_left_corner.set(-10, 10, 0);
	dimX = 20;
	dimY = 20;
	bg = Pixel();
	grid = new Pixel*[(int)floor(dimX)*factor1];
	for (int i = 0; i<floor(dimX)*factor1; i++) {
		grid[i] = new Pixel[(int)floor(dimY)*factor2];
	}
}

Image::~Image(){
	for (int i = 0; i<floor(dimX)*factor1; i++) {
		delete[] grid[i];
	}
	delete[] grid ;
}


Image::Image(double x, double y, double z, double xc, double yc, double zc, double Xdim, double Ydim){
	center.set(xc, yc, zc);
	top_left_corner.set(x, y, z);
	dimX = Xdim;
	dimY = Ydim;
	bg = Pixel();
	grid = new Pixel*[(int)floor(dimX)*factor1];
	for (int i = 0; i<floor(dimX)*factor1; i++) {
		grid[i] = new Pixel[(int)floor(dimY)*factor2];
	}
}

Image::Image(Point &blcorner, Point & cent, double Xdim, double Ydim){
	top_left_corner = blcorner;
	center = cent;
	dimX = Xdim;
	dimY = Ydim;
}

void Image::setBackground(){
	for (int i = 0; i < floor(dimX)*factor1; i++) {
		for (int j = 0; j < floor(dimY)*factor2; j++) {
			grid[i][j] = Pixel(bg);
		}
	}
}

//code courtesy http://stackoverflow.com/questions/30423590/generate-bmp-file-from-array-of-rgb-values and bitmap documentation

void Image::bitmap(int width, int height, Pixel** grid) {

	typedef struct {                       /**** BMP file header structure ****/
		unsigned int   bfSize;           /* Size of file */
		unsigned short bfReserved1;      /* Reserved */
		unsigned short bfReserved2;      /* ... */
		unsigned int   bfOffBits;        /* Offset to bitmap data */
	} BITMAPFILEHEADER;

	typedef struct {                      /**** BMP file info structure ****/
		unsigned int   biSize;           /* Size of info header */
		int            biWidth;          /* Width of image */
		int            biHeight;         /* Height of image */
		unsigned short biPlanes;         /* Number of color planes */
		unsigned short biBitCount;       /* Number of bits per pixel */
		unsigned int   biCompression;    /* Type of compression to use */
		unsigned int   biSizeImage;      /* Size of image data */
		int            biXPelsPerMeter;  /* X pixels per meter */
		int            biYPelsPerMeter;  /* Y pixels per meter */
		unsigned int   biClrUsed;        /* Number of colors used */
		unsigned int   biClrImportant;   /* Number of important colors */
	} BITMAPINFOHEADER;

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	/* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
	unsigned short bfType = 0x4d42;
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize = 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + height * width * 3;
	bfh.bfOffBits = 0x36;

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 5000;
	bih.biYPelsPerMeter = 5000;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	FILE *file = fopen("out.bmp", "wb");
	if (!file) {
		std::cout << "Could not write file\n";
		return;
	}

	/*Write headers*/
	fwrite(&bfType, 1, sizeof(bfType), file);
	fwrite(&bfh, 1, sizeof(bfh), file);
	fwrite(&bih, 1, sizeof(bih), file);

	/*Write bitmap*/
	for (int y = bih.biHeight - 1; y >= 0; y--) { /*Scanline loop backwards*/
		for (int x = 0; x < bih.biWidth; x++) { /*Column loop forwards*/
												/*compute some pixel values*/
			//Pixel p = grid[x][y];
			float rr = 0, gg = 0, bb = 0;
			for (int j = 0; j < factor3; j++) {
				for (int i = 0; i < factor3; i++) {
					Pixel p = grid[factor3*x + i][factor3*y + j];
					rr += p.r; gg += p.g; bb += p.b;
				}
			}
			unsigned char r = (char)rr/(factor3*factor3);/*255 * ((double)x / bih.biWidth);*/
			unsigned char g = (char)gg/(factor3*factor3);/*255 * ((double)y / bih.biHeight);*/
			unsigned char b = (char)bb/(factor3*factor3);
			fwrite(&b, 1, 1, file);
			fwrite(&g, 1, 1, file);
			fwrite(&r, 1, 1, file);
		}
	}
	fclose(file);
}
