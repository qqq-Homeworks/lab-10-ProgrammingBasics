#include "functions.hpp"

int main() {
    double **matrixOriginal = new double *[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        matrixOriginal[i] = new double[SIZE];
    }

    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            std::cin >> matrixOriginal[i][j];
        }
    }

    double **matrix = new double *[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        matrix[i] = new double[SIZE];
    }

    double **reversedMatrix = new double *[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        reversedMatrix[i] = new double[SIZE];
    }
    double **resultMatrix = new double *[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        resultMatrix[i] = new double[SIZE];
    }

    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            matrix[i][j] = matrixOriginal[i][j];
        }
    }

    printMatrix(matrixOriginal, SIZE);
    if (!gaussJordan(matrix, reversedMatrix, SIZE)) {
        std::cout << "Обратная матрица не существует";
    } else {

        multiplyMatrixes(matrixOriginal, reversedMatrix, resultMatrix, SIZE);
        printMatrix(reversedMatrix, SIZE);
        printMatrix(resultMatrix, SIZE);
    }

    for (size_t i = 0; i < SIZE; ++i) {
        delete[] matrix[i];
        delete[] reversedMatrix[i];
        delete[] matrixOriginal[i];
        delete[] resultMatrix[i];
    }
    delete[] matrix;
    delete[] reversedMatrix;
    delete[] matrixOriginal;
    delete[] resultMatrix;

    return 0;
}
