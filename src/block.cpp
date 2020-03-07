#include "block.h"

Block::Block(int size, std::string label, int x, int y) : size(size), label(label), x(x), y(y)
{
	
}

void Block::setX(int val)
{
	this->x = val;
}

void Block::setY(int val)
{
	this->y = val;
}

void Block::moveX(int val)
{
	this->x += val;
}

void Block::moveY(int val)
{
	this->y += val;
}

int Block::getX()
{
	return this->x;
}

int Block::getY()
{
	return this->y;
}

void Block::change_label(std::string label)
{
	this->label = label;
}