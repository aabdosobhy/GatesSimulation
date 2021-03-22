#include "exIt.h"



exIt::exIt(ApplicationManager *pApp) :Action(pApp)
{

}


exIt::~exIt()
{
}
void exIt::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Click A to save or ESC if you don't want to save.. ");
	string blank, yes, no;
	blank = "Images\\Menu\\blank.jpg";
	yes = "Images\\Menu\\blankyes.jpg";
	no = "Images\\Menu\\blankno.jpg";
	pIn->getWindowPtr()->DrawImage(blank, UI.width / 2 - 100, UI.height / 2 - 50, 200, 100);
	bool t = true;
	int x, y, xx, yy;
	while (t)
	{
		pIn->getWindowPtr()->GetMouseCoord(x, y);
		if (x >= UI.width / 2 - 100 + 25 && x <= UI.width / 2 - 100 + 85 && y >= UI.height / 2 - 50 + 63 && y <= UI.height / 2 - 50 + 92)
			pIn->getWindowPtr()->DrawImage(yes, UI.width / 2 - 100, UI.height / 2 - 50, 200, 100);
		else if (x >= UI.width / 2 - 100 + 116 && x <= UI.width / 2 + 176 - 100 && y >= UI.height / 2 - 50 + 63 && y <= UI.height / 2 - 50 + 92)
			pIn->getWindowPtr()->DrawImage(no, UI.width / 2 - 100, UI.height / 2 - 50, 200, 100);
		else 	pIn->getWindowPtr()->DrawImage(blank, UI.width / 2 - 100, UI.height / 2 - 50, 200, 100);
		if (pIn->getWindowPtr()->GetButtonState(LEFT_BUTTON, xx, yy) == BUTTON_DOWN)
		{
			if (xx >= UI.width / 2 - 100 + 25 && xx <= UI.width / 2 - 100 + 85 && yy >= UI.height / 2 - 50 + 63 && yy <= UI.height / 2 - 50 + 92)
			{
				pManager->save();
				break;
			}
			else if (xx >= UI.width / 2 - 100 + 116 && xx <= UI.width / 2 + 176 - 100 && yy >= UI.height / 2 - 50 + 63 && yy <= UI.height / 2 - 50 + 92)
				return;
		}
	}
	//char n;
	//keytype key = NO_KEYPRESS;
	//pIn->getWindowPtr()->FlushKeyQueue();     //HEBA TA3DEEEL
	//key = pIn->getWindowPtr()->WaitKeyPress(n);
	//if (key == ASCII)
	//{
	//	pManager->save();
	//}
	//else
	//{
	//	return;
	//}
}
void exIt::Execute()
{
	ReadActionParameters();

	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}
	while (!pManager->actualActions.empty())
	{
		pManager->actualActions.pop();
	}
	//pManager->cleaning();
	pManager->selected_components.clear();
	//pManager->~ApplicationManager();
}

void exIt::Undo()
{
}

void exIt::Redo()
{
}
