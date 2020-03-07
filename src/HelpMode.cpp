#include "HelpMode.h"
#include "colors.h"



HelpMode::HelpMode(Input &input, const std::vector<Bind> &bindsCollection) :
	Mode(input),
	bindsCollection(bindsCollection)
{}


HelpMode::~HelpMode()
{}


void HelpMode::operator()()
{
	initWindow();
	fillLines();
	firstIndex = 0;
	while (1) {
		renderLines();

		auto &inputKey = input.getKey();

		try {
			auto &key = dynamic_cast<const ResizeKey&>(inputKey);
			handle(key);
			continue;
		}
		catch (std::bad_cast&) {}

		try {
			auto &key = dynamic_cast<const KeyboardKey&>(inputKey);
			handle(key);
			continue;
		}
		catch (std::bad_cast&) {}
	}
}


void HelpMode::initWindow()
{
	window = newwin(LINES, COLS, 0, 0);
}


void HelpMode::fillLines()
{
	lines.clear();
	lines = {
		"       q    Close help",
		"<UARROW>    Scroll help up",
		"<DARROW>    Scroll help down",
		"     "
	};
	for (auto &bind : bindsCollection)
		lines.push_back(bind.toString());
}


void HelpMode::endWindow()
{
	wclear(window);
	delwin(window);
}


void HelpMode::handle(const ResizeKey &key)
{
	endWindow();
	throw Resize();
}


void HelpMode::handle(const KeyboardKey &key)
{
	switch (key.getCode()) {
	case 'q':
		endwin();
		throw End();
		break;
	case 259:	//up
		if (firstIndex != 0) 
			--firstIndex;
		break;
	case 258:
		if (firstIndex != lines.size() - 1) 
			++firstIndex;
		break;
	}
}


void HelpMode::renderLines()
{
	wclear(window);
	short current = HELP_EVEN_PAIR, next = HELP_ODD_PAIR; 
	if (firstIndex % 2 == 1)
		std::swap(current, next);
	size_t i, last;
	for (i = firstIndex, last = firstIndex + LINES; i < lines.size() && i != last; ++i) {
		wattron(window, COLOR_PAIR(current));
		wprintw(window, "%s", lines[i].c_str());
		waddstr(window, std::string(COLS - getcurx(window), ' ').c_str());
		wattroff(window, COLOR_PAIR(current));
		std::swap(current, next);
	}

	std::string fill((LINES - getcury(window)) * COLS, ' ');
	wattron(window, COLOR_PAIR(current));
	waddstr(window, fill.c_str());
	wattroff(window, COLOR_PAIR(current));

	wrefresh(window);
}


size_t HelpMode::lineBreakPosition(const std::string &line)
{
	size_t pos = 0;
	for (auto &c : line) {
		if (pos + 1 > static_cast<size_t>(COLS))
			return pos;
		++pos;
	}
	return pos;
}
