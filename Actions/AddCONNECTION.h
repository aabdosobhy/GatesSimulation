#pragma once
#include "Action.h"
//#include "action.h"
#include "..\Components\Connection.h"

class Connection;

class AddCONNECTION :
	public Action
{
	int x1, y1, x2, y2;
	int id_done;
	bool can_draw;
public:
	vector<pair<int, int>> path_done;
	vector<pair<int, int>> subpath_done;
	AddCONNECTION(ApplicationManager *pApp);
	~AddCONNECTION();
	int getid_done()
	{
		return id_done;
	}
	void setid_done(int i)
	{
		id_done = i;
	}
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	Connection * loadconn(Connection * pA);
	virtual void Undo();
	virtual void Redo();

};

