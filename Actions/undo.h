#pragma once
#include"Action.h"
class undo :
	public Action
{
public:
	undo(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual ~undo();
};

