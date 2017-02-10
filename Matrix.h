#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "Point.h"

class Matrix {

public:
	double M[4][4];

	Matrix(void);
	Matrix(double m[][4]);
	Matrix(double a1, double a2, double a3, double a4, double a5, double a6,
		double a7, double a8, double a9);
	void Scale(double factor);
	bool operator==(const Matrix &);
	Matrix operator*(const Matrix &);
	Matrix operator+(const Matrix &);
	Matrix operator-(const Matrix &);
	Matrix transpose();
	Matrix inverse();
	Point transform(Point &);
	void print();

};


#endif
