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
  bool operator==(const Matrix &);
  Matrix operator*(const Matrix &);
	Matrix operator+(const Matrix &);
	Matrix operator-(const Matrix &);
  Point transform(Point &);
};


#endif
