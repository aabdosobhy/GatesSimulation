//#include "Input.h"
#include "Output.h"
class ApplicationManager;
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
window* Input::getWindowPtr()
{
	return pWind;
}
string Input::GetSrting(Output *pOut)
{
	pWind->FlushKeyQueue();
	pWind->FlushMouseQueue();
	string s = "";
	///TODO: Implement this Function
	
	//////////////////// ESCAPE ASCII =27 ////// BACKSPACE =8 ////////// Enter =13
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	char n;
	keytype key= ARROW;
	while (key) {
		key = pWind->WaitKeyPress(n);
		if (key == ESCAPE)
		{
			s = "";
			return s;
		}
		if (key == ASCII)
		{
			if (n == 8) { 
				if (s.size() > 0) 
				{
					//s -= s[s.size() - 1];
					s=s.substr(0, s.size() -1);
				}
			}
			else if (n == 13)
			{ return s; }
			else
			{ s += n; }
		}
		pOut->PrintMsg(s);
	}
	return NULL;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() 
{
		int x, y;
		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

		if (UI.AppMode == DESIGN)	//application is in design mode
		{
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < UI.ToolBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
			

				case ITM_Add: return Add_Gate;
				case ITM_NEW: return NEW;
				case ITM_copy_cut: return copy_cut;
				case ITM_Edit_label: return EDIT_Label;
				case ITM_Delete: return DEL;
				case ITM_Select: return select_icon;
				case ITM_Unselect: return unselect;
				case ITM_Move: return MOVE;
				case ITM_Multi_Select:return multi_select;		
				case ITM_Select_Area:return Select_Area;
						//////////////////////
				case ITM_EXIT: return EXIT;
				case ITM_SWITCH_TO_SIMMULATION: return SIM_MODE;
				case ITM_SAVE:return SAVE;
				case ITM_LOAD: return LOAD;
				case ITM_REDO:return REDO;
				case ITM_UNDO: return UNDO;
				case ITM_Edit_pin:return EDIT_pin;


					/////// end ta3deel feryal
				default: return DSN_TOOL;	//A click on empty place in desgin toolbar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{   
				sx = x;           //HEBAAAAAAAAA BT3OOOOOOK
				sy = y;

				if (sx % 15 > 7)
					sx = sx / 15 + 1;
				else
					sx = sx / 15;


				if (sy % 15 > 7)
					sy = sy / 15 + 1;
				else
					sy = sy / 15;

					return UNSELECTALL;	    //HEBAAAAAAAAA
					
			}

			//[3] User clicks on the status bar
			return STATUS_BAR;
		}
		else if(UI.AppMode==SIMULATION)	//Application is in Simulation mode
		{

			///////////////START TA3DEEEEL HEBAAAAAAAAAAAA
			if (y >= 0 && y < UI.ToolBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_TRUTH:return Create_TruthTable;
			//	case ITM_ValidCiruit:return valid_circuit;
				case ITM_SimCirciut:return simulate_circuit;
				case ITM_PROBING:return prob_circuit;
				case ITM_SwitchToDesign:return DSN_MODE;
				case ITM_EXIT2:return EXIT;
				case ITM_changeSwitch:return Change_Switch;

				default: return SIM_TOOL;	//A click on empty place in  SIMU  toolbar
				}
				
			}
			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				sx = x;           //HEBAAAAAAAAA BT3OOOOOOK
				sy = y;
				if (sx % 15 > 7)
					sx = sx / 15 + 1;
				else
					sx = sx / 15;


				if (sy % 15 > 7)
					sy = sy / 15 + 1;
				else
					sy = sy / 15;
				return UNSELECTALL;	    //HEBAAAAAAAAA

			}

			//[3] User clicks on the status bar
			return STATUS_BAR;

			////////////////////////end hebaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

			//return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
		}
		else if (UI.AppMode == ADD)
		{
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < UI.ToolBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
					case ITM_AND2: return ADD_AND_GATE_2;
					case ITM_OR2: return ADD_OR_GATE_2;
					//case ITM_EXIT: return EXIT;
					///// start ta3deel feryal
					case ITM_NAND2: return ADD_NAND_GATE_2;
					case ITM_NOR2: return ADD_NOR_GATE_2;
					case ITM_XOR2: return ADD_XOR_GATE_2;
					case ITM_XNOR2: return ADD_XNOR_GATE_2;
					case ITM_AND3: return ADD_AND_GATE_3;
					case ITM_NOR3: return ADD_NOR_GATE_3;
					case ITM_XOR3: return ADD_XOR_GATE_3;
					case ITM_BUFFER: return ADD_Buff;
					case ITM_INVERTER: return ADD_INV;
					case ITM_SWITCH: return ADD_Switch;
					case ITM_LED: return ADD_LED;
					case ITM_CONNECTIONS: return ADD_CONNECTION;
					case ITM_switch_back:return Switch_Back;
					case ITM_REDO2:return REDO;
					case ITM_UNDO2: return UNDO;


					/////// end ta3deel feryal
				default: return ADD_tool;	//A click on empty place in desgin toolbar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				sx = x;           //HEBAAAAAAAAA BT3OOOOOOK
				sy = y;
				if (sx % 15 > 7)
					sx = sx / 15 + 1;
				else
					sx = sx / 15;


				if (sy % 15 > 7)
					sy = sy / 15 + 1;
				else
					sy = sy / 15;
				return UNSELECTALL;	    //HEBAAAAAAAAA

			}

			//[3] User clicks on the status bar
			return STATUS_BAR;
		}
		else
		{
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < UI.ToolBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				
				case ITM_switch_back2: return Create_TruthTable;
					/////// end ta3deel feryal
				default: return truth_tool;	//A click on empty place in desgin toolbar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				sx = x;           //HEBAAAAAAAAA BT3OOOOOOK
				sy = y;
				if (sx % 15 > 7)
					sx = sx / 15 + 1;
				else
					sx = sx / 15;


				if (sy % 15 > 7)
					sy = sy / 15 + 1;
				else
					sy = sy / 15;
				return UNSELECTALL;	    //HEBAAAAAAAAA

			}

			//[3] User clicks on the status bar
			return STATUS_BAR;
		}

}


	




Input::~Input()
{
}
