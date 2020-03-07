#include "StartBlock.h"

void StartBlock::change_label(std::string label) {}

std::string StartBlock::get_as_string()
{
	std::string result = "";
	result.append("<element type=\"Start\">\n");
	result.append("<x>" + std::to_string(this->x) + "</x>\n");
	result.append("<y>" + std::to_string(this->y) + "</y>\n");
	result.append("<connections>\n");
	for (int i = 0; i < this->connections.size(); i++)
	{
		result.append("<id>" + std::to_string(this->connections[i]) + "</id>\n");
	}
	result.append("</connections>\n");
	result.append("</element>\n");

	return result;
}