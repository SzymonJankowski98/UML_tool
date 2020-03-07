#pragma once

#include "Mode.h"
#include "BaseTool.h"
#include "OptionItem.h"


class ParamMode :
	public Mode
{
	BaseTool &tool;
	const OptionItem *target;
	WINDOW *window;
	size_t innerWidth, innerHeight;
	std::vector<std::string> lines;
	std::string buffer;
	size_t bufferPosition, bufferX, bufferY, bufferWidth;

	static const std::unordered_map<int, char> mapToChar;

public:
	ParamMode(Input&, BaseTool&);
	~ParamMode() override;

	void operator()() override;
	void setTarget(const OptionItem *item) { target = item; }

private:
	void initWindow();
	void paramToLines();
	void renderWindow();
	void delWindow();
	void renderBuffer();
	void addToBuffer(const KeyboardKey&);
};

