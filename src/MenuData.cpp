#include "MenuData.h"



MenuData::MenuData()
{}


MenuData::~MenuData()
{}


void MenuData::addItem(const TopItem &item)
{
	items.push_back(item);
}


TopItem& MenuData::getByLabel(const std::string &label)
{
	for (auto &item : items)
		if (item.getLabel() == label)
			return item;
	throw UndefinedItem();
}