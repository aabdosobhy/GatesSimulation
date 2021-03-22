#pragma once
#include"Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class exIt :
	public Action
{
public:
	exIt(ApplicationManager *pApp);
	virtual ~exIt();
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

