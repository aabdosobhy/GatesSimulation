#include "Save.h"



Save::Save(ApplicationManager *pApp):Action(pApp)
{
}

void Save:: Execute()
{
	pManager->save();
	while (!pManager->actualActions.empty()) pManager->actualActions.pop();
	while(!pManager->redoActions.empty()) pManager->redoActions.pop();
}

void Save::Undo()
{
}

void Save::Redo()
{
}

Save::~Save()
{
}

void Save::ReadActionParameters()
{
}
