#include "DecisionBlock.h"

void DecisionBlock::print(WINDOW* win, int color=100, int shift_x, int shift_y)
{
	WINDOW* w = derwin(win, this->size, this->size * 2, this->x + shift_x, this->y + shift_y);
	wbkgd(w, COLOR_PAIR(color));

	mvwprintw(w, size / 2, 2, this->label.c_str());

	for (int i = 0; i < size / 2 + 1; i++)
	{
		mvwprintw(w, i, size - i * 2 - 1, "o");
		mvwprintw(w, i, size + i * 2, "o");
		mvwprintw(w, size - i - 1, size - i * 2 - 1, "o");
		mvwprintw(w, size - i - 1, size + i * 2, "o");
	}
}

int DecisionBlock::get_true()
{
	return this->true_connection;
}

int DecisionBlock::get_false()
{
	return this->false_connection;
}

void DecisionBlock::set_true(int con)
{
	this->true_connection = con;
}

void DecisionBlock::set_false(int con)
{
	this->false_connection = con;
}

std::string DecisionBlock::get_as_string()
{
	std::string result = "";
	result.append("<element type=\"DecisionBlock\">\n");
	result.append("<x>" + std::to_string(this->x) + "</x>\n");
	result.append("<y>" + std::to_string(this->y) + "</y>\n");
	result.append("<label>" + this->label + "</label>\n");
	result.append("<true>" + std::to_string(this->true_connection) + "</true>\n");
	result.append("<false>" + std::to_string(this->false_connection) + "</false>\n");
	result.append("</element>\n");

	return result;
}