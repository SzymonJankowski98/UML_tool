#include "Window.h"


Window::Window() :
	window(nullptr)
{}


Window::Window(const int width, const int height, const int dx, const int dy)
{
	init(width, height, dx, dy);
}


Window::~Window()
{
	del();
}


void Window::init(const int width, const int height, const int dx, const int dy)
{
	window = newwin(height, width, dy, dx);
}


void Window::del()
{
	wclear(window);
	wrefresh(window);
	delwin(window);
	window = nullptr;
}
