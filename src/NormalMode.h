#pragma once

#include "BaseTool.h"
#include "Mode.h"
#include "Menu.h"
#include "Bind.h"

#include <functional>


class NormalMode :
	public Mode
{
	BaseTool &tool;
	Menu &menu;
	const std::function<void()> &editionHandler;

public:
	NormalMode(Input&, BaseTool&, Menu&, const std::function<void()>&);
	~NormalMode() override;

	void operator()() override;

private:
	void handle(const ResizeKey&);
	void handle(const MouseKey&);
	void handle(const KeyboardKey&);
};

