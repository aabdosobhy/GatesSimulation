#include "AddGate.h"


AddGate::AddGate(ApplicationManager *pApp) :Action(pApp)
{
}


AddGate::~AddGate()
{
}
void AddGate::ReadActionParameters()
{
	
}
//Execute action (code depends on action type)
void AddGate::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->Cleartoolbar();
	pOut->CreateAddToolBar();

}

void AddGate::Undo()
{

}
void AddGate::Redo()
{

}