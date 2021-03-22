#pragma once
#include"Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class create_truthtable :
	public Action
{
	//image truthtable; //msh m7tagaha lano kl mra hyd5l ykryt truth table gded 7ta lw hwa hwa hy3mlo tany
	//image simulation; //shayla screen shoot ll gates wl connections fe al simiulation
public:
	create_truthtable(ApplicationManager *pApp);
	virtual ~create_truthtable();
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	void OFile(int ** , int **, string * , string *);

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

