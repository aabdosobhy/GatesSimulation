#include "Load.h"



Load::Load(ApplicationManager *pApp) :Action(pApp)
{
}


Load::~Load()
{
}

void Load::ReadActionParameters()
{
}

void Load::Execute()
{
	pManager->load();
}

void Load::Undo()
{
}

void Load::Redo()
{
}
