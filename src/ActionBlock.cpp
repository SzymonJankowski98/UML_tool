#include "ActionBlock.h"

void ActionBlock::print(WINDOW* win, int color=100, int shift_x, int shift_y)
{
	WINDOW* w = derwin(win, this->size, this->size * 2, this->x + shift_x, this->y + shift_y);
	wbkgd(w, COLOR_PAIR(color));
	box(w, 0, 0);
	mvwprintw(w, 1, 1, this->label.c_str());
}

std::vector<int> ActionBlock::get_connections()
{
	return this->connections;
}

void ActionBlock::add_connection(int con)
{
	this->connections.push_back(con);
}

void ActionBlock::delete_connection_index(int index)
{
	this->connections.erase(this->connections.begin() + index);
}

void ActionBlock::delete_connection(int value)
{
	this->connections.erase(std::remove(this->connections.begin(), this->connections.end(), value), this->connections.end());
}

std::string ActionBlock::get_as_string()
{
	std::string result = "";
	result.append("<element type=\"ActionBlock\">\n");
	result.append("<x>" + std::to_string(this->x) + "</x>\n");
	result.append("<y>" + std::to_string(this->y) + "</y>\n");
	result.append("<label>" + this->label + "</label>\n");
	result.append("<connections>\n");
	for (int i = 0; i < this->connections.size(); i++)
	{
		result.append("<id>" + std::to_string(this->connections[i]) + "</id>\n");
	}
	result.append("</connections>\n");
	result.append("</element>\n");

	return result;
}