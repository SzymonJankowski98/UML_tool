#pragma once

#include "Mode.h"


class AlertMode :
	public Mode
{
	std::vector<std::string> lines;
	size_t width;

public:
	AlertMode(Input&);
	~AlertMode() override;

	void operator()() override;
	void setMessage(const std::string&);
};

