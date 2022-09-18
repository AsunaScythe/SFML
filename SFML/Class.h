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

	int getH();

	int getW();

	Matrix<T>& operator =(Matrix<T> const& param);

	Matrix<T>& operator = (Matrix<T>&& param);

	T* operator [](int index);

	Matrix<T> operator *(Matrix<T> const& param);

	~Matrix();

	Matrix<T>& normalize();

	static Matrix<T> identity(int size);

	static Matrix<T> transform(double x, double y, double z);

	static Matrix<T> rotate(double x, double y, double z);

	static Matrix<T> projection(double z);


private:
	int width,
		height;

	T** data;

};

template<typename T>
int Matrix<T>::getH() {
	return height;
}

template<typename T>
int Matrix<T>::getW() {
	return width;
}


template<typename T>
Matrix<T>::Matrix(int height, int width) :height(height), width(width) {
	data = new T * [height];
	for (int i = 0; i < height;i++) {
		data[i] = new T[width];
		for (int j = 0; j < width; j++)
			data[i][j] = 0;

	}
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> param):height(param.size()),width(param.begin()->size()) {
	data = new T * [height];
	int i = 0,
		j = 0;
	for (auto a : param){
		j = 0;
		data[i] = new T[width];
		for (auto b : a) {
			data[i][j] =  b;
			j++;
		}
		i++;
	}
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> const& param):height(param.height),width(param.width) {
	data = new T * [height];
	for (int i = 0; i < height; i++) {
		data[i] = new T[width];
		for (int j = 0; j < width; j++)
			data[i][j] = param.data[i][j];
	}

}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && param) :height(param.height), width(param.width) {
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
	if(data != nullptr)
		for (int i = 0; i < height; i++)
			delete[] data[i];
	delete[] data;
}

template<typename T>
Matrix<T> Matrix<T>::identity(int size) {
	Matrix answer(size, size);
	for (int i = 0; i < size; i++)
		answer[i][i] = 1;
	return answer;
}

template<typename T>
Matrix<T> Matrix<T>::transform(double x, double y, double z) {
	x *= M_PI / 180;
	y *= M_PI / 180;
	z *= M_PI / 180;
	
	Matrix<T>	
		x_rotate = { {1      ,0      ,0      ,0      },
					 {0      ,cos(x) ,sin(x) ,0      },
					 {0      ,-sin(x),cos(x) ,0      },
					 {0      ,0      ,0      ,1      } },

		y_rotate = { {cos(y) ,0      ,-sin(y),0      },
					 {0      ,1      ,0      ,0      },
					 {sin(y) ,0      ,cos(y) ,0      },
					 {0      ,0      ,0      ,1      } },

		z_rotate = { {cos(z) ,sin(z) ,0      ,0      },
					 {-sin(z),cos(z) ,0      ,0      },
					 {0      ,0      ,1      ,0      },
					 {0      ,0      ,0      ,1      } };

		return x_rotate * y_rotate * z_rotate;

}

template<typename T>
Matrix<T> Matrix<T>::rotate(double x, double y, double z) {
	return Matrix<T>({ {1      ,0      ,0      ,0      },
					   {0      ,1      ,0      ,0      },
					   {0      ,0      ,1      ,0      },
					   {x      ,y      ,z      ,1      } });
}


template<typename T>
Matrix<T> Matrix<T>::projection(double z) {
	return Matrix<T>({{1      ,0      ,0      ,0      },
					  {0      ,1      ,0      ,0      },
					  {0      ,0      ,0      ,-1./z  },
					  {0      ,0      ,0      ,1      }});
}


template<typename T>
Matrix<T>& Matrix<T>::normalize() {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] /= data[i][3];
	return *this;
}