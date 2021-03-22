#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class cut_copy :
	public Action
{
	int Cx, Cy;
	int xold, yold, xnew, ynew;
	string choose;   //copy or cut 
	vector<int> iddones1;
	vector<int> iddones2;
public:
	cut_copy(ApplicationManager *pApp);
	virtual ~cut_copy();
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
