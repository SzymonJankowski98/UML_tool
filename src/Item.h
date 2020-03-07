#pragma once

#include <string>


class Item
{
	const std::string label;

public:
	Item(const std::string &label) : label(label) {}
	virtual ~Item() {}

	virtual const std::string& getLabel() const { return label; }
};

