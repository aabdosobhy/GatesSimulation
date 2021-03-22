#include "Delete.h"



Delete::Delete(ApplicationManager *pApp) :Action(pApp)
{

}


Delete::~Delete()
{
}

void Delete::ReadActionParameters()
{
}

void Delete::Execute()
{
	pManager->Delete_selected_components(iddones);
	pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}

void Delete::Undo()
{
	pManager->Readd_selected_components(iddones);
}

void Delete::Redo()
{
	iddones.clear();
	pManager->Delete_selected_components(iddones);
}
