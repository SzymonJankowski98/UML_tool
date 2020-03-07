#include "ParamMode.h"
#include "margins.h"
#include "colors.h"

#include <stdexcept>



ParamMode::ParamMode(Input &input, BaseTool &tool) :
	Mode(input),
	tool(tool)
{}


ParamMode::~ParamMode()
{
	if (window)
		delwin(window);
}


void ParamMode::operator()()
{
	initWindow();
	buffer = "";
	bufferPosition = 0;
	while (1) {
		renderBuffer();

		auto &inputKey = input.getKey();

		try {
			auto &key = dynamic_cast<const ResizeKey&>(inputKey);
			delWindow();
			throw Resize();
			continue;
		} catch (std::bad_cast&) {}

		try {
			auto &key = dynamic_cast<const KeyboardKey&>(inputKey);

			switch (key.getCode()) {
			case 27:	//esc
				delWindow();
				throw End();
				break;
			case 13:	//enter
				tool.setEntry(target->getEntry(), buffer);
				target->handle();
				delWindow();
				throw End();
				break;
			default:
				addToBuffer(key);
			}
			continue;
		}
		catch (std::bad_cast&) {}
	}
}


void ParamMode::initWindow()
{
	paramToLines();
	innerHeight = lines.size() + PARAM_VERTICAL_MARGINS + PARAM_BETWEEN_MARGIN + 1;
	bufferX = (PARAM_HORIZONTAL_MARGINS / 2);
	bufferY = innerHeight - (PARAM_VERTICAL_MARGINS / 2) - 1;
	bufferWidth = innerWidth - PARAM_HORIZONTAL_MARGINS;
	window = newwin(innerHeight, innerWidth, (LINES - innerHeight) / 2, (COLS - innerWidth) / 2);
	renderWindow();
}


void ParamMode::paramToLines()
{
	size_t pos = 0, prev = 0, maxLineWidth = COLS / 2;
	innerWidth = maxLineWidth + PARAM_HORIZONTAL_MARGINS;
	auto &param = target->getParam();

	std::vector<std::string> words;
	while (pos != std::string::npos) {
		pos = param.find(' ', prev);
		words.push_back(param.substr(prev, pos - prev));
		prev = pos + 1;
	}

	lines.clear();
	std::string line = "";
	for (const auto &word : words) {
		if (line.size() + word.size() + 1 <= maxLineWidth)
			line += " " + word;
		else {
			lines.push_back(line);
			size_t i = 0;
			for (; i < word.size() / maxLineWidth; ++i)
				lines.push_back(word.substr(i * maxLineWidth, maxLineWidth));
			line = word.substr(i * maxLineWidth, maxLineWidth);
		}
	}
	if (!line.empty())
		lines.push_back(line);
}


void ParamMode::renderWindow()
{
	wattron(window, COLOR_PAIR(PARAM_PAIR));
	std::string fill(innerWidth * innerHeight, ' ');
	mvwprintw(window, 0, 0, "%s", fill.c_str());

	for (size_t i = 0; i < lines.size(); ++i)
		mvwprintw(window, i + 1, (bufferWidth - lines[i].size()) / 2, "%s", lines[i].c_str());
	wattroff(window, COLOR_PAIR(PARAM_PAIR));
	wrefresh(window);
}


void ParamMode::delWindow()
{
	wclear(window);
	delwin(window);
}


void ParamMode::renderBuffer()
{
	size_t cursor;
	wmove(window, bufferY, bufferX);
	wattron(window, COLOR_PAIR(BUFFER_PAIR));
	if (buffer.size() < bufferWidth) {
		wprintw(window, "%s", (buffer + std::string(bufferWidth - buffer.size(), ' ')).c_str());
		cursor = bufferPosition;
	}
	else if (bufferPosition <= bufferWidth) {
		wprintw(window, "%s", buffer.substr(0, bufferWidth).c_str());
		cursor = bufferPosition;
	}
	else {
		size_t first = bufferPosition - bufferWidth;
		wprintw(window, "%s", (bufferPosition == buffer.size() ?
			buffer.substr(first, bufferWidth - 1) + " " :
			buffer.substr(first, bufferWidth)
		).c_str());
		cursor = bufferWidth - 1;
	}
	wattroff(window, COLOR_PAIR(BUFFER_PAIR));

	wattron(window, COLOR_PAIR(PARAM_PAIR));
	mvwaddstr(window, bufferY + 1, 0, std::string(innerWidth, ' ').c_str());
	mvwaddch(window, bufferY + 1, bufferX + cursor, 0xaf);
	wattroff(window, COLOR_PAIR(PARAM_PAIR));

	wrefresh(window);
}


void ParamMode::addToBuffer(const KeyboardKey &key)
{
	switch (key.getCode()) {
	case 8:	//bs
		if (bufferPosition > 0)
			buffer.erase(bufferPosition-- - 1, 1);
		break;
	case 260:	//larrow
		if (bufferPosition > 0)
			--bufferPosition;
		break;
	case 261:	//rarrow
		if (bufferPosition < buffer.size())
			++bufferPosition;
		break;
	default:
		try {
			char c = mapToChar.at(key.getCode());
			if (bufferPosition == 0)
				buffer = c + buffer;
			else if (bufferPosition == buffer.size())
				buffer += c;
			else
				buffer = buffer.substr(0, bufferPosition + 1) + c + buffer.substr(bufferPosition + 1);
			++bufferPosition;
		}
		catch (std::out_of_range&) {}
	}
}


const std::unordered_map<int, char> ParamMode::mapToChar = {
{32, ' '},
{33, '!'},
{34, '"'},
{35, '#'},
{36, '$'},
{37, '%'},
{38, '&'},
{39, '\''},
{40, '('},
{41, ')'},
{42, '*'},
{43, '+'},
{44, ','},
{45, '-'},
{46, '.'},
{47, '/'},
{48, '0'},
{49, '1'},
{50, '2'},
{51, '3'},
{52, '4'},
{53, '5'},
{54, '6'},
{55, '7'},
{56, '8'},
{57, '9'},
{58, ':'},
{59, ';'},
{60, '<'},
{61, '='},
{62, '>'},
{63, '?'},
{64, '@'},
{65, 'A'},
{66, 'B'},
{67, 'C'},
{68, 'D'},
{69, 'E'},
{70, 'F'},
{71, 'G'},
{72, 'H'},
{73, 'I'},
{74, 'J'},
{75, 'K'},
{76, 'L'},
{77, 'M'},
{78, 'N'},
{79, 'O'},
{80, 'P'},
{81, 'Q'},
{82, 'R'},
{83, 'S'},
{84, 'T'},
{85, 'U'},
{86, 'V'},
{87, 'W'},
{88, 'X'},
{89, 'Y'},
{90, 'Z'},
{91, '['},
{92, '\\'},
{93, ']'},
{94, '^'},
{95, '_'},
{96, '`'},
{97, 'a'},
{98, 'b'},
{99, 'c'},
{100, 'd'},
{101, 'e'},
{102, 'f'},
{103, 'g'},
{104, 'h'},
{105, 'i'},
{106, 'j'},
{107, 'k'},
{108, 'l'},
{109, 'm'},
{110, 'n'},
{111, 'o'},
{112, 'p'},
{113, 'q'},
{114, 'r'},
{115, 's'},
{116, 't'},
{117, 'u'},
{118, 'v'},
{119, 'w'},
{120, 'x'},
{121, 'y'},
{122, 'z'},
{123, '{'},
{124, '|'},
{125, '}'},
{126, '~'}
};