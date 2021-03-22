#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

class select_area :
	public Action
{
	GraphicsInfo GInfo;
public:
	select_area(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	
	virtual ~select_area();
};

