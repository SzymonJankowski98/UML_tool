#pragma once

#include "Input.h"


class Mode
{
protected:
	Input &input;

public:
	Mode(Input &input) :
		input(input)
	{}
	virtual ~Mode() {};

	virtual void operator()() = 0;

	class Resize {};
	class End {};
};
