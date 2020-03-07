#include "UML_Diagram.h"

UML_Diagram::UML_Diagram(int size) : size(size), picked_node(0), shift_x(0), shift_y(0), connection_to_add(-1), connection_to_delete(-1)
{
	this->init_colors();
}

UML_Diagram::UML_Diagram(tinyxml2::XMLDocument* xmlDoc, int size): size(size), picked_node(0), shift_x(0), shift_y(0), connection_to_add(-1), connection_to_delete(-1)
{
	this->init_colors();
	tinyxml2::XMLNode* elements = (*xmlDoc).FirstChild();
	if (elements == nullptr) return;

	tinyxml2::XMLElement* element = elements->FirstChildElement("element");
	
	int i = 0;
	while (element != nullptr)
	{
		int x, y;
		element->FirstChildElement("x")->QueryIntText(&x);
		element->FirstChildElement("y")->QueryIntText(&y);
		std::string type = element->Attribute("type");
		if (type == "Start")
		{	
			StartBlock* block = new StartBlock(this->size, x, y);
			tinyxml2::XMLElement* connection = element->FirstChildElement("connections")->FirstChildElement("id");
			int value;
			while (connection != nullptr)
			{
				connection->QueryIntText(&value);
				block->add_connection(value);
				connection = connection->NextSiblingElement("id");
			}
			this->diagram.push_back(block);
		}
		else if (type == "ActionBlock")
		{
			tinyxml2::XMLElement* label = element->FirstChildElement("label");
			ActionBlock* block = new ActionBlock(this->size, label->GetText(), x, y);
			tinyxml2::XMLElement* connection = element->FirstChildElement("connections")->FirstChildElement("id");
			int value;
			while (connection != nullptr)
			{
				connection->QueryIntText(&value);
				block->add_connection(value);
				connection = connection->NextSiblingElement("id");
			}
			this->diagram.push_back(block);
		}
		else if (type == "DecisionBlock")
		{
			tinyxml2::XMLElement* label = element->FirstChildElement("label");
			int true_value, false_value;
			DecisionBlock* block = new DecisionBlock(this->size, label->GetText(), x, y);
			tinyxml2::XMLElement* true_con = element->FirstChildElement("true");
			tinyxml2::XMLElement* false_con = element->FirstChildElement("false");
			true_con->QueryIntText(&true_value);
			false_con->QueryIntText(&false_value);
			block->set_true(true_value);
			block->set_false(false_value);
			this->diagram.push_back(block);
		}
		else if (type == "Finish")
		{
			Block* block = new FinishBlock(this->size, x, y);
			this->diagram.push_back(block);
		}
		element = element->NextSiblingElement("element");
		i++;
	}
}

void UML_Diagram::init_colors()
{
	init_pair(100, COLOR_WHITE, COLOR_BLACK);
	init_pair(101, COLOR_RED, COLOR_BLACK);
	init_pair(102, COLOR_BLUE, COLOR_BLACK);
	init_pair(103, COLOR_GREEN, COLOR_BLACK);
	init_pair(104, COLOR_YELLOW, COLOR_BLACK);
}

bool UML_Diagram::add_start_block() 
{
	for (int i = 0; i < this->diagram.size(); i++)
	{
		if (dynamic_cast<StartBlock*>(this->diagram[i]) != nullptr)
		{
			return false;
		}
	}
	this->diagram.push_back(new StartBlock(this->size, 1, 1));
	this->picked_node = diagram.size() - 1;
	return true;
}

bool UML_Diagram::add_finish_block()
{
	for (int i = 0; i < this->diagram.size(); i++)
	{
		if (dynamic_cast<FinishBlock*>(this->diagram[i]) != nullptr)
		{
			return false;
		}
	}
	this->diagram.push_back(new FinishBlock(this->size, 1, 1));
	this->picked_node = diagram.size() - 1;
	return true;
}

void UML_Diagram::add_decision_block()
{
	this->diagram.push_back(new DecisionBlock(this->size, "label", 1, 1));
	this->picked_node = diagram.size() - 1;
}

void UML_Diagram::add_action_block()
{
	this->diagram.push_back(new ActionBlock(this->size, "label", 1, 1));
	this->picked_node = diagram.size() - 1;
}

void UML_Diagram::print_diagram(WINDOW* win)
{
	for (int i = 0; i < this->diagram.size(); i++)
	{
		int x = this->diagram[i]->getX();
		int y = this->diagram[i]->getY();

		if (i == this->picked_node)
		{
			this->diagram[i]->print(win, 104, shift_x, shift_y);
		}
		else if (i == this->connection_to_add)
		{
			this->diagram[i]->print(win, 103, shift_x, shift_y);
		}
		else if (i == this->connection_to_delete)
		{
			this->diagram[i]->print(win, 101, shift_x, shift_y);
		}
		else
		{
			this->diagram[i]->print(win, 100, shift_x, shift_y);
		}

		if (dynamic_cast<FinishBlock*>(this->diagram[i]) != nullptr)
		{

		}
		else if (dynamic_cast<DecisionBlock*>(this->diagram[i]) != nullptr)
		{
			int true_con = (dynamic_cast<DecisionBlock*>(this->diagram[i]))->get_true();
			int false_con = (dynamic_cast<DecisionBlock*>(this->diagram[i]))->get_false();
			if (true_con != -1)
			{
				this->print_connection(win, x, y, this->diagram[true_con]->getX(), this->diagram[true_con]->getY());
			}
			if (false_con != -1)
			{
				this->print_false_connection(win, x, y, this->diagram[false_con]->getX(), this->diagram[false_con]->getY());
			}
		}
		else
		{
			std::vector<int> connections = (dynamic_cast<ActionBlock*>(this->diagram[i]))->get_connections();
			for (int j = 0; j < connections.size(); j++)
			{
				this->print_connection(win, x, y, this->diagram[connections[j]]->getX(), this->diagram[connections[j]]->getY());
			}
		}
	}
}

void UML_Diagram::print_connection(WINDOW* win, int x1, int y1, int x2, int y2)
{
	int start_x = x1 + this->size;
	int start_y = y1 + this->size;
	int end_x = x2 - 1;
	int end_y = y2 + this->size;
	if (end_x - start_x >= 0)
	{
		if (end_y - start_y > 0)
		{
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_LLCORNER, 1);
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y + 1, ACS_HLINE, end_y - start_y);
			mvwvline(win, this->shift_x + start_x, this->shift_y + end_y, ACS_URCORNER, 1);
			mvwvline(win, this->shift_x + start_x + 1, this->shift_y + end_y, ACS_VLINE, end_x - start_x);
		}
		else if(end_y - start_y == 0)
		{
			mvwvline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_VLINE, end_x - start_x + 1);
		}
		else
		{
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_LRCORNER, 1);
			mvwhline(win, this->shift_x + start_x, this->shift_y + end_y, ACS_HLINE, start_y - end_y);
			mvwvline(win, this->shift_x + start_x, this->shift_y + end_y, ACS_ULCORNER, 1);
			mvwvline(win, this->shift_x + start_x + 1, this->shift_y + end_y, ACS_VLINE, end_x - start_x);
		}
	}
	else
	{
		if (end_y - start_y > 0)
		{
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_LLCORNER, 1);
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y + 1, ACS_HLINE, end_y - start_y - this->size - 2);
			mvwhline(win, this->shift_x + start_x, this->shift_y + end_y - this->size - 1, ACS_LRCORNER, 1);
			mvwvline(win, this->shift_x + end_x + 1, this->shift_y + end_y - this->size - 1, ACS_VLINE, start_x - end_x - 1);
			mvwvline(win, this->shift_x + end_x, this->shift_y + end_y - this->size - 1, ACS_ULCORNER, 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y - this->size, ACS_HLINE, this->size);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y, ACS_URCORNER, 1);
		}
		else
		{
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_LRCORNER, 1);
			mvwhline(win, this->shift_x + start_x, this->shift_y + end_y + this->size + 1, ACS_HLINE, start_y - end_y - this->size - 1);
			mvwhline(win, this->shift_x + start_x, this->shift_y + end_y + this->size, ACS_LLCORNER, 1);
			mvwvline(win, this->shift_x + end_x + 1, this->shift_y + end_y + this->size, ACS_VLINE, start_x - end_x - 1);
			mvwvline(win, this->shift_x + end_x, this->shift_y + end_y + this->size, ACS_URCORNER, 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y, ACS_HLINE, this->size);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y, ACS_ULCORNER, 1);
		}
	}
}

void UML_Diagram::print_false_connection(WINDOW* win, int x1, int y1, int x2, int y2)
{
	int start_x = x1 + this->size / 2;
	int start_y = y1 + this->size;
	int end_x = x2 - 1;
	int end_y = y2 + this->size;
	if (end_x - start_x >= 0)
	{
		if (end_y - start_y > 0)
		{
			start_y += this->size + 1;
			mvwvline(win, this->shift_x + end_x, this->shift_y + start_y, ACS_VLINE, end_y - start_y);
			mvwvline(win, this->shift_x + start_x, this->shift_y + end_y, ACS_URCORNER, 1);
			mvwvline(win, this->shift_x + start_x + 1, this->shift_y + end_y, ACS_VLINE, end_x - start_x);
		}
		else
		{
			start_y -= this->size;
			mvwhline(win, this->shift_x + start_x, this->shift_y + end_y, ACS_HLINE, start_y - end_y);
			mvwvline(win, this->shift_x + start_x, this->shift_y + end_y, ACS_ULCORNER, 1);
			mvwvline(win, this->shift_x + start_x + 1, this->shift_y + end_y, ACS_VLINE, end_x - start_x);
		}
	}
	else
	{
		if (end_y - start_y > 0)
		{
			start_y -= this->size + 1;
			mvwvline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_LLCORNER, 1);
			mvwvline(win, this->shift_x + end_x + 1, this->shift_y + start_y, ACS_VLINE, start_x - end_x - 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + start_y, ACS_ULCORNER, 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + start_y + 1, ACS_HLINE, end_y - start_y - 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y, ACS_URCORNER, 1);
		}
		else
		{
			start_y += this->size;
			mvwhline(win, this->shift_x + start_x, this->shift_y + start_y, ACS_LRCORNER, 1);
			mvwvline(win, this->shift_x + end_x + 1, this->shift_y + start_y, ACS_VLINE, start_x - end_x - 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + start_y, ACS_URCORNER, 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y + 1, ACS_HLINE, start_y - end_y - 1);
			mvwhline(win, this->shift_x + end_x, this->shift_y + end_y, ACS_ULCORNER, 1);
		}
	}
}

void UML_Diagram::move_picked_node_X(int val)
{
	this->diagram[this->picked_node]->moveX(val);
}

void UML_Diagram::move_picked_node_Y(int val)
{
	this->diagram[this->picked_node]->moveY(val);
}

void UML_Diagram::next_node()
{
	this->picked_node = (this->picked_node + 1) % this->diagram.size();
}

void UML_Diagram::change_label(std::string label)
{
	this->diagram[this->picked_node]->change_label(label);
}

void UML_Diagram::delete_element()
{
	this->repair_diagram();
	this->diagram.erase(this->diagram.begin() + this->picked_node);
	this->picked_node = 0;
}

void UML_Diagram::repair_diagram()
{
	for (int i = 0; i < this->diagram.size(); i++)
	{
		if (dynamic_cast<DecisionBlock*>(this->diagram[i]) != nullptr)
		{
			int true_con = (dynamic_cast<DecisionBlock*>(this->diagram[i]))->get_true();
			int false_con = (dynamic_cast<DecisionBlock*>(this->diagram[i]))->get_false();
			if (true_con <= this->picked_node && true_con > -1)
			{
				if (true_con == this->picked_node)
				{
					(dynamic_cast<DecisionBlock*>(this->diagram[i]))->set_true(-1);
				}
				else
				{
					(dynamic_cast<DecisionBlock*>(this->diagram[i]))->set_true(true_con - 1);
				}
			}
			if (false_con >= this->picked_node && false_con > -1)
			{
				if (false_con == this->picked_node)
				{
					(dynamic_cast<DecisionBlock*>(this->diagram[i]))->set_false(-1);
				}
				else
				{
					(dynamic_cast<DecisionBlock*>(this->diagram[i]))->set_false(false_con - 1);
				}
			}
		}
		else if (dynamic_cast<FinishBlock*>(this->diagram[i]) == nullptr)
		{
			std::vector<int> connections = (dynamic_cast<ActionBlock*>(this->diagram[i]))->get_connections();
			for (int j = connections.size() - 1; j >= 0; j--)
			{
				if (connections[j] >= this->picked_node)
				{
					if (connections[j] == this->picked_node)
					{
						(dynamic_cast<ActionBlock*>(this->diagram[i]))->delete_connection_index(j);
					}
					else
					{
						(dynamic_cast<ActionBlock*>(this->diagram[i]))->delete_connection_index(j);
						(dynamic_cast<ActionBlock*>(this->diagram[i]))->add_connection(connections[j] - 1);
					}
				}
			}
		}
	}
}

void UML_Diagram::move_window_up()
{
	this->shift_x -= 1;
}

void UML_Diagram::move_window_down()
{
	this->shift_x += 1;
}

void UML_Diagram::move_window_right()
{
	this->shift_y += 1;
}

void UML_Diagram::move_window_left()
{
	this->shift_y -= 1;
}

void UML_Diagram::set_connection_to_add(int value)
{
	this->connection_to_add = value;
}

void UML_Diagram::set_connection_to_delete(int value)
{
	this->connection_to_delete = value;
}

std::vector<int> UML_Diagram::possible_connections()
{
	std::vector<int> possible_connections(this->diagram.size());
	std::iota(std::begin(possible_connections), std::end(possible_connections), 0);
	possible_connections.erase(std::remove(possible_connections.begin(), possible_connections.end(), this->picked_node), possible_connections.end());

	if (dynamic_cast<FinishBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		return std::vector<int>();
	}
	else if (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		int true_con = (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]))->get_true();
		int false_con = (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]))->get_false();

		if (true_con >= 0)
		{
			possible_connections.erase(std::remove(possible_connections.begin(), possible_connections.end(), true_con), possible_connections.end());
		}

		if (false_con >= 0)
		{
			possible_connections.erase(std::remove(possible_connections.begin(), possible_connections.end(), false_con), possible_connections.end());
		}
	}
	else
	{
		std::vector<int> connections = (dynamic_cast<ActionBlock*>(this->diagram[this->picked_node]))->get_connections();
		for (int j = 0;  j < connections.size(); j++)
		{
			possible_connections.erase(std::remove(possible_connections.begin(), possible_connections.end(), connections[j]), possible_connections.end());
		}
	}

	for (int i = 0; i < this->diagram.size(); i++)
	{
		if (dynamic_cast<StartBlock*>(this->diagram[i]) != nullptr)
		{
			possible_connections.erase(std::remove(possible_connections.begin(), possible_connections.end(), i), possible_connections.end());
		}
	}

	return possible_connections;
}

void UML_Diagram::add_connection()
{
	if (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node])->set_true(this->connection_to_add);
		this->connection_to_add = -1;
	}
	else if (dynamic_cast<FinishBlock*>(this->diagram[picked_node]) == nullptr)
	{
		dynamic_cast<ActionBlock*>(this->diagram[this->picked_node])->add_connection(this->connection_to_add);
		this->connection_to_add = -1;
	}
}

bool UML_Diagram::add_false_connection()
{
	
	if (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node])->set_false(this->connection_to_add);
		this->connection_to_add = -1;
		return true;
	}
	return false;
}
void UML_Diagram::delete_connection()
{
	if (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		if (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node])->get_true() == this->connection_to_delete)
		{
			dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node])->set_true(-1);
		}
		else
		{
			dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node])->set_false(-1);
		}
		this->connection_to_delete = -1;
	}
	else if (dynamic_cast<FinishBlock*>(this->diagram[picked_node]) == nullptr)
	{
		dynamic_cast<ActionBlock*>(this->diagram[this->picked_node])->delete_connection(this->connection_to_delete);
		this->connection_to_delete = -1;
	}
}

std::vector<int> UML_Diagram::connections_to_delete()
{
	std::vector<int> connections_to_delete;

	if (dynamic_cast<FinishBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		return std::vector<int>();
	}
	else if (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]) != nullptr)
	{
		int true_con = (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]))->get_true();
		int false_con = (dynamic_cast<DecisionBlock*>(this->diagram[this->picked_node]))->get_false();
		connections_to_delete.push_back(true_con);
		connections_to_delete.push_back(false_con);
	}
	else
	{
		connections_to_delete = dynamic_cast<ActionBlock*>(this->diagram[this->picked_node])->get_connections();
	}
	return connections_to_delete;
}

std::string UML_Diagram::generate_string()
{
	std::string result = "<schema>\n";
	for (int i = 0; i < this->diagram.size(); i++)
	{
		result += this->diagram[i]->get_as_string();
	}
	result.append("</schema>\n");

	return result;
}