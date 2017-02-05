#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

class Matrix {

public:
	float M[4][4];

	Matrix(void);
	Matrix(float m[4][]);
	float Det();
	void Scale(float factor);
  bool operator==(const Matrix &);
  Matrix operator*(const Matrix &);
	Matrix operator+(const Matrix &);
	Matrix operator-(const Matrix &);
};


#endif
