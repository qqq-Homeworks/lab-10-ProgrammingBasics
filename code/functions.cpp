// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>

#include "functions.hpp"

void printMatrix(double **matrix, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cout << std::setw(12) << std::setprecision(5) << std::fixed << matrix[i][j];
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}


void multiplyMatrixes(double **matrix1, double **matrix2, double **resultMatrix, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            resultMatrix[i][j] = 0;
        }
    }
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            for (size_t k = 0; k < N; ++k) {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            resultMatrix[i][j] = abs(resultMatrix[i][j]);
        }
    }
}

bool isMatrixHasReversed(double **matrix, size_t N) {
    bool result = true;
    for (size_t i = 0; i < N; ++i) {
        if (matrix[i][i] == 0) {
            result = false;
            for (size_t j = i; j < N; ++j) {
                if (matrix[j][i] != 0) {
                    for (size_t k = 0; k < N; ++k) {
                        std::swap(matrix[j][k], matrix[i][k]);
                    }
                    result = true;
                    continue;
                }
            }
            if (!result) {
                return result;
            }
        }
    }

    return true;
    // по-хорошему ещё бы проверять, есть ли подходящая строка выше. Но в методе требуют проверять лишь те,
    // что под строкой с нулём на главной диагонали. Проверка тех строк что выше - черевата, потому что нужно
    // проверять ещё и то, чтобы они не заменились на строки с нулём в главной диагонали.
}

void generateRandom(double **matrix, size_t N) {
    srand(time(nullptr));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }
}

bool gaussJordan(double **matrix, double **reversed, size_t N) {
    if (!isMatrixHasReversed(matrix, N)) {
        return false;
    } else {
        double **unoMatrix = new double *[N];
        for (size_t i = 0; i < N; ++i) {
            unoMatrix[i] = new double[N];
        }
        //Единичная матрица (искомая обратная матрица)
        for (int i = 0; i < N; i++)
            for (size_t j = 0; j < N; ++j) {
                if (i == j) {
                    unoMatrix[i][j] = 1;
                } else {
                    unoMatrix[i][j] = 0;
                }
            }

        double **bigMatrix = new double *[N];
        for (size_t i = 0; i < N; ++i) {
            bigMatrix[i] = new double[N * 2];
        }
        //Общая матрица, получаемая скреплением Начальной матрицы и единичной
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                bigMatrix[i][j] = matrix[i][j];
                bigMatrix[i][j + N] = unoMatrix[i][j];
            }
        }
        for (size_t k = 0; k < N; k++) //k-номер строки
        {
            for (size_t i = 0; i < 2 * N; i++) //i-номер столбца
                bigMatrix[k][i] = bigMatrix[k][i] /
                                  matrix[k][k]; //Деление k-строки на первый член !=0 для преобразования его в единицу
            for (size_t i = k + 1; i < N; i++) //i-номер следующей строки после k
            {
                double q = bigMatrix[i][k] / bigMatrix[k][k]; //Коэффициент
                for (size_t j = 0; j < 2 * N; j++) //j-номер столбца следующей строки после k
                    bigMatrix[i][j] = bigMatrix[i][j] - bigMatrix[k][j] *
                                                        q; //Зануление элементов матрицы ниже первого члена, преобразованного в единицу
            }
            for (size_t i = 0; i < N; i++) //Обновление, внесение изменений в начальную матрицу
                for (size_t j = 0; j < N; j++)
                    matrix[i][j] = bigMatrix[i][j];
        }
        for (int k = N - 1; k > -1; k--) //k-номер строки
        {
            for (int i = 2 * N - 1; i > -1; i--) //i-номер столбца
                bigMatrix[k][i] = bigMatrix[k][i] / matrix[k][k];
            for (int i = k - 1; i > -1; i--) //i-номер следующей строки после k
            {
                double q = bigMatrix[i][k] / bigMatrix[k][k];
                for (int j = 2 * N - 1; j > -1; j--) //j-номер столбца следующей строки после k
                    bigMatrix[i][j] = bigMatrix[i][j] - bigMatrix[k][j] * q;
            }
        }
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                reversed[i][j] = bigMatrix[i][j + N];


        for (size_t i = 0; i < N; ++i) {
            delete[] bigMatrix[i];
            delete[] unoMatrix[i];
        }


        delete[] bigMatrix;
        delete[] unoMatrix;

        return true;
    }
}
