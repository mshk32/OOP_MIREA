#include <iostream>
#include <cmath>

using namespace std;

//Не очень понял должна ли матрица обязательно состоять из 4 различных цифр (как написано в условии задания)
// или из массива чисел 2х2. Поэтому представлены 2 варианта 

class Matrix_2x2 {
private:
    float matrix[2][2];

public:
    Matrix_2x2() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    Matrix_2x2(float A, float B, float C, float D) {
        matrix[0][0] = A;
        matrix[0][1] = B;
        matrix[1][0] = C;
        matrix[1][1] = D;
    }

    Matrix_2x2(const Matrix_2x2& M) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                matrix[i][j] = M.matrix[i][j];
            }
        }
    }

    Matrix_2x2 operator* (float n) {
        Matrix_2x2 res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                res.matrix[i][j] = matrix[i][j] * n;
            }
        }
        return res;
    }

    Matrix_2x2 operator* (Matrix_2x2 M) {
        Matrix_2x2 res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                res.matrix[i][j] = matrix[i][0] * M.matrix[0][j] + matrix[i][1] * M.matrix[1][j];
            }
        }
        return res;
    }

    void print() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    friend Matrix_2x2 operator* (float n, const Matrix_2x2& M);
};


Matrix_2x2 operator* (float n, const Matrix_2x2& M) {
    Matrix_2x2 res;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            res.matrix[i][j] = n * M.matrix[i][j];
        }
    }
    return res;
}


int main() {

    Matrix_2x2 mat(1, 2, 3, 4);
    cout << "Matrix mat:" << endl;
    mat.print();

    Matrix_2x2 result1 = mat * 2.0f;
    cout << "Matrix mat * 2.0:" << endl;
    result1.print();

    Matrix_2x2 result2 = 2.0f * mat;
    cout << "Matrix 2.0 * mat:" << endl;
    result2.print();
    
    

    return 0;
}