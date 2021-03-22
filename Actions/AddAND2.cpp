#include "AddAND2.h"
#include "..\ApplicationManager.h"
#include <iostream>
#include <string>
AddAND2::AddAND2(ApplicationManager *pApp):Action(pApp)
{
}

AddAND2::~AddAND2(void)
{
}

void AddAND2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	// calculate the new coordinates "magnet"

	if (Cx % 15 > 7) Cx = Cx / 15 + 1;
	else Cx = Cx / 15 ;
		//(Cx % 15<= 7)Cx = Cx / 15 - 1;
if (Cy% 15 > 7) Cy = Cy / 15 + 1;
	else Cy = Cy / 15 ;
	//if(Cy % 15<= 7)Cy = Cy / 15 - 1;
	Cx *= 15; Cy *= 15;
	while (!pManager->check_matrix(Cx, Cy))
	{
		pOut->PrintMsg("This area is not empty choose another place"); ////hebaaaaa wrbna ystorrrr
		pIn->GetPointClicked(Cx, Cy);
		if (Cx % 15 > 7) Cx = Cx / 15 + 1;
		else Cx = Cx / 15;
		
		if (Cy % 15 > 7) Cy = Cy / 15 + 1;
		else Cy = Cy / 15;
		
		Cx *= 15; Cy *= 15;
	}//call fn elahsas
	
	//Clear Status Bar
	//pOut->ClearStatusBar();
	
}

void AddAND2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	AND2 *pA=new AND2(GInfo, AND2_FANOUT); 

	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());

	/*for (int i = 0; i < UI.height / 15 + 1; i++)
	{
		for (int j = 0; j <60; j++)
		{

			cout << ApplicationManager::screenMatrix[i][j].second;
			//ApplicationManager::screenMatrix[i][j].second = "empty";
		}
		cout << endl;
	}*/

	id_done = pA->getid();  //ta3deeeeeeeeeeeeeel
	//push action  into stack for undo and redo
	pManager->AddComponent(pA);
	pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}

void AddAND2::Undo()
{
	Output* pOut = pManager->GetOutput();
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	pManager->Lazy_DeleteComponent(id_done, GInfo);
	pOut->Clear_Gate_from_D_A(GInfo.x1, GInfo.y1);
}

void AddAND2::Redo()
{
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Component *pp = pManager->find_component_with_specific_id(id_done);
	pp->setlazy_d(false);
	pp->updateMatrix(GInfo, id_done, pp->gettype());
}


