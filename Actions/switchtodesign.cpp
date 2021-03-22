#include "switchtodesign.h"


switchtodesign::switchtodesign(ApplicationManager *pApp) :Action(pApp)
{
}


switchtodesign::~switchtodesign()
{
}

void switchtodesign::ReadActionParameters()
{

}
//Execute action (code depends on action type)
void switchtodesign::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->Cleartoolbar();
	pOut->CreateDesignToolBar();
	pManager->switch_design();
}

void switchtodesign::Undo()
{

}
void switchtodesign::Redo()
{

}