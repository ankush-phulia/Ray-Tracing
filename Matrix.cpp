#include "Matrix.h"

Matrix::Matrix(void){                //identity matrix
  for(int i; i<4; i++)
    for(int j; j<4; j++)
      if(i==j)
        M[i][j] = 1.0f;
      else
        M[i][j] = 0.0f;
}

Matrix::Matrix(float m[4][]){
  for(int i; i<4; i++)
    for(int j; j<4; j++)
      M[i][j] = m[i][j];
}

float Matrix::Det()
{

}

void Matrix::Scale(float factor)
{ for(int i; i<4; i++)
    for(int j; j<4; j++)
      M[i][j] *= factor;

}

bool Matrix::operator==(const Matrix & m2)
{ for(int i; i<4; i++)
    for(int j; j<4; j++)
      if(M[i][j] != m2[i][j])
        return false;
  return true
}

Matrix Matrix::operator*(const Matrix &m2)
{

}

Matrix Matrix::operator+(const Matrix &m2){
  Matrix Mat(M);
  for(int i; i<4; i++)
    for(int j; j<4; j++)
      Mat.M[i][j] += m2[i][j];
}

Matrix Matrix::operator-(const Matrix &m2){
  Matrix Mat(M);
  for(int i; i<4; i++)
    for(int j; j<4; j++)
      Mat.M[i][j] -= m2[i][j];
}
