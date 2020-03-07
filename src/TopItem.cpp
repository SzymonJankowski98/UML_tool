#include "TopItem.h"



TopItem::TopItem(const std::string &label) :
	Item(label)
{}


TopItem::~TopItem()
{}


void TopItem::addItem(const OptionItem &item)
{
	options.push_back(item);
}