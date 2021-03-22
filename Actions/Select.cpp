#include "Select.h"



Select::Select(ApplicationManager *pApp) :Action(pApp)
{
	id_done = 0;
}

void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on gate or connection you want to select");
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

void Select::Execute()
{
	ReadActionParameters();
	pManager->change_ALL_to_UnHI();
	pManager->selected_components.clear();
	if (pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy)) != NULL)
	{
		
		pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->change_to_HI();
		setid_done(pManager->getComponentPosition(Cx, Cy));
		GraphicsInfo g;
		g = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getgrahicsinfo();
		pair<pair<int, int>, pair<int, int>>emp;
		emp.first.first = g.x1;
		emp.first.second = g.y1;
		emp.second.first = 0;
		emp.second.second = 0;
		if(ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'h'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'v'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'd')
		pManager->selected_components.push_back(emp);

		//pManager->selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
	}
	else
	{
		pManager->change_ALL_to_UnHI();
		pManager->selected_components.clear();
	}


	if (id_done != 0)
	{
		pManager->actualActions.push(this);
		
	}
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}


Select::~Select()
{
	
}


void Select::Undo()
{
	
	pManager->find_component_with_specific_id(id_done)->change_to_UnHI();
	GraphicsInfo g;
	g=pManager->find_component_with_specific_id(id_done)->getgrahicsinfo();
	pManager->selected_components.clear();

}
void Select::Redo()
{
	GraphicsInfo g;
	pManager->find_component_with_specific_id(id_done)->change_to_HI();
	g = pManager->find_component_with_specific_id(id_done)->getgrahicsinfo();
	pair<pair<int, int>, pair<int, int>>emp;
	emp.first.first = g.x1;
	emp.first.second = g.y1;
	emp.second.first = 0;
	emp.second.second =0;
	if (ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'h'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'v'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'd')
	pManager->selected_components.push_back(emp);

	//pManager->selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));

}

int Select::getid_done()
{
	return id_done;
}

void Select::setid_done(int i)
{
	id_done = i;
}
