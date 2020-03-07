#pragma once

#include "BaseBackend.h"
#include "Terminal.h"
#include "NormalMode.h"
#include "TooSmallMode.h"
#include "HelpMode.h"
#include "AlertMode.h"
#include "ParamMode.h"

#include <functional>


class MceditBackend :
	public BaseBackend
{
	bool isOpen;
	Terminal terminal;
	Input input;
	std::function<void()> editionHandler;
	std::vector<Bind> bindsCollection;
	Menu menu;
	NormalMode normalMode;
	TooSmallMode tooSmallMode;
	HelpMode helpMode;
	AlertMode alertMode;
	ParamMode paramMode;
	Mode *currentMode;

	static const std::string unsavedAlert;

public:
	MceditBackend(BaseTool *const);
	~MceditBackend() override;

	void bind(const std::string&, std::function<void()>, const std::string&) override;
	void start() override;
	void handleResize();
	void handleModeEnd();
	void handleParam(const OptionItem*);

private:
	void helpHandler();
	void quitHandler();
};

