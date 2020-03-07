#pragma once

#include "MenuData.h"
#include "ParsedBind.h"
#include "MenuPositioner.h"

#include <functional>
#include <curses.h>


class Menu final
{
	MenuData data;
	MenuPositioner positioner;
	WINDOW *const &menuWindow, *const &toolWindow, *optionsWindow;

public:
	Menu(WINDOW *const&, WINDOW *const&);
	~Menu();

	void addItem(const ParsedBind&, const std::function<void()>);
	void select(const TopItem *item) { data.select(item); renderOptions(); }
	void setPosition() { positioner.setPosition(); }

	const std::vector<TopItem> getItems() const { return data.getItems(); }
	const TopItem* getSelected() const { return data.getSelected(); }
	const Item* itemAt(const int x, const int y) const { return positioner.itemAt(x, y); }

	void renderTop();
	void renderOptions();
	void hideOptions();

	class TooSmallTerminal {};
};

