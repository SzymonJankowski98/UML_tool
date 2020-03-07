#pragma once

#include "Key.h"

#include <curses.h>


class MouseKey final :
	public Key
{
	const int x, y;

public:
	MouseKey(const MEVENT&);
	~MouseKey() override;

	int getX() const;
	int getY() const;
};

