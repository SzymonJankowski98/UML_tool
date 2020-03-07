#pragma once

#include <string>
#include <curses.h>
#include <exception>


class BaseTool
{
public:
	virtual ~BaseTool() {};

	virtual std::string getEntry(const std::string&) const = 0;
	virtual void setEntry(const std::string&, const std::string&) = 0;
	virtual void assignWindow(WINDOW*) = 0;

	class UndefinedEntry {};
};
