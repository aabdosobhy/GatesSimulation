#include "cut_copy.h"



cut_copy::cut_copy(ApplicationManager *pApp) :Action(pApp)
{
	choose = "";
}


cut_copy::~cut_copy()
{
}

void cut_copy::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on gate you want to excute the action relative to ");
	pIn->getWindowPtr()->FlushMouseQueue();
	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);
	if (Cx % 15 > 7)
		Cx = Cx / 15 + 1;
	else
		Cx = Cx / 15;


	if (Cy % 15 > 7)
		Cy = Cy / 15 + 1;
	else
		Cy = Cy / 15;

	while (pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy)) == NULL || pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getHI() == false)
	{
		pOut->PrintMsg("this area is empty click on gate or this gate is not highlited");
		pIn->getWindowPtr()->FlushMouseQueue();
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);
		if (Cx % 15 > 7)
			Cx = Cx / 15 + 1;
		else
			Cx = Cx / 15;


		if (Cy % 15 > 7)
			Cy = Cy / 15 + 1;
		else
			Cy = Cy / 15;

	}



	GraphicsInfo g;
	g = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getgrahicsinfo();
	xold = g.x1;
	yold = g.y1;
	for (int i = 0; i < pManager->selected_components.size(); i++)
	{
		pManager->selected_components[i].second.first = g.x1 - pManager->selected_components[i].first.first;
		pManager->selected_components[i].second.second = g.y1 - pManager->selected_components[i].first.second;
	}
	pOut->PrintMsg("choose the place you want to paste in");

	pIn->getWindowPtr()->FlushMouseQueue();
	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);
	if (Cx % 15 > 7)
		Cx = Cx / 15 + 1;
	else
		Cx = Cx / 15;


	if (Cy % 15 > 7)
		Cy = Cy / 15 + 1;
	else
		Cy = Cy / 15;
	bool returned = true;
	while (returned)
	{
		returned = false;
		//while (!pManager->find_component_with_specific_id(pManager->check_matrix(Cx * 15, Cy * 15)))

		while (!pManager->check_matrix(Cx * 15, Cy * 15))
		{

			pOut->PrintMsg("this area is not empty choose another place");
			pIn->getWindowPtr()->FlushMouseQueue();
			//Wait for User Input
			pIn->GetPointClicked(Cx, Cy);
			if (Cx % 15 > 7)
				Cx = Cx / 15 + 1;
			else
				Cx = Cx / 15;


			if (Cy % 15 > 7)
				Cy = Cy / 15 + 1;
			else
				Cy = Cy / 15;


		}
		xnew = Cx * 15 - 25;
		ynew = Cy * 15 - 25;
		for (int i = 0; i < pManager->selected_components.size(); i++)
		{
			pManager->selected_components[i].first.first = xnew - pManager->selected_components[i].second.first;
			pManager->selected_components[i].first.second = ynew - pManager->selected_components[i].second.second;
		//	(pManager->getComponentPosition()!=0)
			if (pManager->check_matrix(pManager->selected_components[i].first.first+25 , pManager->selected_components[i].first.second+25 ) ==false)
				returned = true;
		}
		if (returned)
		{
			pOut->PrintMsg("this area is not empty choose another place");
			pIn->getWindowPtr()->FlushMouseQueue();
			//Wait for User Input
			pIn->GetPointClicked(Cx, Cy);
			if (Cx % 15 > 7)
				Cx = Cx / 15 + 1;
			else
				Cx = Cx / 15;


			if (Cy % 15 > 7)
				Cy = Cy / 15 + 1;
			else
				Cy = Cy / 15;

		}

	}

}

void cut_copy::Execute()
{
	if (pManager->selected_components.size() == 0)
		return;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("click A to copy or ESCAPE to cut");
	char n;
	keytype key = NO_KEYPRESS;
	pIn->getWindowPtr()->FlushKeyQueue();     //HEBA TA3DEEEL
	key = pIn->getWindowPtr()->WaitKeyPress(n);
	if (key == ASCII)
	{
		choose = "copy";
		ReadActionParameters();
		pManager->copy_selected_components(xold, yold, iddones1, iddones2);
		for (int i = 0; i < pManager->selected_components.size(); i++)
		{
			pManager->selected_components[i].first.first = xold - (xnew - pManager->selected_components[i].first.first);
			pManager->selected_components[i].first.second = yold - (ynew - pManager->selected_components[i].first.second);
			pManager->selected_components[i].second.first = 0;
			pManager->selected_components[i].second.second = 0;
		}

	}
	else
	{
		choose = "cut";
		ReadActionParameters();
		pManager->setcleaned(false);  //lazm hyms7 7aga 3mltha hna 3shan al lazy delete bta3t al connection gwa al connection nfsha wmfeesh point 3la Appmang
		pManager->cut_selected_components(xold, yold, iddones1, iddones2);
		pManager->selected_components.clear();
		pManager->change_copy_unhi(iddones2);
	}

	pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}

void cut_copy::Undo()
{
	if (choose != "")
	{
		if (choose == "copy")
		{
			pManager->uncopy_cut_components(iddones2);
		}
		else if (choose == "cut")
		{
			pManager->uncopy_cut_components(iddones2);
			pManager->Readd_selected_components(iddones1);
		}
	}
}

void cut_copy::Redo()
{
	if (choose != "")
	{
		if (choose == "copy")
		{
			pManager->Readd_selected_components(iddones2);
			pManager->change_copy_unhi(iddones2);

		}
		else if (choose == "cut")
		{
			pManager->Readd_selected_components(iddones2);
			pManager->uncopy_cut_components(iddones1);
		}
	}
}
