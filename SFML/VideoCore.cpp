#include "VideoCore.h"

Camera& Camera::SetPosition(double x, double y, double z) {
	position[0][0] = x;
	position[0][1] = y;
	position[0][2] = z;
	return *this;
}

Camera& Camera::SetAngle(double x, double y, double z) {
	angle[0][0] = x;
	angle[0][1] = y;
	angle[0][2] = z;
	return *this;
}

template<typename T>
Matrix<T> Camera::Render() {

	//return (Matrix<double>::rotate(-Coords[0], -Coords[1], -Coords[2]) * Matrix<double>::transform(0, 0, -Angle[2]) * Matrix<double>::rotate(0, 0, -1000) * Matrix<double>::transform(Angle[0], 0, 0) * Matrix<double>::rotate(0, 0, 1000) * Matrix<double>::projection(1000)).normalize();
}