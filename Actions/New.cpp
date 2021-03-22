#include "New.h"



New::New(ApplicationManager *pApp) : Action(pApp)
{
	
}

void  New::ReadActionParameters()
{

}

void  New::Execute()
{
	//Emptying the stacks of Actions and REDO actions
	while (!pManager->actualActions.empty()) pManager->actualActions.pop();
	while (!pManager->redoActions.empty()) pManager->redoActions.pop();
	//Filling the matrix as a new sheet
	pManager->fillmatrix();
	//Deleting component list
	pManager->DeleteCompList();


}

void  New::Undo()
{
}

void  New::Redo()
{
}



New::~New()
{
}
