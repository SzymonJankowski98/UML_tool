#pragma once

#include <string>


class Key
{
	const std::string representation;

public:
	Key(const std::string &representation) : representation(representation) {}
	virtual ~Key() {};

	virtual const std::string& getRepresentation() const { return representation; }
};
