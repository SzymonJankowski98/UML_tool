#pragma once

#include "BaseTool.h"
#include "tinyxml2.h"
#include "UML_Diagram.h"
#include <unordered_map>
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <string>

#include "StartBlock.h"
#include "FinishBlock.h"
#include "DecisionBlock.h"
#include "ActionBlock.h"


class UMLTool final :
	public BaseTool
{
	std::unordered_map<std::string, std::string> entries;
	WINDOW *window;

private:
	UML_Diagram* current_file;
	std::string file_name;
	int move_mode;
	int edit_mode;
	std::vector<int> temp_connections;
	int temp_connection_counter;
public:
	UMLTool();
	~UMLTool() override;

	std::string getEntry(const std::string&) const override;
	void setEntry(const std::string&, const std::string&) override;
	void assignWindow(WINDOW*) override;

	void open();
	void new_diagram();
	void save();
	void save_as();
	void edition();
	void fill();
	void unsave();
	void param();
	void clear();
	void move_node();
	void move_diagram();
	void change_label();
	void add_start_block();
	void add_finish_block();
	void add_action_block();
	void add_decision_block();
	void delete_block();
	void move_window_up();
	void move_window_down();
	void move_window_right();
	void move_window_left();
	void add_connection_mode();
	void delete_connection_mode();
	void increment_temp_connections();
};

