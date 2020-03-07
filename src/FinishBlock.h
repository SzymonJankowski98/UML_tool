#pragma once
#include "ActionBlock.h"
#include "../PDCurses/curses.h"
class FinishBlock :
	public ActionBlock
{
public:
	FinishBlock(int size, int x, int y) :ActionBlock(size, "FINISH", x, y) {}
	void change_label(std::string label);
	std::string get_as_string();
};

