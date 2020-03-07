#pragma once

#include "BaseTool.h"

#include <string>
#include <functional>


class BaseBackend
{
protected:
	BaseTool *const tool;

public:
	BaseBackend(BaseTool *const tool) : tool(tool) {};
	virtual ~BaseBackend() {};

	virtual void bind(const std::string&, std::function<void()>, const std::string&) = 0;
	virtual void start() = 0;
};

