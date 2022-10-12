#pragma once
#include "Matrix.h"
class Camera
{
public:
	Camera():position({ {0,0,0} }), angle({ {0,0,0} }) {}

	Camera& SetPosition(double x, double y, double z);

	Camera& SetAngle(double x, double y, double z);
	
	template<typename T>
	Matrix<T> Render();

private:
	Matrix<double> position;
	Matrix<double> angle;
};

