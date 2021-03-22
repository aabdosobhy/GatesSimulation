#include "Unselect.h"





Unselect::Unselect(ApplicationManager * pApp) : Action(pApp)
{
	id_done = 0;
}

void Unselect::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on gate or connection you want to unselect");
	pIn->getWindowPtr()->FlushMouseQueue();
	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	if (Cx % 15 > 7)
		Cx = Cx / 15 + 1;
	else
		Cx = Cx / 15;


	if (Cy % 15 > 7)
		Cy = Cy / 15 + 1;
	else
		Cy = Cy / 15;

}

void Unselect::Execute()
{

	ReadActionParameters();
	if (pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy)) != NULL)
	{
		pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->change_to_UnHI();
		setid_done(pManager->getComponentPosition(Cx, Cy));
		GraphicsInfo g;
		g = pManager->find_component_with_specific_id(id_done)->getgrahicsinfo();
		pManager->selected_components.clear();
	}
	if(id_done!=0)
	pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}

Unselect::~Unselect()
{
}
void Unselect::Undo()
{
	pManager->find_component_with_specific_id(id_done)->change_to_HI();
	GraphicsInfo g;
	g = pManager->find_component_with_specific_id(id_done)->getgrahicsinfo();
	if (ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'h'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'v'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'd')
	pManager->selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
}
void Unselect::Redo()
{
	pManager->find_component_with_specific_id(id_done)->change_to_UnHI();
	GraphicsInfo g;
	g = pManager->find_component_with_specific_id(id_done)->getgrahicsinfo();
	pManager->selected_components.clear();
}

int Unselect::getid_done()
{
	return id_done;
}

void Unselect::setid_done(int i)
{
	id_done = i;
}
