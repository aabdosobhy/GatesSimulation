
#include "..\ApplicationManager.h"
#include<string>
#include<iostream>
using namespace std;
#include "Edit_label.h"

Edit_label::Edit_label(ApplicationManager *pApp) :Action(pApp)
{
	id_done = 0;
}
void Edit_label::ReadActionParameters() {
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on gate or connection you want to edit its label ");

	//Wait for User Input
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
	
	if (ApplicationManager::screenMatrix[Cy][Cx].second == "empty")
	{
		pOut->PrintMsg("You didn't click on gate or connection so we will end the action");
		can_edit = false;
		return;
	}

	pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy][Cx].first)->change_to_HI();
	pManager->UpdateInterface();
	
	pOut->PrintMsg("Write the label less than or equal 5 for gates and 2 for connections");
	label = pIn->GetSrting(pOut);
	if (label.length() > 5)
		label = label.substr(0, 5);
	if(ApplicationManager::screenMatrix[Cy][Cx].second[0]=='c'&&ApplicationManager::screenMatrix[Cy][Cx].second[1] != '_'&&label.length()>2)
		label = label.substr(0, 2);


	//Clear Status Bar
	pOut->ClearStatusBar();

}
//Execute action (code depends on action type)
void Edit_label::Execute() {
	can_edit = true;
	ReadActionParameters();
	if (can_edit == false)
		return;
	Component* pp = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy));

	if (pp != NULL)
	{
		id_done = pManager->getComponentPosition(Cx, Cy);
		last_label = pp->getlabel();
		pp->edit_label(label);
	}
	if (id_done != 0)
	{
		pManager->actualActions.push(this);
		
	}
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}


void Edit_label::Undo() {
	Component* p = pManager->find_component_with_specific_id(id_done);
	if (p != NULL)
	{
		p->edit_label(last_label);
	}

}
void Edit_label::Redo() {

	Component* p = pManager->find_component_with_specific_id(id_done);
	if (p != NULL)
	{
		p->edit_label(label);
	}
}


Edit_label::~Edit_label(void)
{
}
