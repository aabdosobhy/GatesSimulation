#pragma once
#include"Action.h"
#include"..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class AddGate :
	public Action
{
public:
	AddGate(ApplicationManager *pApp);
	virtual ~AddGate();
	
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

