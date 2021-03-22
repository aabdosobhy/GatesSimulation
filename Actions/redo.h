#pragma once
#include"Action.h"
class redo :
	public Action
{
public:
	redo(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual ~redo();
};

