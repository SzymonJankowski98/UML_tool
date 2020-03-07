#pragma once

#include "KeyboardKey.h"
#include "MouseKey.h"
#include "ResizeKey.h"

#include <curses.h>
#include <memory>


constexpr int resizeSleep = 500;


class Input final
{
	std::unique_ptr<Key> key;

public:
	Input();
	~Input();

	const Key& getKey();

	class UndefinedKey {};
};

