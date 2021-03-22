#pragma once
#include "Action.h"
#include"..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class SwitchBack :
	public Action
{
public:
	SwitchBack(ApplicationManager *pApp);
	virtual ~SwitchBack();
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

