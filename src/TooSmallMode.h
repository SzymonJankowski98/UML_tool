#pragma once

#include "Mode.h"


class TooSmallMode :
	public Mode
{
public:
	TooSmallMode(Input&);
	~TooSmallMode() override;

	void operator()() override;
};

