#include "Bind.h"



Bind::Bind(const std::string &command, const std::function<void()> handler, const std::string &description) :
	command(getCommand(command)), handler(handler), description(description)
{}


Bind::~Bind()
{}


ParsedBind Bind::getParsed() const
{
	return ParsedBind(command);
}


std::string Bind::toString() const
{
	return command + "  -  " + description;
}


std::string Bind::getCommand(const std::string &command)
{
	std::smatch match;
	std::regex_match(command, match, backendRegex);
	return match[1];
}


const std::regex Bind::backendRegex(
	"^"
	"(?:#mcedit#)?"
	"(.*)"
	"$"
);