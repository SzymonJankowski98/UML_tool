#include "OptionItem.h"



OptionItem::OptionItem(const std::string &label, const std::string &param, const std::string &entry, const std::function<void()> handler) :
	Item(label),
	param(param), entry(entry), handler(handler)
{}


OptionItem::~OptionItem()
{}
