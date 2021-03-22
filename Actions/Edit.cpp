#include "Edit.h"
#include "..\Components\Connection.h"
#include "..\ApplicationManager.h"
#include"..\Components\Gate.h"
#include"..\Components\LED.h"
#include"..\Components\Switch.h"
#include<iostream>
using namespace std;

Edit::Edit(ApplicationManager *pApp) :Action(pApp)
{
}


Edit::~Edit()
{
}

void Edit::ReadActionParameters()
{

	can_draw = true;

	string firstpt = ""; //needed to check that the user did not connect between two output pins or two onput pins
	string secondpt = "";
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Draw connection : click the first point ' an empty place or a statusbar or a toolbar  is not allowed the action will end if so '    ");

	//Wait for User Input
	pIn->GetPointClicked(x1, y1);

	// calculate the new coordinates "magnet"

	if (x1 % 15 > 7) x1 = x1 / 15 + 1;
	else x1 = x1 / 15;
	if (y1 % 15 > 7) y1 = y1 / 15 + 1;
	else y1 = y1 / 15;
	x1 *= 15; y1 *= 15;
	//call fn elahsas


	if (ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second[0] == 'c')
	{

		if (ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second != "c_u"&&
			ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second != "c_l"&&
			ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second != "c_m"&&
			ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second != "c_o")
		{
			ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second = "cdt";
			firstpt = "out";
		}
		else if (ApplicationManager::screenMatrix[y1 / 15][x1 / 15].second == "c_o")
		{
			if (ApplicationManager::screenMatrix[y1 / 15][x1 / 15 + 1].second == "c_o")
			{
				x1 = x1 + 15;
			}
			firstpt = "out";
		}
		else
		{
			if (ApplicationManager::screenMatrix[y1 / 15][x1 / 15 - 1].second == "c_u" ||
				ApplicationManager::screenMatrix[y1 / 15][x1 / 15 - 1].second == "c_l" ||
				ApplicationManager::screenMatrix[y1 / 15][x1 / 15 - 1].second == "c_m"
				)
				x1 = x1 - 15;
			if (ApplicationManager::screenMatrix[y1 / 15 + 1][x1 / 15].second == "c_u")
			{
				y1 = y1 + 15;
				if (ApplicationManager::screenMatrix[y1 / 15 + 1][x1 / 15].second == "c_u")
					y1 = y1 + 15;
			}
			firstpt = "in";
		}
		pOut->PrintMsg("Draw connection : click the second point 'not an empty place or a statusbar or a toolbar '");

		//Wait for User Input
		pIn->GetPointClicked(x2, y2);

		// calculate the new coordinates "magnet"

		if (x2 % 15 > 7) x2 = x2 / 15 + 1;
		else x2 = x2 / 15;
		if (y2 % 15 > 7) y2 = y2 / 15 + 1;
		else y2 = y2 / 15;
		x2 *= 15; y2 *= 15;
		if (ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second[0] == 'c')
		{
			can_draw = true; //m4 la2yeen 7aga nektebha gwa el if 
			if (ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second != "c_u"&&
				ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second != "c_l"&&
				ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second != "c_m"&&
				ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second != "c_o")
			{
				ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second = "cdt";
				secondpt = "out";
			}
			else if (ApplicationManager::screenMatrix[y2 / 15][x2 / 15].second == "c_o")
			{
				if (ApplicationManager::screenMatrix[y2 / 15][x2 / 15 + 1].second == "c_o")
				{
					x2 = x2 + 15;
				}
				secondpt = "out";

			}
			else
			{
				if (ApplicationManager::screenMatrix[y2 / 15][x2 / 15 - 1].second == "c_u" ||
					ApplicationManager::screenMatrix[y2 / 15][x2 / 15 - 1].second == "c_l" ||
					ApplicationManager::screenMatrix[y2 / 15][x2 / 15 - 1].second == "c_m")
					x2 = x2 - 15;
				if (ApplicationManager::screenMatrix[y2 / 15 + 1][x2 / 15].second == "c_u")
				{
					y2 = y2 + 15;
					if (ApplicationManager::screenMatrix[y2 / 15 + 1][x2 / 15].second == "c_u")
						y2 = y2 + 15;
				}
				secondpt = "in";

			}
		}
		else
		{
			pOut->PrintMsg("the second point can't drawn here we will end the action");
			can_draw = false;
		}

	}
	else
	{
		pOut->PrintMsg("the first point can't drawn here we will end the action");
		can_draw = false;
	}
	if (firstpt == secondpt)
	{
		pOut->PrintMsg("Can not connect between two input pins or two output pins.We will end the action");
		can_draw = false;
	}

}

void Edit::select_connection()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMsg("Select connection you want to edit its source or destination or both of them");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);
	if (Cx % 15 > 7) Cx = Cx / 15 + 1;
	else Cx = Cx / 15;
	if (Cy % 15 > 7)Cy = Cy / 15 + 1;
	else Cy = Cy / 15;
	Cx *= 15; Cy *= 15;
	if (pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy / 15][Cx / 15].first) != NULL&&dynamic_cast<Connection*>(pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy / 15][Cx / 15].first)))
	{
		pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy / 15][Cx / 15].first)->change_to_HI();
		pManager->UpdateInterface();
	}
	else
	{
		can_draw = false;
		pOut->PrintMsg("you didn't select connection to edit so we will end the action");
	}
}

void Edit::Execute()
{

	Output* pOut = pManager->GetOutput();
	can_draw = true;
	select_connection();

	if (can_draw == false) {

		return;

	}

	id_done = ApplicationManager::screenMatrix[Cy / 15][Cx / 15].first;
	Connection *pA = ((Connection*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[Cy / 15][Cx / 15].first));

	pA->help_undo();
	pA->delete_connection_itself(pOut);

	ReadActionParameters();


	if (can_draw == false)
	{
		pA->Readd();
		return;
	}
	GraphicsInfo GInfo;
	GInfo.x1 = x1 / 15;
	GInfo.y1 = y1 / 15;
	GInfo.x2 = x2 / 15;
	GInfo.y2 = y2 / 15;

	////////ta3deeeeeeeeeeeeeel
	int xzyada, yzyada;
	if ((ApplicationManager::screenMatrix[GInfo.y1][GInfo.x1].second) == "c_u" ||
		(ApplicationManager::screenMatrix[GInfo.y1][GInfo.x1].second) == "c_l" ||
		(ApplicationManager::screenMatrix[GInfo.y1][GInfo.x1].second) == "c_m")
	{
		xzyada = GInfo.x1;
		yzyada = GInfo.y1;
		GInfo.x1 = GInfo.x1 - 1;
		pA->choosePath(GInfo);
	}
	else
	{

		xzyada = GInfo.x2;
		yzyada = GInfo.y2;
		GInfo.x2 = GInfo.x2 - 1;
		pA->choosePath(GInfo);
	}
	pair<int, int>zyada;
	zyada.first = xzyada;
	zyada.second = yzyada;
	//endddddddddddddddddddddddddddd




	//if(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second==c_o)

	id_done = pA->getid();  //ta3deeeeeeeeeeeeeel

	if (pA->path.size() == 0)
	{
		pOut->PrintMsg("This connection can't be drawen as there is no space");
		return;
	}
	else
	{
		//ta3deeeeeeeeelllllll
		// kda al source daymn hykon fe a5r al path 
		//||(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second.size() == 2
		if (((ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second) == "c_o" ||
			(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second) == "cdt"))

		{
			pA->path.push_back(zyada);
			std::reverse(pA->path.begin(), pA->path.end());
		}
		else
		{
			pA->path.insert(pA->path.begin(), zyada);
		}
		pA->sub_path = pA->path;
		//	subpath_done = pA->sub_path;

		//endddddddddddddddddddd

		//source is a connection
		if ((ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].second[1]) != '_')
		{
			//ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].second = "cdt"; // set this point as a tafree3a 
			//set the source pin as the source in of the original connection
			Connection * source = ((Connection*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first));
			if (source->getSourcePin()->ConnectTo(pA) == false) //reached max.fanout
			{
				pOut->PrintMsg("this connection can not be drawn as this output pin has its max num of fanout");
				delete pA;
				pA = NULL;
				return;
			}
			pA->setSourcePin(source->getSourcePin());

			pA->set_DstPair(pA->path[0]);
			pA->settafree3a(pA->path[pA->path.size() - 1]);
			pA->setmtfr3(true);
			//completing the path to the source pin
			int end = (source->path.size());
			for (int i = 0; i < end; i++)
			{
				if (source->path[i] == pA->gettafree3a())
				{
					Connection *temp = ((Connection*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first));
					for (int j = i; j < end; j++)
					{
						pA->path.push_back(temp->path[j]);
					}
					break;
				}

			}
			pA->set_sourcePair(pA->path[pA->path.size() - 1]);

			// destination
			//if destination is a led 
			if (pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first)->gettype() == "LED")
			{
				if (((LED*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_m_InputPin()->set_pConnect(pA))
				{
					pA->setDestPin(((LED*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_m_InputPin());
					pA->SetPinNum(0);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					pA->getSourcePin()->delete_SPECIFIC_m_Connections(pA->getid());
					delete pA;
					pA = NULL;
					return;
				}

			}
			//if destination is the upper pin of the gate
			else if (ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second[2] == 'u')
			{
				if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]->set_pConnect(pA))
				{
					pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]);
					pA->SetPinNum(0);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					pA->getSourcePin()->delete_SPECIFIC_m_Connections(pA->getid());
					delete pA;
					pA = NULL;
					return;
				}

			}
			//if destination is the lower pin of the gate
			else if (ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second[2] == 'l')
			{
				if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[1]->set_pConnect(pA))
				{
					pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[1]);
					pA->SetPinNum(1);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					pA->getSourcePin()->delete_SPECIFIC_m_Connections(pA->getid());
					delete pA;
					pA = NULL;
					return;
				}


			}
			//if destination is the middle pin of the gate in case it has three input pins 
			else if ((((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_InputsN() == 3))
			{
				if (ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second[2] == 'm')
				{
					if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[2]->set_pConnect(pA))
					{
						pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[2]);
						pA->SetPinNum(2);
					}
					else
					{
						pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
						pA->getSourcePin()->delete_SPECIFIC_m_Connections(pA->getid());
						delete pA;
						pA = NULL;
						return;
					}


				}
			}
			//if destination gate has only one input pin

			else if ((((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_InputsN() == 1))
			{
				if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]->set_pConnect(pA))
				{
					pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]);
					pA->SetPinNum(0);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					pA->getSourcePin()->delete_SPECIFIC_m_Connections(pA->getid());
					delete pA;
					pA = NULL;
					return;
				}



			}
		}
		//source is a gate or a switch 
		else if (ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].second[2] == 'o')
		{
			//source is a switch 
			if (pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first)->gettype() == "Switch")
			{
				if ((((Switch*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first))->get_OutputPin())->ConnectTo(pA))
				{
					pA->setSourcePin(((Switch*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first))->get_OutputPin());
					pA->set_DstPair(pA->path[0]);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this output pin has its max num of fanout");
					delete pA;
					pA = NULL;
					return;
				}

			}

			else {
				if ((((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first))->get_OutputPin())->ConnectTo(pA))
				{
					pA->setSourcePin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first))->get_OutputPin());
					pA->set_DstPair(pA->path[0]);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this output pin has its max num of fanout");
					delete pA;
					pA = NULL;
					return;
				}
			}
			// destination
			//if destination is a led 

			if (pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first)->gettype() == "LED")
			{
				if (((LED*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_m_InputPin()->set_pConnect(pA))
				{
					pA->setDestPin(((LED*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_m_InputPin());
					pA->SetPinNum(0);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					delete pA;
					pA = NULL;
					return;
				}

			}
			//if destination is the upper pin of the gate
			else if (ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second[2] == 'u')
			{
				if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]->set_pConnect(pA))
				{
					pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]);
					pA->SetPinNum(0);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					delete pA;
					pA = NULL;
					return;
				}


			}
			//if destination is the lower pin of the gate

			else if (ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second[2] == 'l')
			{
				if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[1]->set_pConnect(pA))
				{
					pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[1]);
					pA->SetPinNum(1);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					delete pA;
					pA = NULL;
					return;
				}



			}
			//if destination is the middle pin of the gate in case it has three input pins 

			else if ((((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_InputsN() == 3))
			{
				if (ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second[2] == 'm')
				{
					if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[2]->set_pConnect(pA))
					{
						pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[2]);
						pA->SetPinNum(2);
					}
					else
					{
						pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
						delete pA;
						pA = NULL;
						return;
					}


				}
			}
			//if destination gate has only one input pin

			else if ((((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_InputsN() == 1))
			{
				if (((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]->set_pConnect(pA))
				{
					pA->setDestPin(((Gate*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].first))->get_arr_InputPins()[0]);
					pA->SetPinNum(0);
				}
				else
				{
					pOut->PrintMsg("this connection can not be drawn as this input pin is not empty");
					delete pA;
					pA = NULL;
					return;
				}


			}
		}

	}
	//path_done = pA->path;

	//pA->updateMatrix_CONNECTION(pA->path);
	//pManager->AddComponent(pA);
	pA->setlazy_d(false);
	pA->change_to_UnHI();
	pManager->actualActions.push(this);
	while (!pManager->redoActions.empty())
	{
		pManager->redoActions.pop();
	}


	//push the action to allow undo and redo
	pManager->check_Add_Connection();          //de lena 3shan ntfrg
	pA->updateMatrix_CONNECTION(pA->sub_path);
	if (pA->getDestPin() == NULL)
		pOut->PrintMsg("this connection is not valid.Please connect from outpin or connection to input pin");
	if (pA->getSourcePin() == NULL)
		pOut->PrintMsg("this connection is not valid.Please connect from outpin or connection to input pin");

}

void Edit::Undo()
{

	Output* pOut = pManager->GetOutput();
	Connection *pA = ((Connection*)pManager->find_component_with_specific_id(id_done));
	//pA->delete_connection_itself(pOut);

	pA->help_redo();
	pA->delete_connection_itself(pOut);

	/*GraphicsInfo g;
	g.y1 = g.x1 = 90;
	g.y2 = g.x2 = 78;

	pOut->Clear_Connection_from_D_A(pA->path);*/
	//	this -> delete_from_Matrix(g);    //g mlhash lazma
	pA->Readd_undo();


}

void Edit::Redo()
{
	Output* pOut = pManager->GetOutput();
	Connection *pA = ((Connection*)pManager->find_component_with_specific_id(id_done));
	pA->delete_connection_itself(pOut);
	pA->Readd_redo();
}
