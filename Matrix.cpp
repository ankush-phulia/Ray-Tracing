#include "Matrix.h"

Matrix::Matrix(void){                //identity matrix
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				M[i][j] = 1.0f;
			}
			else {
				M[i][j] = 0.0f;
			}
		}
	}
}

Matrix::Matrix(float m[][4]){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			M[i][j] = m[i][j];
		}
	}
}

Point Matrix::transform(Point &P){
	Point P1;
	P1.x = P.x*M[0][0] + P.y*M[0][1] + P.z*M[0][2] + P.w*M[0][3];
	P1.y = P.x*M[1][0] + P.y*M[1][1] + P.z*M[1][2] + P.w*M[1][3];
	P1.z = P.x*M[2][0] + P.y*M[2][1] + P.z*M[2][2] + P.w*M[2][3];
	P1.w = P.x*M[3][0] + P.y*M[3][1] + P.z*M[3][2] + P.w*M[3][3];
	P1.x /= P1.w;
	P1.y /= P1.w;
	P1.z /= P1.w;
	P1.w /= P1.w;
	return P1;
}

void Matrix::Scale(float factor){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			M[i][j] *= factor;
		}
	}
}

bool Matrix::operator==(const Matrix &m2){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (M[i][j] != m2.M[i][j]) {
				return false;
			}
		}
	}
	return true;
}

Matrix Matrix::operator*(const Matrix &m2){
	Matrix Mat(M);
	float s;
	for(int i = 0; i<4; i++){
		for (int j = 0; j < 4; j++) {
			s = 0.0f;
			for (int k = 0; k < 4; k++) {
				s += M[i][k] * m2.M[k][j];
			}
			Mat.M[i][j] = s;
		}
	}
	return Mat;
}

Matrix Matrix::operator+(const Matrix &m2){
	Matrix Mat(M);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mat.M[i][j] += m2.M[i][j];
		}
	}
	return Mat;
}

Matrix Matrix::operator-(const Matrix &m2){
  Matrix Mat(M);
  for (int i = 0; i < 4; i++) {
	  for (int j = 0; j < 4; j++) {
		  Mat.M[i][j] -= m2.M[i][j];
	  }
  }
  return Mat;
}
