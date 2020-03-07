#pragma once
#include "block.h"
#include <string>
#include <vector>
#include <vector>
#include <algorithm>

class ActionBlock :
	public Block
{
protected:
	std::vector<int> connections;
public:
	ActionBlock(int size, std::string label, int x, int y) :Block(size, label, x, y) {}
	void print(WINDOW* win, int color, int shift_x = 0, int shift_y = 0);
	std::vector<int> get_connections();
	void add_connection(int con);
	void delete_connection(int value);
	void delete_connection_index(int index);
	std::string get_as_string();
};

