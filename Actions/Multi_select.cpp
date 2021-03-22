#include "Multi_select.h"


Multi_select::Multi_select(ApplicationManager * pApp) :Action(pApp)
{
	
}

void Multi_select::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	//Print Action Message
	pOut->PrintMsg("Click on gate(s) or connection(s) you want to select. ");
	pIn->getWindowPtr()->FlushMouseQueue();        //HEBA TA3DEEEL WMA3MOL FE SELECT W UN SELECT
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

void Multi_select::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	char n;
	keytype key = NO_KEYPRESS;
	//	pIn->getWindowPtr()->GetKeyPress(n);
	ReadActionParameters();
	pManager->change_ALL_to_UnHI();
	pManager->selected_components.clear();
	if (pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy)) != NULL)
	{
		pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->change_to_HI();
		iddones.push_back(pManager->getComponentPosition(Cx, Cy));
		GraphicsInfo g;
		g = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getgrahicsinfo();
		if (ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'h'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'v'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'd')
		pManager->selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
	}
	else
	{
		pManager->change_ALL_to_UnHI();
		pManager->selected_components.clear();
	}
	pManager->UpdateInterface();      //????hl msmo7ly
	pOut->PrintMsg("Click A to continue or Enter to stop selecting");
	pIn->getWindowPtr()->FlushKeyQueue();     //HEBA TA3DEEEL
	key = pIn->getWindowPtr()->WaitKeyPress(n);
	while (key == ASCII&&n != 13)
	{

		ReadActionParameters();
		if (pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy)) != NULL)
		{
			pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->change_to_HI();
			iddones.push_back(pManager->getComponentPosition(Cx, Cy));
			GraphicsInfo g;
			g = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getgrahicsinfo();
			if (ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'h'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'v'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != 'd')
			pManager->selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
		}
		else
		{
			pManager->change_ALL_to_UnHI();
			pManager->selected_components.clear();
		}

		pManager->UpdateInterface();

		pOut->PrintMsg("Click A to continue or Enter to stop selecting");
		pIn->getWindowPtr()->FlushKeyQueue();     // HEBAAAAAAAAAAAAAAA T3DEL
		key = pIn->getWindowPtr()->WaitKeyPress(n);
	}
	if(iddones.size()!=0)
	{ 
		pManager->actualActions.push(this);
	}
	
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}

Multi_select::~Multi_select()
{
}

void Multi_select::Undo()
{
	for (int i = 0; i < iddones.size(); i++)
	{
		pManager->find_component_with_specific_id(iddones[i])->change_to_UnHI();
		pManager->UpdateInterface();
		pManager->selected_components.clear();

	}
}
void Multi_select::Redo()
{
	for (int i = 0; i < iddones.size(); i++)
	{
		pManager->find_component_with_specific_id(iddones[i])->change_to_HI();
		pManager->UpdateInterface();
		GraphicsInfo g;
		g = pManager->find_component_with_specific_id(iddones[i])->getgrahicsinfo();
		if(ApplicationManager::screenMatrix[g.y1/15][g.x1 / 15].second[1] != 'h'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'v'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] !=  'd')
		pManager->selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
		
	}

}