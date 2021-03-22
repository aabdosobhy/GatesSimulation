#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
class switchtosim :
	public Action
{
	string error; //defines the error (if exists) when validating the circuit
public:
	switchtosim(ApplicationManager *pApp);
	virtual ~switchtosim();

	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

