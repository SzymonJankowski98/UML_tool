#pragma once
#include "block.h"
#include "../PDCurses/curses.h"
#include <string>

class DecisionBlock :
	public Block
{
private:
	int true_connection;
	int false_connection;
public:
	DecisionBlock(int size, std::string label, int x, int y) :Block(size, label, x, y), true_connection(-1), false_connection(-1) {}
	int get_true();
	int get_false();
	void set_true(int con);
	void set_false(int con);
	void print(WINDOW* win, int color, int shift_x = 0, int shift_y = 0);
	std::string get_as_string();
};
