#include "FinishBlock.h"

void FinishBlock::change_label(std::string label) {}

std::string FinishBlock::get_as_string()
{
	std::string result = "";
	result.append("<element type=\"Finish\">\n");
	result.append("<x>" + std::to_string(this->x) + "</x>\n");
	result.append("<y>" + std::to_string(this->y) + "</y>\n");
	result.append("</element>\n");

	return result;
}