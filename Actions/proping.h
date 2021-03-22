#pragma once
#include"Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class proping :
	public Action
{

	int Cx, Cy;

public:
	proping(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

	virtual ~proping();
};

