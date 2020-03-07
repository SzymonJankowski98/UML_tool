#pragma once

#include "Key.h"

#include <unordered_map>


class KeyboardKey final :
	public Key
{
	const int code;

	static const std::unordered_map<int, std::string> keyMap;

public:
	KeyboardKey(const int);
	~KeyboardKey() override;

	int getCode() const;
};

