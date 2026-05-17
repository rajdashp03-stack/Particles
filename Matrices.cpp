#include "Matrices.h"

namespace Matrices {

	Matrix::Matrix(int _rows, int _cols) {

        rows = _rows;
        cols = _cols;

        a.resize(rows);
        for (size_t i = 0; i < a.size(); ++i) {

            a.at(i).resize(cols);
        }

        for (size_t i = 0; i < a.size(); ++i) {

            for (size_t j = 0; j < a.at(i).size(); ++j) {

                a.at(i).at(j) = 0;
            }
        }

	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {

        a.at(0).at(0) = cos(theta);
        a.at(0).at(1) = -(sin(theta));
        a.at(1).at(0) = sin(theta);
        a.at(1).at(1) = cos(theta);

	}

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {

        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;

    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {

        for (size_t i = 0; i < nCols; ++i) {

            a.at(0).at(i) = xShift;
            a.at(1).at(i) = yShift;
        }

    }

    Matrix operator+(const Matrix& a, const Matrix& b) {

        //No error checking
        Matrix c(a.getRows(), a.getCols());

        for (size_t i = 0; i < a.getRows(); ++i) {

            for (size_t j = 0; j < a.getCols(); ++j) {

                c(i, j) = a(i, j) + b(i, j);
            }
        }

        return c;
    }

    Matrix operator*(const Matrix& a, const Matrix& b) {

        Matrix c(a.getRows(), a.getCols());

        for (size_t i = 0; i < a.getRows(); ++i) {

            for (size_t j = 0; j < a.getCols(); ++j) {

                c(i, j) = a(i, j) * b(i, j);
            }
        }

        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b) {

        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols())) {

            return false;
        }
        else {

            for (size_t i = 0; i < a.getRows(); ++i) {

                for (size_t j = 0; j < a.getCols(); ++j) {

                    if (a(i, j) != b(i, j)) { 
                        
                        return false;
                    }
                }
            }

            return true;
        }

    }

    bool operator!=(const Matrix& a, const Matrix& b) {

        return (!(a == b));
    }

    ostream& operator<<(ostream& os, const Matrix& a) {

        for (size_t i = 0; i < a.getRows(); ++i) {

            for (size_t j = 0; j < a.getCols(); ++j) {

                os << a(i, j) << ' ';
            }
            os << '\n';
        }

        return os;
    }
}