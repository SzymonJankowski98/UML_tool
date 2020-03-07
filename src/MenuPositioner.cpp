#include "MenuPositioner.h"
#include "margins.h"



MenuPositioner::MenuPositioner(const MenuData &data) :
	data(data),
	minWidth(0), minHeight(0)
{}


MenuPositioner::~MenuPositioner()
{}


void MenuPositioner::setPosition()
{
	int currentDx = 0, currentDy, itemWidth, optionWidth, maxOptionWidth;
	for (auto &item : data.getItems()) {
		itemWidth = item.getLabel().size() + TOP_MARGINS;
		position.emplace(&item, ItemPosition(itemWidth, 1, currentDx, 0));

		maxOptionWidth = 0;
		for (auto &option : item.getItems()) {
			optionWidth = option.getLabel().size() + OPTION_MARGINS;
			if (optionWidth > maxOptionWidth) maxOptionWidth = optionWidth;
		}

		currentDy = 1;
		for (auto &option : item.getItems()) {
			position.emplace(&option, ItemPosition(maxOptionWidth, 1, currentDx, currentDy++));
		}
		currentDx += itemWidth;

		if (currentDx + maxOptionWidth > minWidth) minWidth = currentDx + maxOptionWidth;
		if (currentDy > minHeight) minHeight = currentDy;
	}
	if (currentDx > minWidth) minWidth = currentDx;
}


const Item* MenuPositioner::itemAt(const int x, const int y) const
{
	for (auto &item : data.getItems())
		if (position.at(&item).clicked(x, y)) return &item;
	auto selected = data.getSelected();
	if (selected != nullptr) {
		for (auto &item : selected->getItems())
			if (position.at(&item).clicked(x, y))
				return &item;
	}
	return nullptr;
}
