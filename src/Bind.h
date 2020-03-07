#pragma once

#include "ParsedBind.h"


class Bind final
{
	const std::string command, description;
	const std::function<void()> handler;

	const static std::regex backendRegex;

public:
	Bind(const std::string&, const std::function<void()>, const std::string&);
	~Bind();

	ParsedBind getParsed() const;
	const std::function<void()>& getHandler() const { return handler; }
	std::string toString() const;

private:
	static std::string getCommand(const std::string&);
};

