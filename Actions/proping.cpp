#include "proping.h"
#include"..\Components\Connection.h"

proping::proping(ApplicationManager *pApp) :Action(pApp)
{
}

void proping::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Click on the connection you want to prob.. ");
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

void proping::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if ((dynamic_cast<Connection*>(pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy][Cx].first))))
	{
		if (((Connection*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy][Cx].first))->getSourcePin()->getStatus() == HIGH)
			pOut->PrintMsg("1");
		else

			pOut->PrintMsg("0");
	}
	else
	{

		pOut->PrintMsg("You didn't click on a connection we will end the action");
	}
}

void proping::Undo()
{
}

void proping::Redo()
{
}


proping::~proping()
{
}
