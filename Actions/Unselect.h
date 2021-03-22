#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class Unselect :
	public Action
{
	int Cx, Cy; 
	int id_done;
	
public:
	Unselect(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	int getid_done();
	void setid_done(int i);


	virtual ~Unselect();
};

