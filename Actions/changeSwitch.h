#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"

class changeSwitch :
	public Action
{
	int Cx, Cy;
public:
	changeSwitch(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	~changeSwitch();
};