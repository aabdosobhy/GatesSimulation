#include "select_area.h"



select_area::select_area(ApplicationManager *pApp) :Action(pApp)
{
}

void select_area::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	//Print Action Message
	pOut->PrintMsg("Click to start selecting ...");

	pIn->getWindowPtr()->FlushMouseQueue();        //HEBA TA3DEEEL WMA3MOL FE SELECT W UN SELECT
												   //Wait for User Input
	pIn->GetPointClicked(GInfo.x1, GInfo.y1);


	if (GInfo.x1 % 15 > 7)
		GInfo.x1 = GInfo.x1 / 15 + 1;
	else
		GInfo.x1 = GInfo.x1 / 15;


	if (GInfo.y1 % 15 > 7)
		GInfo.y1 = GInfo.y1 / 15 + 1;
	else
		GInfo.y1 = GInfo.y1 / 15;
	pOut->PrintMsg("Press enter to stop selecting ");

	image screen, toolbar;

	pIn->getWindowPtr()->StoreImage(screen, 0, 0, UI.width, UI.height);
	pIn->getWindowPtr()->StoreImage(toolbar, 0, 0, UI.width, UI.ToolBarHeight);
	int x, y, xx, yy;
	pIn->getWindowPtr()->SetBuffering(true);
	bool t = true;
	char cKeyData;

	while (pIn->getWindowPtr()->GetKeyPress(cKeyData) != ASCII)
	{
		pIn->getWindowPtr()->GetMouseCoord(x, y);
		if (x % 15 > 7)
			xx = x / 15 + 1;
		else xx = x / 15;
		if (y % 15 > 7)
			yy = y / 15 + 1;
		else yy = y / 15;
		pIn->getWindowPtr()->DrawImage(screen, 0, 0, UI.width, UI.height);
		pIn->getWindowPtr()->SetPen(PURPLE, 3);
		pIn->getWindowPtr()->DrawRectangle(GInfo.x1 * 15, GInfo.y1 * 15, xx * 15, yy * 15, FRAME);
		pIn->getWindowPtr()->DrawImage(toolbar, 0, 0, UI.width, UI.ToolBarHeight);
		pOut->PrintMsg("Press enter to end selecting");

		pIn->getWindowPtr()->UpdateBuffer();




	}
	pIn->getWindowPtr()->FlushMouseQueue();
	pIn->getWindowPtr()->SetBuffering(false);
	pIn->getWindowPtr()->FlushMouseQueue();

	pIn->getWindowPtr()->DrawImage(screen, 0, 0, UI.width, UI.height);


	if (GInfo.x1 > xx)
	{
		x = xx;
		xx = GInfo.x1;
		GInfo.x1 = x;
	}
	if (GInfo.y1 >yy)
	{
		y = yy;
		yy = GInfo.y1;
		GInfo.y1 = y;
	}
	GInfo.x2 = xx;
	GInfo.y2 = yy;

	if (GInfo.x1 < 0)
		GInfo.x1 = 0;
	if (GInfo.x2 > UI.width / 15)
		GInfo.x2 = UI.width / 15 - 1;
	if (GInfo.y1 <  UI.ToolBarHeight / 15)
		GInfo.y1 = UI.ToolBarHeight / 15 + 1;
	if (GInfo.y2 >(UI.height - UI.StatusBarHeight) / 15)
		GInfo.y2 = (UI.height - UI.StatusBarHeight) / 15 - 1;
}

void select_area::Execute()
{
	ReadActionParameters();
	pManager->change_ALL_to_UnHI();
	pManager->selected_components.clear();
	pManager->help_select_area(GInfo);
	pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
}

void select_area::Undo()
{
	pManager->help_unselect_area(GInfo);
	pManager->selected_components.clear();
}

void select_area::Redo()
{
	pManager->help_select_area(GInfo);
}


select_area::~select_area()
{
}
