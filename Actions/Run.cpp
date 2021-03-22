#include "Run.h"



void Run::ReadActionParameters()
{
}

void Run::Execute()
{

	pManager->run_for_simulation();

}

void Run::Undo()
{
}

void Run::Redo()
{
}

Run::Run(ApplicationManager *pApp) : Action(pApp)
{
}


Run::~Run()
{
}
