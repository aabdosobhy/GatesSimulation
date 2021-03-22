#include "undo.h"

#include "..\ApplicationManager.h"

undo::undo(ApplicationManager *pApp) :Action(pApp)
{
}

void undo::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("user want to undo the action");

}

void undo::Execute()
{
	ReadActionParameters();
if(!pManager->actualActions.empty())
{
	pManager->actualActions.top()->Undo();
	pManager->redoActions.push(pManager->actualActions.top());
	pManager->actualActions.pop();
}

}


void undo::Undo()
{
}

void undo::Redo()
{
}

undo::~undo()
{
}
