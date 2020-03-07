#pragma once
#include "../PDCurses/curses.h"
#include <string>

class Block
{	
protected:
	int size;
	std::string label;
	int x;
	int y;
public:
	Block(int size, std::string label, int x, int y);
	virtual void print(WINDOW *win, int color=100, int shift_x=0, int shift_y=0) = 0;
	virtual void change_label(std::string label);
	virtual std::string get_as_string() = 0;
	void setX(int val);
	void moveX(int val);
	void setY(int val);
	void moveY(int val);
	int getX();
	int getY();
};

