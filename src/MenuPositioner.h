#pragma once

#include "ItemPosition.h"
#include "MenuData.h"

#include <unordered_map>


class MenuPositioner final
{
	const MenuData& data;

	int minWidth, minHeight;
	std::unordered_map<const Item*, ItemPosition> position;

public:
	MenuPositioner(const MenuData&);
	~MenuPositioner();

	void setPosition();
	const Item* itemAt(const int, const int) const;
	int getMinWidth() const { return minWidth; }
	int getMinHeight() const { return minHeight; }
	const ItemPosition& getPosition(const Item &item) const { return position.at(&item); }
};

