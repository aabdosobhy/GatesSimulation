#include "switchtosim.h"


switchtosim::switchtosim(ApplicationManager *pApp) :Action(pApp)
{
}


switchtosim::~switchtosim()
{
}
void switchtosim::ReadActionParameters()
{

}
//Execute action (code depends on action type)
void switchtosim::Execute()
{
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
	while (!pManager->actualActions.empty())
	{
		pManager->actualActions.pop();
	}
	pManager->cleaning();
	pManager->selected_components.clear();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	error = pManager->circuit_valid();
	if (error == "No Error")
	{
		pOut->Cleartoolbar();
		pOut->CreateSimulationToolBar();
		//image *I= ApplicationManager::CircSimag;
		//pOut->getpointerwind()->StoreImage(*I,0,UI.ToolBarHeight,UI.width,UI.height-UI.ToolBarHeight);
	}
	else if (error == "sequential")
	{
		pOut->PrintMsg("Sequential is forbidden.Check your circuit again");
	}
	else if (error == "empty pin")
	{
		pOut->PrintMsg("There is an empty pin.Check your circuit again");

	}
	else if (error == "No Switch")
	{
		pOut->PrintMsg("There is no Switches.Check your circuit again");

	}
	else if (error == "No LED")
	{
		pOut->PrintMsg("There is no Leds.Check your circuit again");

	}
	
	
}

void switchtosim::Undo()
{

}
void switchtosim::Redo()
{

}