#pragma once
#include"Action.h"
#include"..\ApplicationManager.h"
class New:
public Action
{

public:
	New(ApplicationManager*);
	virtual ~New();

	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

