#include "Window.h"

Window::Window(int height, int width) :height(height), width(width), data(new _int8[width * height * 4]) {}

Window::~Window() { delete[] data; }

int Window::getHeight() { return height; }

int Window::getWidth() { return width; }

_int8* Window::operator[](int index) { return &data[width * index]; }


