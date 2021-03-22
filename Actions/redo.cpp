#include "redo.h"
#include "..\ApplicationManager.h"


redo::redo(ApplicationManager *pApp) : Action(pApp)
{
	//id_done = 0;
}

void redo::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("user want to redo the action");
}

void redo::Execute()
{
	ReadActionParameters();
	if (!pManager->redoActions.empty())
	{
		pManager->redoActions.top()->Redo();
		pManager->actualActions.push(pManager->redoActions.top());
		pManager->redoActions.pop();
	}

}

void redo::Undo()
{
}

void redo::Redo()
{
}


redo::~redo()
{
}
