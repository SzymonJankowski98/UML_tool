#include "Terminal.h"



Terminal::Terminal()
{
	initscr();
	initColors();
	init();
}


Terminal::~Terminal()
{
	del();
	endwin();
}


void Terminal::init()
{
	noecho();
	cbreak();
	raw();
	keypad(stdscr, true);
	mousemask(BUTTON1_CLICKED, NULL);
	curs_set(0);
	refresh();

	toolWindow.init(COLS, LINES - 1, 0, 1);
	menuWindow.init(COLS, 1, 0, 0);
}


void Terminal::resize()
{
	del();
	resize_term(0, 0);
	init();
}


void Terminal::initColors()
{
	start_color();

	init_color(MENU_ODD_FG_COLOR, 0, 0, 0);
	init_color(MENU_ODD_BG_COLOR, 1000, 1000, 1000);
	init_pair(MENU_ODD_PAIR, MENU_ODD_FG_COLOR, MENU_ODD_BG_COLOR);

	init_color(MENU_EVEN_FG_COLOR, 0, 0, 0);
	init_color(MENU_EVEN_BG_COLOR, 750, 750, 750);
	init_pair(MENU_EVEN_PAIR, MENU_EVEN_FG_COLOR, MENU_EVEN_BG_COLOR);

	init_color(SUBMENU_ODD_FG_COLOR, 0, 0, 0);
	init_color(SUBMENU_ODD_BG_COLOR, 1000, 1000, 1000);
	init_pair(SUBMENU_ODD_PAIR, SUBMENU_ODD_FG_COLOR, SUBMENU_ODD_BG_COLOR);

	init_color(SUBMENU_EVEN_FG_COLOR, 0, 0, 0);
	init_color(SUBMENU_EVEN_BG_COLOR, 750, 750, 750);
	init_pair(SUBMENU_EVEN_PAIR, SUBMENU_EVEN_FG_COLOR, SUBMENU_EVEN_BG_COLOR);

	init_color(ALERT_FG_COLOR, 0, 0, 0);
	init_color(ALERT_BG_COLOR, 750, 0, 0);
	init_pair(ALERT_PAIR, ALERT_FG_COLOR, ALERT_BG_COLOR);

	init_color(PARAM_FG_COLOR, 0, 0, 0);
	init_color(PARAM_BG_COLOR, 1000, 1000, 1000);
	init_pair(PARAM_PAIR, PARAM_FG_COLOR, PARAM_BG_COLOR);

	init_color(BUFFER_FG_COLOR, 0, 0, 0);
	init_color(BUFFER_BG_COLOR, 750, 750, 750);
	init_pair(BUFFER_PAIR, BUFFER_FG_COLOR, BUFFER_BG_COLOR);

	init_color(HELP_ODD_FG_COLOR, 0, 0, 0);
	init_color(HELP_ODD_BG_COLOR, 1000, 1000, 1000);
	init_pair(HELP_ODD_PAIR, HELP_ODD_FG_COLOR, HELP_ODD_BG_COLOR);

	init_color(HELP_EVEN_FG_COLOR, 0, 0, 0);
	init_color(HELP_EVEN_BG_COLOR, 750, 750, 750);
	init_pair(HELP_EVEN_PAIR, HELP_EVEN_FG_COLOR, HELP_EVEN_BG_COLOR);
}


void Terminal::restore()
{
	touchwin(menuWindow.getWindow());
	touchwin(toolWindow.getWindow());
	wnoutrefresh(menuWindow.getWindow());
	wnoutrefresh(toolWindow.getWindow());
	doupdate();
}


void Terminal::del()
{
	toolWindow.del();
	menuWindow.del();
	clear();
	refresh();
}
