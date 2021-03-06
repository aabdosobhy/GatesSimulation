#pragma once

#include "action.h"
#include "..\Components\NAND2.h"
class AddNAND2 :
	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	int id_done;

public:
	AddNAND2(ApplicationManager *pApp);
	virtual ~AddNAND2(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

