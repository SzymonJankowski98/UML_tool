#pragma once

#include "Mode.h"
#include "Bind.h"

#include <vector>
#include <curses.h>


class HelpMode :
	public Mode
{
	const std::vector<Bind> &bindsCollection;
	WINDOW *window;
	std::vector<std::string> lines;
	size_t firstIndex;

public:
	HelpMode(Input&, const std::vector<Bind>&);
	~HelpMode() override;

	void operator()() override;

private:
	void initWindow();
	void fillLines();
	void endWindow();
	void handle(const ResizeKey&);
	void handle(const KeyboardKey&);
	void renderLines();

	static size_t lineBreakPosition(const std::string&);
};

