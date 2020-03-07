#include "NormalMode.h"



NormalMode::NormalMode(Input &input, BaseTool &tool, Menu &menu, const std::function<void()> &editionHandler) :
	Mode(input),
	tool(tool),
	menu(menu),
	editionHandler(editionHandler)
{}


NormalMode::~NormalMode()
{}


void NormalMode::operator()()
{
	auto &inputKey = input.getKey();

	try {
		auto &key = dynamic_cast<const ResizeKey&>(inputKey);
		handle(key);
		return;
	}
	catch (std::bad_cast&) {}

	try {
		auto &key = dynamic_cast<const MouseKey&>(inputKey);
		handle(key);
		return;
	}
	catch (std::bad_cast&) {}

	try {
		auto &key = dynamic_cast<const KeyboardKey&>(inputKey);
		handle(key);
		return;
	}
	catch (std::bad_cast&) {}
}

void NormalMode::handle(const ResizeKey &key)
{
	throw Resize();
}


void NormalMode::handle(const MouseKey &key)
{
	auto item = menu.itemAt(key.getX(), key.getY());

	if (item == nullptr) {
		menu.select(nullptr);
		tool.setEntry("KEY", key.getRepresentation());
		if (editionHandler)
			editionHandler();
	}
	else if (auto topItem = dynamic_cast<const TopItem*>(item)) {
		menu.select(topItem);
	}
	else if (auto optionItem = dynamic_cast<const OptionItem*>(item)) {
		menu.select(nullptr);
		if (optionItem->getParam().empty())
			optionItem->handle();
		else throw optionItem;
	}
}


void NormalMode::handle(const KeyboardKey &key)
{
	if (menu.getSelected() == nullptr) {
		tool.setEntry("KEY", key.getRepresentation());
		if (editionHandler)
			editionHandler();
	}
}