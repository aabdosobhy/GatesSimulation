#pragma once
#include"Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
#include<vector>
class Delete :
	public Action
{
	int Cx, Cy;
	vector<int> iddones;
public:
	Delete(ApplicationManager *pApp);
	virtual ~Delete();

	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute() ;

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

};

