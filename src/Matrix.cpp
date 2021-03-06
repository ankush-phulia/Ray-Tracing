#include "Matrix.h"

Matrix::Matrix(void) {  // identity matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                M[i][j] = 1.0f;
            } else {
                M[i][j] = 0.0f;
            }
        }
    }
}

Matrix::Matrix(double m[][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            M[i][j] = m[i][j];
        }
    }
}

Point Matrix::transform(Point &P) {
    Point P1;
    P1.x = P.x * M[0][0] + P.y * M[0][1] + P.z * M[0][2] + P.w * M[0][3];
    P1.y = P.x * M[1][0] + P.y * M[1][1] + P.z * M[1][2] + P.w * M[1][3];
    P1.z = P.x * M[2][0] + P.y * M[2][1] + P.z * M[2][2] + P.w * M[2][3];
    P1.w = P.x * M[3][0] + P.y * M[3][1] + P.z * M[3][2] + P.w * M[3][3];
    P1.x /= P1.w;
    P1.y /= P1.w;
    P1.z /= P1.w;
    P1.w /= P1.w;
    return P1;
}

Matrix::Matrix(double a1, double a2, double a3, double a4, double a5, double a6,
               double a7, double a8, double a9) {
    M[0][0] = a1;
    M[0][1] = a2;
    M[0][2] = a3;
    M[1][0] = a4;
    M[1][1] = a5;
    M[1][2] = a6;
    M[2][0] = a7;
    M[2][1] = a8;
    M[1][2] = a9;
}

void Matrix::Scale(double factor) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            M[i][j] *= factor;
        }
    }
}

bool Matrix::operator==(const Matrix &m2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (M[i][j] != m2.M[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::operator*(const Matrix &m2) {
    Matrix Mat(M);
    double s;
    for (int i = 0; i < 4; i++) {
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

Matrix Matrix::operator+(const Matrix &m2) {
    Matrix Mat(M);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Mat.M[i][j] += m2.M[i][j];
        }
    }
    return Mat;
}

Matrix Matrix::operator-(const Matrix &m2) {
    Matrix Mat(M);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Mat.M[i][j] -= m2.M[i][j];
        }
    }
    return Mat;
}

Matrix Matrix::transpose() {
    Matrix m = Matrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m.M[i][j] = M[j][i];
        }
        return m;
    }
}

Matrix Matrix::inverse() {
    Matrix m = Matrix();
    m.M[0][0] = M[2][2] * M[1][1] - M[2][1] * M[1][2];
    m.M[0][1] = -(M[2][2] * M[0][1] - M[2][1] * M[0][2]);
    m.M[0][2] = M[1][2] * M[0][1] - M[1][1] * M[0][2];
    m.M[1][0] = -(M[2][2] * M[1][0] - M[2][0] * M[1][2]);
    m.M[1][1] = (M[2][2] * M[0][0] - M[2][0] * M[0][2]);
    m.M[1][2] = -(M[1][2] * M[0][0] - M[1][0] * M[0][2]);
    m.M[2][0] = (M[2][1] * M[1][0] - M[2][0] * M[1][1]);
    m.M[2][1] = -(M[2][1] * M[0][0] - M[2][0] * M[0][1]);
    m.M[2][2] = (M[1][1] * M[0][0] - M[1][0] * M[0][1]);
    return m;
}

void Matrix::print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
