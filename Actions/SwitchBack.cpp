#include "SwitchBack.h"


SwitchBack::SwitchBack(ApplicationManager *pApp) :Action(pApp)
{
}


SwitchBack::~SwitchBack()
{
}

void SwitchBack::ReadActionParameters()
{

}
//Execute action (code depends on action type)
void SwitchBack::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->Cleartoolbar();
	pOut->CreateDesignToolBar();

}

void SwitchBack::Undo()
{

}
void SwitchBack::Redo()
{

}