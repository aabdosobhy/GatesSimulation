#pragma once
#include "Action.h"
#include "..\Components\Connection.h"

class Edit :
	public Action
{
	int x1, y1, x2, y2;
	int Cx, Cy;
	int id_done;
	bool can_draw;
public:
	Edit(ApplicationManager *pApp);
	virtual ~Edit();
	virtual void ReadActionParameters();
	void select_connection();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

