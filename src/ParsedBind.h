#pragma once

#include <string>
#include <functional>
#include <regex>


class ParsedBind final
{
	std::smatch regexResult;
	static const std::regex itemRegex, editionRegex;

public:
	const std::string top, option, param, entry;

public:
	ParsedBind(const std::string&);
	~ParsedBind();
	
	class Invalid {};
	class Edition {};

private:
	static std::smatch parse(const std::string&);
};

