#pragma once

#include "Item.h"

#include <functional>


class OptionItem final :
	public Item
{
	const std::string param, entry;
	const std::function<void()> handler;

public:
	OptionItem(const std::string&, const std::string&, const std::string&, const std::function<void()>);
	~OptionItem();

	const std::string& getParam() const { return param; }
	const std::string& getEntry() const { return entry; }
	void handle() const { handler(); }
};

