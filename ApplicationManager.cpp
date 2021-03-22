#include "ApplicationManager.h"
#include"Actions\AddGate.h"
#include"Actions\Edit_label.h"
#include"Actions\Multi_select.h"
#include"Actions\Select.h"
#include"Actions\SwitchBack.h"
#include"Actions\unselect_all.h"
#include"Actions\Unselect.h"
#include"Actions\switchtosim.h"
#include"Actions\switchtodesign.h"
#include"Actions\AddAND2.h"
#include "Actions\AddBuffer.h"
#include "Actions\AddINVERTER.h"
#include "Actions\AddOR2.h"
#include "Actions\AddNOR2.h"
#include"Actions\AddXNOR2.h" 
#include "Actions\AddXOR2.h"
#include "Actions\AddAND3.h"
#include "Actions\AddNOR3.h"
#include "Actions\AddXOR3.h"
#include "Actions\AddSWITCH.h"
#include "Actions\AddLED.h"
#include "Actions\AddNAND2.h"
#include "Actions\Move.h"
#include"Actions\Run.h"
#include"Components\XOR3.h"
#include"Components\NOR3.h"
#include"Actions\redo.h"
#include"Actions\undo.h"
#include"Actions\select_area.h"
#include "Actions\AddCONNECTION.h"
#include"Actions\cut_copy.h"
#include"Actions\Delete.h"
#include"Components\LED.h"
#include"Components\Switch.h"
#include"Actions\Edit.h"
#include"Actions\create_truthtable.h"
#include"Actions\changeSwitch.h"
#include"Actions\exIt.h"
#include"Actions\New.h"
#include"Actions\proping.h"
#include"Actions\Save.h"
#include"Actions\Load.h"
#include<fstream>
#include<iostream>
#include <string>
using namespace std;

std::pair<int, std::string> ApplicationManager::screenMatrix[UI.height / 15 + 1][UI.width / 15 + 1];
//image *ApplicationManager::CircSimag=new image();

void ApplicationManager::check_Add_Connection()
{
	for (int i = 0; i < CompCount; i++)
	{
		if ((dynamic_cast<Gate*>(CompList[i]) != 0))
			cout << ((Gate*)CompList[i])->get_OutputPin()->get_m_Conn();
		if (dynamic_cast<Gate*>(CompList[i]) != 0)
			for (int j = 0; j < ((Gate*)CompList[i])->get_InputsN(); j++)
			{
				if (((Gate*)CompList[i])->get_arr_InputPins()[j]->get_pConnect() != NULL)
					cout << ((Gate*)CompList[i])->get_arr_InputPins()[j]->get_pConnect()->gettype();
			}
	}
}

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	//truth_table = false;
	for (int i = 0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
	fillmatrix();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddAND2(this);
		break;

	case ADD_AND_GATE_3:
		pAct = new AddAND3(this);
		break;

	case ADD_Buff:
		pAct = new AddBuffer(this);
		break;

	case ADD_NOR_GATE_2:
		pAct = new AddNOR2(this);
		break;

	case ADD_OR_GATE_2:
		pAct = new AddOR2(this);
		break;
	case simulate_circuit:
		pAct = new Run(this);
		break;


	case ADD_NOR_GATE_3:
		pAct = new AddNOR3(this);
		break;


	case ADD_XNOR_GATE_2:
		pAct = new AddXNOR2(this);
		break;

	case ADD_XOR_GATE_2:
		pAct = new AddXOR2(this);
		break;

	case ADD_XOR_GATE_3:
		pAct = new AddXOR3(this);
		break;

	case ADD_NAND_GATE_2:
		pAct = new AddNAND2(this);
		break;

	case ADD_LED:
		pAct = new AddLED(this);
		break;

	case ADD_INV:
		pAct = new AddINVERTER(this);
		break;
	case ADD_Switch:
		pAct = new AddSWITCH(this);
		break;
	case MOVE:
		pAct = new Move(this);
		break;

	case ADD_CONNECTION:
		pAct = new AddCONNECTION(this);
		break;
	case Switch_Back:                     //hebaaaaaaaaaaa
		pAct = new SwitchBack(this);
		break;
	case EDIT_Label:                     //hebaaaaaaaaaaa
		pAct = new Edit_label(this);
		break;
	case DSN_MODE:
		pAct = new switchtodesign(this);
		break;
	case SIM_MODE:
		pAct = new switchtosim(this);
		break;
	case Add_Gate:
		pAct = new AddGate(this);
		break;

	case NEW:
		pAct = new New(this);
		break;

	case select_icon:
		pAct = new Select(this);
		break;
	case multi_select:
		pAct = new Multi_select(this);
		break;
	case unselect:
		pAct = new Unselect(this);
		break;

	case UNSELECTALL:           //A click on empty place in drawing area hebaaaaaaaaaaa
		pAct = new unselect_all(this);
		break;
	case UNDO:
		pAct = new undo(this);
		break;
	case REDO:
		pAct = new redo(this);
		break;
	case copy_cut:
		pAct = new cut_copy(this);
		break;
	case DEL:
		pAct = new Delete(this);
		break;
	case Select_Area:
		pAct = new select_area(this);
		break;
	case EDIT_pin:
		pAct = new Edit(this);
		break;
	case Create_TruthTable:
		pAct = new create_truthtable(this);
		break;
	case Change_Switch:
		pAct = new changeSwitch(this);
		break;
	case prob_circuit:
		pAct = new proping(this);
		break;
	case SAVE:
		pAct = new Save(this);
		break;
	case LOAD:
		pAct = new Load(this);
		break;

	case EXIT:
		pAct = new exIt(this);
		break;
	}

	if (pAct)
	{
		pAct->Execute();
		//delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	if (UI.AppMode != TruthTable)
	{
		InputInterface->getWindowPtr()->SetPen(BLUE, 3);

		for (int i = 0; i < UI.width; i += 15)
		{
			for (int j = 90; j < UI.height - 50; j += 15)


				InputInterface->getWindowPtr()->DrawPixel(i, j);

		}
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->getlazy_d() == false)
				CompList[i]->Draw(OutputInterface);


		}
	}
}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;

}
void ApplicationManager::fillmatrix()
{
	for (int i = 0; i <UI.height / 15 + 1; i++)
		for (int j = 0; j <UI.width / 15 + 1; j++)
		{

			screenMatrix[i][j].first = 0;
			screenMatrix[i][j].second = "empty";  //      
		}

	for (int i = 0; i <(UI.ToolBarHeight + 10) / 15 + 1; i++)
		for (int j = 0; j < UI.width / 15 + 1; j++)
		{
			screenMatrix[i][j].first = -5;
			screenMatrix[i][j].second = "toolbar";
		}

	for (int i = (UI.height - UI.StatusBarHeight - 15) / 15 + 1; i <UI.height / 15 + 1; i++)
		for (int j = 0; j < UI.width / 15 + 1; j++)
		{
			screenMatrix[i][j].first = -5;
			screenMatrix[i][j].second = "statusbar"; // statusbar    
		}
}
Component* ApplicationManager::find_component_with_specific_id(int component_id)
{
	int i;
	for (i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getid() == component_id)
			return CompList[i];
	}
	if (i >= CompCount)
		return  NULL;

}
void ApplicationManager::Delete_selected_components(vector<int>& iddones)
{

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getHI() == true && (dynamic_cast<Gate*>(CompList[i]) || dynamic_cast<Switch*>(CompList[i]) || dynamic_cast<LED*>(CompList[i])) && CompList[i]->getlazy_d() != true)
		{
			iddones.push_back(CompList[i]->getid());
			GraphicsInfo g = CompList[i]->getgrahicsinfo();
			CompList[i]->Delete(OutputInterface);//to delete components 
			Lazy_DeleteComponent(CompList[i]->getid(), g);
			OutputInterface->Clear_Gate_from_D_A(g.x1, g.y1);
			//CompList[i]->change_to_UnHI();
		}
		else if (CompList[i]->getHI() == true && dynamic_cast<Connection*>(CompList[i]) && CompList[i]->getlazy_d() != true)
		{
			iddones.push_back(CompList[i]->getid());
			((Connection*)CompList[i])->delete_connection_itself(OutputInterface);  //gwaha delete from drawing area
																					//Lazy_DeleteConnetion(CompList[i]->getid(),((Connection*)CompList[i])->path);
																					//CompList[i]->change_to_UnHI();
			cleaned = false;
		}
	}
	selected_components.clear();
}

void ApplicationManager::Readd_selected_components(vector<int>& iddones)
{
	int i = 0, j = 0;
	while (i < CompCount&&j < iddones.size())
	{
		if (CompList[i]->getid() == iddones[j])   //&& CompList[i]->getHI() == false
		{
			//CompList[i]->change_to_HI();
			/*if (!dynamic_cast<Connection*>(CompList[i]))
			{
			GraphicsInfo g;
			g = CompList[i]->getgrahicsinfo();
			selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
			}*/

			CompList[i]->setlazy_d(false);

			CompList[i]->Readd();

			j++;
		}
		i++;
	}
}
void ApplicationManager::change_copy_unhi(vector<int>& iddones)
{
	int i = 0, j = 0;
	while (i < CompCount&&j < iddones.size())
	{
		if (CompList[i]->getid() == iddones[j])   //&& CompList[i]->getHI() == false
		{
			CompList[i]->change_to_UnHI();

			j++;
		}
		i++;
	}
}




void ApplicationManager::uncopy_cut_components(vector<int>& iddones2)
{
	int i = 0, j = 0;
	while (i < CompCount&&j < iddones2.size())
	{
		if (CompList[i]->getid() == iddones2[j])   //&& CompList[i]->getHI() == false
		{
			GraphicsInfo g = CompList[i]->getgrahicsinfo();
			CompList[i]->Delete(OutputInterface);//to delete components 
			Lazy_DeleteComponent(CompList[i]->getid(), g);
			OutputInterface->Clear_Gate_from_D_A(g.x1, g.y1);

			j++;
		}
		i++;
	}
}

int ApplicationManager::GetNumofSw()
{
	int NumSw = 0;
	for (int i = 0; i <getcopmcount(); i++)
		if (dynamic_cast<Switch*>(CompList[i]))
			NumSw++;


	return NumSw;

}
int ApplicationManager::GetNumofLD()
{
	int NumLD = 0;
	for (int i = 0; i <getcopmcount(); i++)
		if (dynamic_cast<LED*>(CompList[i]))
			NumLD++;


	return NumLD;

}
///////////////////////////////////////////////////////////////////////////

void ApplicationManager::DeleteCompList() {
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	CompCount = 0;
	fillmatrix();
	OutputInterface->ClearDrawingArea();
	OutputInterface->CreateDesignToolBar();
	

}
//////////////////////////////////////////////

void  ApplicationManager::setSwitches(int* Comb,string*&S)
{
	vector <Component * > switches;
	int j = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if ((dynamic_cast<Switch *> (CompList[i])))        //ta3del
		{
			S[j++] = CompList[i]->getlabel();
			switches.push_back(CompList[i]);
		}
	}
	for (int i = 0; i < GetNumofSw(); i++)
	{
		if (Comb[i] == 0)
			((Switch*)switches[i])->get_OutputPin()->setStatus(LOW);
		else ((Switch*)switches[i])->get_OutputPin()->setStatus(HIGH);
	}
}
/////////////////////////////////////////////////////
void ApplicationManager::GetLDs(int* &LDs, string*&S)
{
	//int *LDs = new int[GetNumofLD()];
	int j = 0;
	for (int i = 0; i < getcopmcount(); i++)
		if (dynamic_cast<LED*>(CompList[i]))
		{
			S[j] = CompList[i]->getlabel();
			if (CompList[i]->GetInputPinStatus(1) == LOW)
				LDs[j] = 0;
			else LDs[j] = 1;

			j++;
		}

}
void ApplicationManager::switch_design()
{
	for (int i = 0; i < CompCount; i++)
	{
		 if (dynamic_cast<Switch*>(CompList[i]))
		{
			((Switch*)CompList[i])->setoutputpinstatus(LOW);
			((Switch*)CompList[i])->Operate();
		}
	}
	for (int i = 0; i < CompCount; i++)
	{

		if (!dynamic_cast<Connection*>(CompList[i]))
		{

			if (dynamic_cast<LED*>(CompList[i]))
			{
				((LED*)CompList[i])->get_m_InputPin()->setvisited(false);
				((LED*)CompList[i])->setcalculated(false);
				((LED*)CompList[i])->setInputPinStatus(0, LOW);
				((LED*)CompList[i])->Operate();
			}
			else if (dynamic_cast<Gate*>(CompList[i]))
			{
				((Gate*)CompList[i])->set_input_pins_unvisted();
				((Gate*)CompList[i])->setcalculated(false);
				((Gate*)CompList[i])->setoutputpinstatus(LOW);
			}
			

		}
	}
	/*for (int i = 0; i < CompCount; i++)
	{
		if (!dynamic_cast<Switch*>(CompList[i]))
		CompList[i]->Operate();
		
	}*/

}

////////////////////////////////////////////

////////////////////////////////////////////

void ApplicationManager::run_for_simulation()
{


	vector <Component * > switches;
	queue <Component *> components;
	Component * temp;

	for (int i = 0; i < CompCount; i++)
	{

		if (!dynamic_cast<Connection*>(CompList[i]))
		{
			
			 if (dynamic_cast<LED*>(CompList[i]))
			{
				((LED*)CompList[i])->get_m_InputPin()->setvisited(false);
			}
			else if (dynamic_cast<Gate*>(CompList[i]))
			{
				((Gate*)CompList[i])->set_input_pins_unvisted();
			}

		}
	}

		for (int i = 0; i < CompCount; i++)
	{
		if ((dynamic_cast<Switch *> (CompList[i])))        //ta3del
			switches.push_back(CompList[i]);

	}


	for (int i = 0; i < switches.size(); i++)
	{
		
		components.push(switches[i]);
		components.front();
		

		

		while (!components.empty())
		{

		
			if (dynamic_cast<Switch*>(components.front()))

				((Switch*)components.front())->get_OutputPin()->set_children_visited_and_set_status(components);

			else // if a gate (not led)
				((Gate*)components.front())->get_OutputPin()->set_children_visited_and_set_status(components);

			components.pop();
		}

		
	}

}

std::string ApplicationManager::circuit_valid()
{
	int switchCount = 0;
	int ledCount = 0;
	queue<Component*> switches; //contains all switches 
	queue<Component*> help_sequential; //cointains the path from a switch till a led 
	for (int i = 0; i < CompCount; i++)
	{
		if (!(dynamic_cast<Connection*>(CompList[i])))
		{
			if (dynamic_cast<Switch*>(CompList[i]))
			{
				switchCount++;
				switches.push(CompList[i]);
				if (((Switch*)CompList[i])->get_OutputPin()->get_m_Conn() == 0)
					return "empty pin";
			}
			else if (dynamic_cast<LED*>(CompList[i]))
			{
				ledCount++;
				if (((LED*)CompList[i])->get_m_InputPin()->get_pConnect() == NULL)
					return "empty pin";
			}
			else if (((Gate*)CompList[i])->check_empty_Pin())
				return "empty pin";


		}
	}
	if (switchCount == 0)
		return "No Switch";

	if (ledCount == 0)
		return "No LED";
	while (!switches.empty())
	{
		help_sequential.push(switches.front());
		while (!help_sequential.empty())
		{
			if (dynamic_cast<Switch*>(help_sequential.front()))

				((Switch*)help_sequential.front())->get_OutputPin()->set_children_visited(help_sequential);

			else // if a gate (not led)
				((Gate*)help_sequential.front())->get_OutputPin()->set_children_visited(help_sequential);
			help_sequential.pop();
		}
		switches.pop();
	}


	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<LED*>(CompList[i]))
			if ((CompList[i])->getcalculated() == false)
				return "sequential";
	}

	return "No Error";
}


void ApplicationManager::Lazy_DeleteComponent(int i, GraphicsInfo GInfo)
{
	cleaned = false;
	find_component_with_specific_id(i)->setlazy_d(true);
	find_component_with_specific_id(i)->delete_from_Matrix(GInfo);
}
void ApplicationManager::Lazy_DeleteConnetion(int i, vector<pair<int, int>> path)  //b3talo sub bath
{
	cleaned = false;
	find_component_with_specific_id(i)->setlazy_d(true);
	//find_component_with_specific_id(i)->delete_from_Matrix(find_component_with_specific_id(i)->getgrahicsinfo());
}

void ApplicationManager::cleaning()
{
	cleaned = true;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getlazy_d() == true)
		{
			swap(CompList[i], CompList[CompCount - 1]);
			delete CompList[CompCount - 1];
			CompList[CompCount - 1] = NULL;
			CompCount--;
		}
	}
}

void  ApplicationManager::change_ALL_to_UnHI()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->change_to_UnHI();
	}
}

bool ApplicationManager::check_matrix(int cx, int cy)   //check almsahaa aly hadeef feha fadia wla laa
{
	cx /= 15; cy /= 15;
	bool t = true;
	for (int j = cy - 3; j <= cy + 2; j++) //50
	{
		for (int i = cx - 2; i <= cx + 2; i++)
		{
			if (j<0 || j>UI.height / 15 || i<1 || i>UI.width / 15)
				return false;
			if (screenMatrix[j][i].second != "empty")    // htrg3
			{
				t = false;
				break;
			}
		}
		if (!t)
			break;
	}


	return t;

}
void ApplicationManager::help_select_area(GraphicsInfo GInfo)
{


	for (int j = GInfo.y1; j <= GInfo.y2; j++) //50
	{
		for (int i = GInfo.x1; i <= GInfo.x2; i++)
		{
			/*if (j<0 || j>UI.height / 15 || i<1 || i>UI.width / 15)
			return false;*/
			if (screenMatrix[j][i].second != "empty"&&screenMatrix[j][i].second != "label")    // htrg3
			{
				bool hbush = true;
				find_component_with_specific_id(screenMatrix[j][i].first)->change_to_HI();
				GraphicsInfo g;
				g = find_component_with_specific_id(screenMatrix[j][i].first)->getgrahicsinfo();
				for (int k = 0; k < selected_components.size(); k++)
				{
					if (selected_components[k].first.first == g.x1&&selected_components[k].first.second == g.y1)
						hbush = false;
				}
				if (hbush&& !(dynamic_cast<Connection*>(find_component_with_specific_id(screenMatrix[j][i].first))))
					selected_components.push_back(pair<pair<int, int>, pair<int, int>>(pair<int, int>(g.x1, g.y1), pair<int, int>(0, 0)));
			}
		}
		//(ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'h'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'v'&&ApplicationManager::screenMatrix[g.y1 / 15][g.x1 / 15].second[1] != 'd')
	}


}

void ApplicationManager::help_unselect_area(GraphicsInfo GInfo)
{


	for (int j = GInfo.y1; j <= GInfo.y2; j++) //50
	{
		for (int i = GInfo.x1; i <= GInfo.x2; i++)
		{
			/*if (j<0 || j>UI.height / 15 || i<1 || i>UI.width / 15)
			return false;*/
			if (screenMatrix[j][i].second != "empty"&&screenMatrix[j][i].second != "label")    // htrg3
			{
				find_component_with_specific_id(screenMatrix[j][i].first)->change_to_UnHI();
			}
		}

	}


}
void ApplicationManager::copy_selected_components(int x, int y, vector<int>& iddones1, vector<int>& iddones2)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getHI() == true && (dynamic_cast<Gate*>(CompList[i]) || dynamic_cast<Switch*>(CompList[i]) || dynamic_cast<LED*>(CompList[i])))

		{
			iddones1.push_back(CompList[i]->getid());
			GraphicsInfo g = CompList[i]->getgrahicsinfo();
			for (int j = 0; j < selected_components.size(); j++)
			{
				if (x - selected_components[j].second.first == g.x1&&y - selected_components[j].second.second == g.y1)
					CompList[i]->copy(this, selected_components[j].first.first, selected_components[j].first.second, iddones2);
			}

		}
	}
}

void ApplicationManager::cut_selected_components(int x, int y, vector<int>& iddones1, vector<int>& iddones2)
{
	/*for (int i = 0; i < CompCount; i++)
	{
	if ((dynamic_cast<Gate*>(CompList[i]) != 0))
	cout << ((Gate*)CompList[i])->get_OutputPin().get_m_Conn();
	if	(dynamic_cast<Gate*>(CompList[i]) != 0)
	cout << ((Gate*)CompList[i])->get_arr_InputPins()[0].getStatus();
	}*/
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getHI() == true && (dynamic_cast<Gate*>(CompList[i]) || dynamic_cast<Switch*>(CompList[i]) || dynamic_cast<LED*>(CompList[i]))
			)
		{
			iddones1.push_back(CompList[i]->getid());
			GraphicsInfo g = CompList[i]->getgrahicsinfo();
			for (int j = 0; j < selected_components.size(); j++)
			{
				if (x - selected_components[j].second.first == g.x1&&y - selected_components[j].second.second == g.y1)
				{
					CompList[i]->cut(this, selected_components[j].first.first, selected_components[j].first.second, iddones2);
					CompList[i]->Delete(OutputInterface);//to delete components 
					Lazy_DeleteComponent(CompList[i]->getid(), g);
					OutputInterface->Clear_Gate_from_D_A(g.x1, g.y1);
				}
			}
		}
	}
	selected_components.clear();

}

////////////////////////////////////////////////////////////////////
void ApplicationManager::save()
{
	ofstream out;
	out.open("save.txt", ios::out);
	out << getcopmcount() << endl;

	for (int i = 0; i < getcopmcount(); i++)
	{
		if (!dynamic_cast<Connection*>(CompList[i]))  //if the component isn't a connection 
		{
			CompList[i]->Save(out);
		}

	}
	out << "Connections\n";
	for (int i = 0; i < getcopmcount(); i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))  //if the component is a connection 
		{
			CompList[i]->Save(out);
		}

	}
	out << "-1" << endl;
	out.close();





}
////////////////////////////////////////////////////////////

void ApplicationManager::load() {

	ifstream in;
	in.open("save.txt");
	int counter;
	in >> counter;
	//CompCount = counter;
	int i;
	string *Typ = new string[counter + 2]; string* Lbl = new string[counter];
	GraphicsInfo *Gfx = new GraphicsInfo[counter];
	int *ID = new int[counter];
	int *IP = new int[counter];//source component 
	int *OP = new int[counter];//destination component
	int *Pin = new int[counter]; //pin number
	int j = 0;
	OP[0] = 3;
	Typ[0] = "Start";
	in >> Typ[0];
	for (i = 0; i < counter&&Typ[i] != "Connections"; ++i)
	{

		in >> ID[i] >> Lbl[i] >> Gfx[i].x1 >> Gfx[i].y1 >> Gfx[i].x2 >> Gfx[i].y2;
		if (Lbl[i] == "NULL") Lbl[i] = "";
		in >> Typ[i + 1];
	}

	in >> IP[0];
	for (i = 0; IP[i] != -1; i++)
	{
		in >> OP[i] >> Pin[i];
		in >> IP[i + 1];
	}


	/////////////////////////////Loading Compnents but for Connections////////////////////////////
	for (i = 0; Typ[i] != "Connections"; ++i)
	{

		if (Typ[i] == "AND2")
		{
			AND2 *Comp = new AND2(Gfx[i], AND2_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);



		}
		else if (Typ[i] == "AND3")
		{
			AND3 *Comp = new AND3(Gfx[i], AND3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "Buffer")
		{
			Buffer *Comp = new Buffer(Gfx[i], AND3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);


		}
		else if (Typ[i] == "Inverter")
		{
			Inverter *Comp = new Inverter(Gfx[i], AND3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "LED")
		{
			LED *Comp = new LED(Gfx[i]);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "NAND2")
		{
			NAND2 *Comp = new NAND2(Gfx[i], AND2_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "NOR2")
		{
			NOR2 *Comp = new NOR2(Gfx[i], AND3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "NOR3")
		{
			NOR3 *Comp = new NOR3(Gfx[i], AND3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "OR2")
		{
			OR2 *Comp = new OR2(Gfx[i], AND3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);


			
		}
		else if (Typ[i] == "Switch")
		{
			Switch*Comp = new Switch(Gfx[i], Switch_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}
		else if (Typ[i] == "XNOR2")
		{
			XNOR2 *Comp = new XNOR2(Gfx[i], XNOR2_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

			
		}
		else if (Typ[i] == "XOR2")
		{
			XOR2 *Comp = new XOR2(Gfx[i], XOR2_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);

			AddComponent(Comp);

		}
		else if (Typ[i] == "XOR3")
		{
			XOR3 *Comp = new XOR3(Gfx[i], XOR3_FANOUT);
			Comp->load(Typ[i], Lbl[i], Gfx[i], ID[i]);
			AddComponent(Comp);

		}

	}
	Connection**Arr = new Connection*[counter - i + 1];

	CompCount = i;			

		
	//////////////////////// Loading Connections //////////////////////////////

	for (i; i < counter&&IP[j] != -1; i++)
	{
	
		//Temporary O/P and I/P pins to be set to the connection
		InputPin*tempin;
		OutputPin*tempout;


		if (dynamic_cast <Gate*>(find_component_with_specific_id(IP[j])))
		{

			Gfx[i].x1 =( find_component_with_specific_id(IP[j])->getm_GfxInfo().x2+5) / 15;  
			Gfx[i].y1 = (find_component_with_specific_id(IP[j])->getm_GfxInfo().y1+25) / 15 ;          
			Gate* Ci = (Gate*)find_component_with_specific_id(IP[j]);
			tempout = Ci->get_OutputPin();
			if (tempout->getactualfanout()>1) // if the connection is a fanout not the original connection

			{
				
				Gfx[i].x1 = tempout->get_m_Connections()[0]->path[ tempout->get_m_Connections()[0]->path.size()-1-tempout->getactualfanout()-1 ].first; //first ???
				Gfx[i].y1 = tempout->get_m_Connections()[0]->path[tempout->get_m_Connections()[0]->path.size() - 1 - tempout->getactualfanout()-1].second;
			}
		}
		else if (dynamic_cast <Switch*>(find_component_with_specific_id(IP[j])))
		{
			Gfx[i].x1 = (find_component_with_specific_id(IP[j])->getm_GfxInfo().x2 + 5) / 15; 
			Gfx[i].y1 = (find_component_with_specific_id(IP[j])->getm_GfxInfo().y1 + 25) / 15;
			Switch* Ci = (Switch*)find_component_with_specific_id(IP[j]);
			tempout = Ci->get_OutputPin();
			if (tempout->getactualfanout()>1) // if the connection is a fanout not the original connection
			{
				Gfx[i].x1 = tempout->get_m_Connections()[0]->path[tempout->get_m_Connections()[0]->path.size() - 1 - tempout->getactualfanout()-1].first; //first ???
				Gfx[i].y1 = tempout->get_m_Connections()[0]->path[tempout->get_m_Connections()[0]->path.size() - 1 - tempout->getactualfanout()-1].second; //second??

			}
			
			

		}

		if (dynamic_cast <Gate*>(find_component_with_specific_id(OP[j])))
		{
			Gfx[i].x2 = (find_component_with_specific_id(OP[j])->getm_GfxInfo().x1-5) / 15;
			if (Pin[j] == 2 || dynamic_cast <Buffer*>(find_component_with_specific_id(OP[j])) ||
				dynamic_cast <Inverter*>(find_component_with_specific_id(OP[j])))
				Gfx[i].y2 = (find_component_with_specific_id(OP[j])->getm_GfxInfo().y1 + 25) / 15;
			else if (Pin[j] == 0)
				Gfx[i].y2 =( find_component_with_specific_id(OP[j])->getm_GfxInfo().y1 +10) / 15;
			else if (Pin[j] == 1)
				Gfx[i].y2 = (find_component_with_specific_id(OP[j])->getm_GfxInfo().y1 +40)/ 15 ;
	
			Gate* Co = (Gate*)find_component_with_specific_id(OP[j]);
			tempin = Co->get_arr_InputPins()[Pin[j]];
		}
		else if (dynamic_cast <LED*>(find_component_with_specific_id(OP[j])))
		{
			Gfx[i].x2 = (find_component_with_specific_id(OP[j])->getm_GfxInfo().x1 +25)/ 15 ;
			Gfx[i].y2 =( find_component_with_specific_id(OP[j])->getm_GfxInfo().y1 +55)/ 15 ;
			LED* Co = (LED*)find_component_with_specific_id(OP[j]);
			tempin = Co->get_m_InputPin();

		}



		Connection* pA = new Connection(Gfx[i], tempout, tempin);
		pA->load("connection", "", Gfx[i], i);

		AddComponent(pA);


		j++;
	}
	ofstream out;



	this->UpdateInterface();
	in.close();
	delete[]OP;
	delete[]IP;
	delete Arr;
	delete[]ID;
	delete[]Gfx;
	delete[]Pin;
	delete[]Lbl;
	delete[]Typ;

}
/////////////////////////////////////////////////////////////////////////////
