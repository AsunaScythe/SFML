#pragma once

#define _USE_MATH_DEFINES
#include <iostream>

template<typename T>
class Matrix {
public:

	Matrix(int height, int width);

	Matrix(std::initializer_list<std::initializer_list<T>> param);

	Matrix(Matrix<T> const& param);

	Matrix(Matrix<T>&& param);

	int getHeight();

	int getWidth();

	Matrix<T>& operator =(Matrix<T> const& param);

	Matrix<T>& operator = (Matrix<T>&& param);

	T* operator [](int index);

	Matrix<T> operator *(Matrix<T> const& param);

	Matrix<T>& normalize();

	Matrix<T>& merge(Matrix<T> const& param);

	Matrix<T> add(int h, int w) const;

	~Matrix();

	static double det(Matrix<T> const& param);


private:
	int width,
		height;

	T** data;

};

template<typename T>
int Matrix<T>::getHeight() { return height;}

template<typename T>
int Matrix<T>::getWidth() {	return width;}


template<typename T>
Matrix<T>::Matrix(int height, int width) :height(height), width(width) {
	data = new T * [height];
	for (int i = 0; i < height; i++) {
		data[i] = new T[width];
		for (int j = 0; j < width; j++)
			data[i][j] = 0;

	}
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> param) :height(param.size()), width(param.begin()->size()) {
	data = new T * [height];
	int i = 0,
		j = 0;
	for (auto a : param) {
		j = 0;
		data[i] = new T[width];
		for (auto b : a) {
			data[i][j] = b;
			j++;
		}
		i++;
	}
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> const& param) :height(param.height), width(param.width) {
	data = new T * [height];
	for (int i = 0; i < height; i++) {
		data[i] = new T[width];
		for (int j = 0; j < width; j++)
			data[i][j] = param.data[i][j];
	}

}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& param) :height(param.height), width(param.width) {
	data = param.data;
	param.data = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> const& param) {
	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete[] data;
	height = param.height;
	width = param.width;
	data = new T * [height];
	for (int i = 0; i < height; i++) {
		data[i] = new T[width];
		for (int j = 0; j < width; j++)
			data[i][j] = param.data[i][j];
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& param) {
	height = param.height;
	width = param.width;
	data = param.data;
	param.data = nullptr;

	return *this;
}

template<typename T>
T* Matrix<T>::operator[](int index)
{
	return data[index];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const& param)
{
	Matrix answer(this->height, param.width);
	for (int i = 0; i < answer.height; i++)
		for (int j = 0; j < answer.width; j++)
			for (int k = 0; k < param.width; k++)
				answer[i][j] += data[i][k] * param.data[k][j];
	return answer;
}

template<typename T>
Matrix<T>::~Matrix()
{
	if (data != nullptr)
		for (int i = 0; i < height; i++)
			delete[] data[i];
	delete[] data;
}



template<typename T>
Matrix<T>& Matrix<T>::normalize() {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] /= data[i][3];
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::merge(Matrix<T> const& param) {
	T** temp = new T * [height + param.height];
	int n = 0;
	for (int i = 0; i < height; i++, n++)
		T[i] = data[i];
	for (int i = 0; i < param.height; i++, n++)
		T[n] = param.data[i];
	delete[] data;
	data = temp;
	param.data = nullptr;
	return *this;
}

template<typename T>
double Matrix<T>::det(Matrix<T> const& param) {
	if (param.height == 1)
		return param.data[0][0];
	double D = 0;
	for (int i = 0, j = 1; i < param.height; i++, j *= -1) {
		D += j * det(param.add(i, 0)) * param.data[i][0];
	}
	return D;
}

template<typename T>
Matrix<T> Matrix<T>::add(int h, int w) const {
	Matrix<T> answer(height - 1, height - 1);
	for (int i = 0, n = 0; i < height; i++, n++)
		if (i == h) n--;
		else
			for (int j = 0, k = 0; j < width; j++, k++)
				if (j == w) k--;
				else
					answer[n][k] = data[i][j];
	return answer;
}

