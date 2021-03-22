#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"

class Move :
	public Action
{
	int Cx, Cy, actualcomponent;
	vector<pair<pair<int, int>, pair<int, int>>> oldandnew;

	vector <Component * > selectedcomp;
	int xold, yold, xnew, ynew;
	// two arrays for connection b2a lma n3ml 2l fan zft dh (~_~) 
public:
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	void delete_gate_conection_from_bath_matrix(Component * temp);


	void draw_new_connection_for_gate(Component * temp, int index);

	virtual void Undo();
	virtual void Redo();
	Move(ApplicationManager *pApp);
	~Move();

};

