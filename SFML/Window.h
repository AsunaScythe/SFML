#pragma once
class Window
{
public:
	Window(int height, int width);

	~Window();

	int getHeight();

	int getWidth();

	_int8* operator [](int index);


private:
	int width,
		height;
	__int8* data;
};

