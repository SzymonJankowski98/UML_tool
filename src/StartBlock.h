#pragma once
#include "ActionBlock.h"
class StartBlock :
	public ActionBlock
{
public:
	StartBlock(int size, int x, int y) :ActionBlock(size, "START", x, y) {}
	void change_label(std::string label);
	std::string get_as_string();
};

