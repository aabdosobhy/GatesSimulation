#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class switchtodesign :
	public Action
{
public:
	switchtodesign(ApplicationManager *pApp);
	virtual ~switchtodesign();
	
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

