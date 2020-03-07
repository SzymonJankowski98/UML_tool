#pragma once

#include "TopItem.h"


class MenuData
{
	std::vector<TopItem> items;
	const TopItem *selected;

public:
	MenuData();
	~MenuData();

	void addItem(const TopItem&);
	const std::vector<TopItem>& getItems() const { return items; }
	const TopItem* getSelected() const { return selected; }
	TopItem& getByLabel(const std::string&);
	void select(const TopItem *item) { selected = item; }

	class UndefinedItem {};
};
