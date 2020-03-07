#pragma once

#include <curses.h>


class Window
{
	WINDOW *window;

public:
	Window();
	Window(const int, const int, const int, const int);
	~Window();

	WINDOW *const& getWindow() const { return window; }
	
	void init(const int, const int, const int, const int);
	void del();
};

