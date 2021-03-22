#include "changeSwitch.h"
#include "..\Components\Switch.h"


changeSwitch::changeSwitch(ApplicationManager *pApp) :Action(pApp)
{
}

void changeSwitch::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Click on the switch you want to change ... ");
	pIn->GetPointClicked(Cx, Cy);
	//component_id=pManager->getComponentPosition(Cx, Cy);

	if (Cx % 15 > 7)
		Cx = Cx / 15 + 1;
	else
		Cx = Cx / 15;


	if (Cy % 15 > 7)
		Cy = Cy / 15 + 1;
	else
		Cy = Cy / 15;




}

void changeSwitch::Execute()
{
	ReadActionParameters();
	if ((dynamic_cast<Switch*>(pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy][Cx].first))))
	{

		((Switch*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy][Cx].first))->change_status();

		pManager->run_for_simulation();

	}
	else
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMsg("You didn't click on a switch we will end the action");
	}

}

void changeSwitch::Undo()
{
}

void changeSwitch::Redo()
{
}


changeSwitch::~changeSwitch()
{
}