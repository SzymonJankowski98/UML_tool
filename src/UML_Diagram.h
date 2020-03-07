#pragma once
#include "block.h"
#include "tinyxml2.h"
#include <iostream>
#include "ActionBlock.h"
#include "FinishBlock.h"
#include "StartBlock.h"
#include "DecisionBlock.h"
#include "Block.h"
#include <typeinfo>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

class UML_Diagram
{
private:
	std::vector<Block*> diagram;
	int size;
	int picked_node;
	int connection_to_add;
	int connection_to_delete;
	int shift_x;
	int shift_y;
	void init_colors();
	void print_connection(WINDOW* win, int x1, int y1, int x2, int y2);
	void print_false_connection(WINDOW* win, int x1, int y1, int x2, int y2);
	void repair_diagram();
public:
	UML_Diagram(tinyxml2::XMLDocument* xmlDoc, int size);
	UML_Diagram(int size);
	std::vector<int> possible_connections();
	std::vector<int> connections_to_delete();
	std::string generate_string();
	void print_diagram(WINDOW* win);
	bool add_start_block();
	bool add_finish_block();
	void add_action_block();
	void add_decision_block();
	void delete_element();
	void next_node();
	void move_picked_node_X(int val);
	void move_picked_node_Y(int val);
	void change_label(std::string label);
	void move_window_up();
	void move_window_down();
	void move_window_right();
	void move_window_left();
	void set_connection_to_add(int value);
	void set_connection_to_delete(int value);
	void add_connection();
	bool add_false_connection();
	void delete_connection();
};

