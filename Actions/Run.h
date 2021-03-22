#pragma once
#include "Action.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\Switch.h"

class Run :
	public Action
{
public:
	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	Run(ApplicationManager *pApp);
	~Run();
};

