// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#ifndef CODE_FUNCTIONS_HPP
#define CODE_FUNCTIONS_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define SIZE 4

bool isMatrixHasReversed(double **, size_t);

bool gaussJordan(double **, double **, size_t);

void generateRandom(double **, size_t);

void printMatrix(double **, size_t);

void multiplyMatrixes(double **, double **, double **, size_t);

#endif //CODE_FUNCTIONS_HPP
