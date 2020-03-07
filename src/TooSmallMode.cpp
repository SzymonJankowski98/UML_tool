#include "TooSmallMode.h"



TooSmallMode::TooSmallMode(Input &input) :
	Mode(input)
{}


TooSmallMode::~TooSmallMode()
{}


void TooSmallMode::operator()()
{
	clear();
	printw("Too small screen!");
	refresh();

	while (1) {
		try {
			dynamic_cast<const ResizeKey&>(input.getKey());
			throw Resize();
		}
		catch (std::bad_cast&) {}
	}
}
