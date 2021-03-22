#include "unselect_all.h"






unselect_all::unselect_all(ApplicationManager * pApp) : Action(pApp)

{
}

void unselect_all::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("An empty click on drawing area");
}

void unselect_all::Execute()
{
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	if (pManager->getComponentPosition(pIn->getsx(), pIn->getsy()) == 0)
		pManager->change_ALL_to_UnHI();
	pManager->selected_components.clear();
	/*pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}*/
}

unselect_all::~unselect_all()
{
}
void unselect_all::Undo()
{

}
void unselect_all::Redo()
{

}