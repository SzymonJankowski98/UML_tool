#include "MceditBackend.h"
#include "UMLTool.h"


int main()
{
	UMLTool *tool = new UMLTool();
	BaseBackend *backend = new MceditBackend(tool);

	backend->bind(".File.Open${Enter file name:|file_name}", [&tool]() { tool->open(); }, "Open file");
	backend->bind(".File.New", [&tool]() { tool->new_diagram(); }, "Create new diagram");
	backend->bind(".File.Save", [&tool]() { tool->save(); }, "Save file");
	backend->bind(".File.Save As${Enter n:|file_name}", [&tool]() { tool->save_as(); }, "Save file as");
	backend->bind(".Modes.Move Diagram", [&tool]() { tool->move_diagram(); }, "Move diagram mode");
	backend->bind(".Modes.Move Node", [&tool]() { tool->move_node(); }, "Move node mode");
	backend->bind(".Edit.Change Label${Enter new label:|label}", [&tool]() { tool->change_label(); }, "Change node label");
	backend->bind(".Edit.Delete Element", [&tool]() { tool->delete_block(); }, "Delete element");
	backend->bind(".Edit.Add Connection", [&tool]() { tool->add_connection_mode(); }, "Add connection");
	backend->bind(".Edit.Delete Connection", [&tool]() { tool->delete_connection_mode(); }, "Delete connection");
	backend->bind(".Add Element.Add Start Block", [&tool]() { tool->add_start_block(); }, "Add start block");
	backend->bind(".Add Element.Add Finish Block", [&tool]() { tool->add_finish_block(); }, "Add finish block");
	backend->bind(".Add Element.Add Decision Block", [&tool]() { tool->add_decision_block(); }, "Add decision block");
	backend->bind(".Add Element.Add Action Block", [&tool]() { tool->add_action_block(); }, "Add action block");
	backend->bind("#mcedit#<EDITION>", [&tool]() { tool->edition(); }, "");
	backend->start();
	delete backend;
	delete tool;
}