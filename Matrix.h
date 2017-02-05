#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "Point.h"

class Matrix {

public:
	float M[4][4];

	Matrix(void);
	Matrix(float m[4][]);
	void Scale(float factor);
	bool isEqual(const Matrix &);
	Matrix Mult(const Matrix &);
	Matrix Add(const Matrix &);
	Matrix Sub(const Matrix &);
  Point transform(Point &);
};


#endif
