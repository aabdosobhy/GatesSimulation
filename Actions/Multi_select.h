#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
#include<vector>
class Multi_select :
	public Action
{
	int Cx, Cy;
	vector<int> iddones;
public:
	Multi_select(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	virtual ~Multi_select();
};

