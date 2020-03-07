#include "MouseKey.h"



MouseKey::MouseKey(const MEVENT &event) :
	Key("<" + std::to_string(event.x) + "," + std::to_string(event.y) + ">"),
	x(event.x), y(event.y)
{}


MouseKey::~MouseKey()
{}


int MouseKey::getX() const
{
	return x;
}


int MouseKey::getY() const
{
	return y;
}