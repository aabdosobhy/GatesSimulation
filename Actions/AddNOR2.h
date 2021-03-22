#pragma once
#ifndef _ADD_NOR2_GATE_H
#define _ADD_NOR2_GATE_H
#include "..\Actions\Action.h"
#include "..\Components\NOR2.h"
class AddNOR2 :
	public Action
{//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	int id_done;

public:
	AddNOR2(ApplicationManager *pApp);
	virtual ~AddNOR2(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif
