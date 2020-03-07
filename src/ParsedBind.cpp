#include "ParsedBind.h"



ParsedBind::ParsedBind(const std::string &command) :
	regexResult(parse(command)),
	top(regexResult[1]),
	option(regexResult[2]),
	param(regexResult[3]),
	entry(regexResult[4])
{}


ParsedBind::~ParsedBind()
{}


std::smatch ParsedBind::parse(const std::string &command)
{
	std::smatch result;
	if (std::regex_match(command, result, itemRegex))
		return result;
	else if (std::regex_match(command, result, editionRegex))
		throw Edition();
	else throw Invalid();
}


const std::regex ParsedBind::itemRegex(
	"^"
	"\\.(.+?)"	//top label
	"\\.(.+?)"	//option label
	"(?:\\$\\{"			//param
	"([^\\|]*)"			//param label
	"\\|"
	"([^\\}]*)"			//entry name
	"\\})?"
	"$"
), ParsedBind::editionRegex(
	"^"
	"<EDITION>"
	"$"
);
