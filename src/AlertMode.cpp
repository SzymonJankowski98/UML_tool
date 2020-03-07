#include "AlertMode.h"
#include "margins.h"
#include "colors.h"



AlertMode::AlertMode(Input &input) :
	Mode(input)
{}


AlertMode::~AlertMode()
{}


void AlertMode::operator()()
{
	size_t height = lines.size() + ALERT_VERTICAL_MARGINS;
	auto *window = newwin(
		height, width,
		(LINES - height) / 2,
		(COLS - width) / 2
	);
	wattron(window, COLOR_PAIR(ALERT_PAIR));
	mvwprintw(window, 0, 0, "%s", std::string(width, ' ').c_str());
	mvwprintw(window, height - 1, 0, "%s", std::string(width, ' ').c_str());
	for (size_t i = 0; i < lines.size(); ++i) {
		mvwprintw(window, i + 1, 0, "%s", std::string(width, ' ').c_str());
		mvwprintw(window, i + 1, (width - lines[i].size()) / 2, "%s", lines[i].c_str());
	}
	wattroff(window, COLOR_PAIR(ALERT_PAIR));
	wrefresh(window);

	auto &key = input.getKey();

	wclear(window);
	delwin(window);

	try {
		dynamic_cast<const ResizeKey&>(key);
		throw Resize();
	}
	catch (std::bad_cast&) {
		throw End();
	}
}


void AlertMode::setMessage(const std::string &text)
{
	size_t pos = 0, prev = 0, maxLineWidth = COLS / 2;
	width = maxLineWidth + ALERT_HORIZONTAL_MARGINS;

	std::vector<std::string> words;
	while (pos != std::string::npos) {
		pos = text.find(' ', prev);
		words.push_back(text.substr(prev, pos - prev));
		prev = pos + 1;
	}

	lines.clear();
	std::string line = "";
	for (const auto &word : words) {
		if (line.size() + word.size() + 1 <= maxLineWidth)
			line += " " + word;
		else {
			lines.push_back(line);
			size_t i;
			for (i = 0; i < word.size() / maxLineWidth; ++i)
				lines.push_back(word.substr(i * maxLineWidth, maxLineWidth));
			line = word.substr(i * maxLineWidth, maxLineWidth);
		}
	}
	if (!line.empty())
		lines.push_back(line);
}