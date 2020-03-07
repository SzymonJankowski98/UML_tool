#pragma once

#include "Window.h"
#include "colors.h"


class Terminal final
{
	Window toolWindow, menuWindow;

public:
	Terminal();
	~Terminal();

	void init();
	void resize();
	void initColors();
	void restore();
	void del();

	WINDOW *const& getToolWindow() const { return toolWindow.getWindow(); }
	WINDOW *const& getMenuWindow() const { return menuWindow.getWindow(); }
};

