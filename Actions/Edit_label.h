
#pragma once

#include"Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class Edit_label :
	public Action
{
	//int component_id;
	int Cx, Cy;	//click on the gate or connection to edit label
	string label;
	string last_label;
	int id_done;
	bool can_edit;
public:
	Edit_label(ApplicationManager *pApp);
	virtual ~Edit_label();
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

