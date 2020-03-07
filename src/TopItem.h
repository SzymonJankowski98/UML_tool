#pragma once

#include "OptionItem.h"

#include <vector>


class TopItem final :
	public Item
{
	std::vector<OptionItem> options;

public:
	TopItem(const std::string&);
	~TopItem();

	void addItem(const OptionItem&);
	const std::vector<OptionItem>& getItems() const { return options; }
};
