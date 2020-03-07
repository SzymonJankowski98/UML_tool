#include "Input.h"

#include <thread>
#include <chrono>
#include <stdexcept>



Input::Input()
{}


Input::~Input()
{}


const Key& Input::getKey()
{
	int code = getch();
	switch (code) {
	case KEY_RESIZE:
		std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(resizeSleep));
		key = std::unique_ptr<Key>(new ResizeKey());
		break;
	case KEY_MOUSE:
		MEVENT event;
		nc_getmouse(&event);
		key = std::unique_ptr<Key>(new MouseKey(event));
		break;
	default:
		try {
			key = std::unique_ptr<Key>(new KeyboardKey(code));
		}
		catch (std::out_of_range&) {
			throw UndefinedKey();
		}
	}
	return *key;
}