#include "UMLTool.h"

UMLTool::UMLTool():move_mode(0), edit_mode(0), temp_connection_counter(0) 
{
	setEntry("IS_SAVED", "YES");
}


UMLTool::~UMLTool()
{
	delete this->current_file;
}


std::string UMLTool::getEntry(const std::string &key) const
{
	try {
		return entries.at(key);
	}
	catch (std::out_of_range&) {
		throw BaseTool::UndefinedEntry();
	}
}


void UMLTool::setEntry(const std::string &key, const std::string &value)
{
	entries[key] = value;
}


void UMLTool::assignWindow(WINDOW *windowptr)
{
	window = windowptr;
}


void UMLTool::edition()
{
	if (getEntry("KEY") == "<RESIZE>") {
		if (this->current_file != nullptr)
		{
			wclear(window);
			this->current_file->print_diagram(window);
		}
	}
	else if (getEntry("KEY") == "<DARROW>") {
		if (this->current_file != nullptr)
		{
			if (move_mode == 1)
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->current_file->move_picked_node_X(1);
				this->current_file->print_diagram(window);
			}
			else if (move_mode == 0)
			{
				wclear(window);
				this->current_file->move_window_down();
				this->current_file->print_diagram(window);
			}
		}
	}
	else if (getEntry("KEY") == "<UARROW>") {
		if (this->current_file != nullptr)
		{
			if (move_mode == 1)
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->current_file->move_picked_node_X(-1);
				this->current_file->print_diagram(window);
			}
			else if(move_mode == 0)
			{
				wclear(window);
				this->current_file->move_window_up();
				this->current_file->print_diagram(window);
			}
		}
	}
	else if (getEntry("KEY") == "<LARROW>") {
		if (this->current_file != nullptr)
		{
			if (move_mode == 1)
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->current_file->move_picked_node_Y(-1);
				this->current_file->print_diagram(window);
			}
			else if (move_mode == 0)
			{
				wclear(window);
				this->current_file->move_window_left();
				this->current_file->print_diagram(window);
			}
		}
	}
	else if (getEntry("KEY") == "<RARROW>") {
		if (this->current_file != nullptr)
		{
			if (move_mode == 1)
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->current_file->move_picked_node_Y(1);
				this->current_file->print_diagram(window);
			}
			else if (move_mode == 0)
			{
				wclear(window);
				this->current_file->move_window_right();
				this->current_file->print_diagram(window);
			}
		}
	}
	else if (getEntry("KEY") == "<TAB>") {
		if (this->current_file != nullptr)
		{
			if (this->edit_mode == 0)
			{
				wclear(window);
				this->current_file->next_node();
				this->current_file->print_diagram(window);
			}
			else if (this->edit_mode == 1)
			{
				wclear(window);
				this->increment_temp_connections();
				this->current_file->set_connection_to_add(this->temp_connections[this->temp_connection_counter]);
				this->current_file->print_diagram(window);
			}
			else if (this->edit_mode == 2)
			{
				wclear(window);
				this->increment_temp_connections();
				this->current_file->set_connection_to_delete(this->temp_connections[this->temp_connection_counter]);
				this->current_file->print_diagram(window);
			}
		}
	}
	else if (getEntry("KEY") == "<ESC>") {
		if (this->current_file != nullptr)
		{
			wclear(window);
			this->edit_mode = 0;
			this->current_file->set_connection_to_add(-1);
			this->current_file->set_connection_to_delete(-1);
			this->current_file->print_diagram(window);
		}
	}
	else if (getEntry("KEY") == "<ENTER>") {
		if (this->current_file != nullptr)
		{
			if (this->edit_mode == 1)
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->edit_mode = 0;
				this->current_file->add_connection();
				this->current_file->print_diagram(window);
			}
			else if (this->edit_mode == 2)
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->edit_mode = 0;
				this->current_file->delete_connection();
				this->current_file->print_diagram(window);
			}
		}
	}
	else if (getEntry("KEY") == "f") {
	if (this->current_file != nullptr)
	{
		if (this->edit_mode == 1)
		{
			if (this->current_file->add_false_connection())
			{
				setEntry("IS_SAVED", "NO");
				wclear(window);
				this->edit_mode = 0;
				this->current_file->print_diagram(window);
			}
		}
	}
	}
	wrefresh(window);
}

void UMLTool::move_node()
{
	if (this->current_file != nullptr)
	{
		this->move_mode = 1;
	}
}

void UMLTool::move_diagram()
{
	if (this->current_file != nullptr)
	{
		this->move_mode = 0;
	}
}

void UMLTool::fill()
{
	int height, width;
	getmaxyx(window, height, width);
	wmove(window, 0, 0);
	for (int i = 0; i < height * width; ++i) {
		waddstr(window, (std::to_string(i) + " ").c_str());
		waddch(window, i);
	}
	wrefresh(window);
}


void UMLTool::unsave()
{
	setEntry("IS_SAVED", "NO");
}


void UMLTool::param()
{
	wprintw(window, "otoooo %s", getEntry("param").c_str());
}


void UMLTool::clear()
{
	wclear(window);
	wrefresh(window);
}

void UMLTool::new_diagram()
{
	this->file_name = "new_diagram";
	this->current_file = new UML_Diagram(5);
	this->clear();
	this->current_file->print_diagram(window);
}

void UMLTool::open()
{
	setEntry("IS_SAVED", "YES");
	std::string file_name = getEntry("file_name");
	this->file_name = file_name;
	//wprintw(window, "%s\n", ("../../XML_files/" + file_name + ".xml").c_str());
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(("..\\XML_files\\" + file_name + ".xml").c_str());

	this->current_file = new UML_Diagram(&xmlDoc, 5);

	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) return;
	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("schema");

	this->clear();
	this->current_file->print_diagram(window);
}

void UMLTool::save()
{
	std::string is_saved = getEntry("IS_SAVED");
	if (is_saved == "NO")
	{
		std::string result = this->current_file->generate_string();
		std::ofstream out("..\\XML_files\\" + this->file_name + ".xml");
		if (!out) 
		{
			std::cerr << "file open failed: ";
			return ;
		}
		out << result;
		out.close();
		setEntry("IS_SAVED", "YES");
	}
}

void UMLTool::save_as()
{
	this->file_name = getEntry("file_name");
	std::string result = this->current_file->generate_string();
	std::ofstream out("..\\XML_files\\" + this->file_name + ".xml");
	if (!out) 
	{
		std::cerr << "file open failed: ";
		return ;
	}
	out << result;
	out.close();
	setEntry("IS_SAVED", "YES");

}

void UMLTool::change_label()
{
	std::string label = getEntry("label");
	if (this->current_file != nullptr)
	{
		setEntry("IS_SAVED", "NO");
		wclear(window);
		this->current_file->change_label(label);
		this->current_file->print_diagram(window);
		wrefresh(window);
	}
}

void UMLTool::add_start_block()
{
	if (this->current_file != nullptr)
	{
		if (this->current_file->add_start_block())
		{
			setEntry("IS_SAVED", "NO");
			wclear(window);
			this->current_file->print_diagram(window);
			wrefresh(window);
		}
	}
}

void UMLTool::add_finish_block()
{
	if (this->current_file != nullptr)
	{
		if(this->current_file->add_finish_block())
		{
			setEntry("IS_SAVED", "NO");
				wclear(window);
				this->current_file->print_diagram(window);
				wrefresh(window);
		}
	}
}

void UMLTool::add_decision_block()
{
	if (this->current_file != nullptr)
	{
		setEntry("IS_SAVED", "NO");
		wclear(window);
		this->current_file->add_decision_block();
		this->current_file->print_diagram(window);
		wrefresh(window);
	}
}

void UMLTool::add_action_block()
{
	if (this->current_file != nullptr)
	{
		setEntry("IS_SAVED", "NO");
		wclear(window);
		this->current_file->add_action_block();
		this->current_file->print_diagram(window);
		wrefresh(window);
	}
}

void UMLTool::delete_block()
{
	if (this->current_file != nullptr)
	{
		setEntry("IS_SAVED", "NO");
		wclear(window);
		this->current_file->delete_element();
		this->current_file->print_diagram(window);
		wrefresh(window);
	}
}

void UMLTool::move_window_up()
{
	if (this->current_file != nullptr)
	{
		this->current_file->move_window_up();
	}
}

void UMLTool::move_window_down()
{
	if (this->current_file != nullptr)
	{
		this->current_file->move_window_down();
	}
}

void UMLTool::move_window_right()
{
	if (this->current_file != nullptr)
	{
		this->current_file->move_window_right();
	}
}

void UMLTool::move_window_left()
{
	if (this->current_file != nullptr)
	{
		this->current_file->move_window_left();
	}
}

void UMLTool::add_connection_mode()
{
	if (this->current_file != nullptr)
	{
		std::vector<int> possible_connections = this->current_file->possible_connections();
		if (possible_connections.size() > 0)
		{
			wclear(window);
			this->edit_mode = 1;
			this->temp_connections = possible_connections;
			this->temp_connection_counter = 0;
			this->current_file->set_connection_to_add(possible_connections[0]);
			this->current_file->print_diagram(window);
			wrefresh(window);
		}
	}
}

void UMLTool::delete_connection_mode()
{
	if (this->current_file != nullptr)
	{
		std::vector<int> connections_to_delete = this->current_file->connections_to_delete();
		if (connections_to_delete.size() > 0)
		{
			wclear(window);
			this->edit_mode = 2;
			this->temp_connections = connections_to_delete;
			this->temp_connection_counter = 0;
			this->current_file->set_connection_to_delete(connections_to_delete[0]);
			this->current_file->print_diagram(window);
			wrefresh(window);
		}
	}
}

void UMLTool::increment_temp_connections()
{
	this->temp_connection_counter = (this->temp_connection_counter + 1) % this->temp_connections.size();
}