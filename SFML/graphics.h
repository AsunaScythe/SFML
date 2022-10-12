#pragma once
#include "Matrix.h"

Matrix<double> rotate_x(double angle);

Matrix<double> rotate_y(double angle);

Matrix<double> rotate_z(double angle);

Matrix<double> move(double x, double y, double z);

Matrix<double> projection(double z);

Matrix<double> identity(int size);
