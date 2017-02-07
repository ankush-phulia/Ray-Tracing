#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "Point.h"

class Matrix {

public:
	double M[4][4];

	Matrix(void);
	Matrix(double m[][4]);
	void Scale(double factor);
	bool operator==(const Matrix &);
	Matrix operator*(const Matrix &);
	Matrix operator+(const Matrix &);
	Matrix operator-(const Matrix &);
	Point transform(Point &);
	void print();

};


#endif
