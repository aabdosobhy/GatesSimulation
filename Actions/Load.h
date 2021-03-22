#pragma once
#include "Action.h"
#include"..\ApplicationManager.h"
#include<fstream>
#include<string>

#include"AddAND2.h"
#include "AddBuffer.h"
#include "AddINVERTER.h"
#include "AddOR2.h"
#include "AddNOR2.h"
#include "AddXNOR2.h" 
#include "AddXOR2.h"
#include "AddAND3.h"
#include "AddNOR3.h"
#include "AddXOR3.h"
#include "AddSWITCH.h"
#include "AddLED.h"
#include "AddNAND2.h"

class Load :
	public Action
{
	
public:
	Load(ApplicationManager *);
	~Load();
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();


};


