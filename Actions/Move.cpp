#include "Move.h"
#include "..\Components\LED.h"
#include "..\Components\Gate.h"
#include"..\Components\Switch.h"
using namespace std;
void Move::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on gate you want to move ");
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
	//id_done = 0;
}

void Move::Execute()
{
	image toolbarimage;
	image screenimage;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int xx, yy;
	string empty = "empty.JPG";
	image gate;
	actualcomponent = 0;
	//////////////////////////////////	
	//////////////////////////////////
	//////////////////////////////////
	////////   t3dil gdid    /////////
	//////////////////////////////////
	//////////////////////////////////
	//////////////////////////////////


	int xsmall, ysmall, xbig, ybig;

	bool selected = false;
	for (int i = 0; i < pManager->selected_components.size(); i++)
	{

		if (i == 0)
		{
			pManager->selected_components[i].first.first += 25;
			pManager->selected_components[i].first.second += 25;
			xbig = xsmall = pManager->selected_components[i].first.first;
			ysmall = ybig = pManager->selected_components[i].first.second;
			selected = true;
			actualcomponent++;
			selectedcomp.push_back(pManager->find_component_with_specific_id(pManager->getComponentPosition(pManager->selected_components[i].first.first / 15, pManager->selected_components[i].first.second / 15)));
			delete_gate_conection_from_bath_matrix(selectedcomp[i]);


			pair<pair<int, int>, pair<int, int>>emp;
			emp.first.first = pManager->selected_components[i].first.first;
			emp.first.second = pManager->selected_components[i].first.second;
			emp.second.first = 0;
			emp.second.second = 0;
			oldandnew.push_back(emp);
		}

		else
		{
			pManager->selected_components[i].first.first += 25;
			pManager->selected_components[i].first.second += 25;
			if (xbig < pManager->selected_components[i].first.first)
				xbig = pManager->selected_components[i].first.first;
			if (xsmall > pManager->selected_components[i].first.first)
				xsmall = pManager->selected_components[i].first.first;

			if (ybig < pManager->selected_components[i].first.second)
				ybig = pManager->selected_components[i].first.second;
			if (ysmall > pManager->selected_components[i].first.second)
				ysmall = pManager->selected_components[i].first.second;

			selectedcomp.push_back(pManager->find_component_with_specific_id(pManager->getComponentPosition(pManager->selected_components[i].first.first / 15, pManager->selected_components[i].first.second / 15)));
			actualcomponent++;
			delete_gate_conection_from_bath_matrix(selectedcomp[i]);
			pair<pair<int, int>, pair<int, int>>emp;
			emp.first.first = pManager->selected_components[i].first.first;
			emp.first.second = pManager->selected_components[i].first.second;
			emp.second.first = 0;
			emp.second.second = 0;
			oldandnew.push_back(emp);
		}

	}







	//ReadActionParameters();
	char n;
	keytype key = NO_KEYPRESS;
	int iX, iY;
	if (selected)
	{
		int RectULX = xsmall - 30;
		int RectULY = ysmall - 45;
		int RectWidth = xbig - xsmall + 60;
		int Rectlength = ybig - ysmall + 75;
		GraphicsInfo kkk;

		for (int i = 0; i < pManager->selected_components.size(); i++)
		{
			pManager->selected_components[i].second.first = pManager->selected_components[i].first.first - RectULX;
			pManager->selected_components[i].second.second = pManager->selected_components[i].first.second - RectULY;


			kkk.x1 = pManager->selected_components[i].first.first - 25;
			kkk.y1 = pManager->selected_components[i].first.second - 25;
			selectedcomp[i]->delete_from_Matrix(kkk);



			pIn->getWindowPtr()->DrawImage(empty, pManager->selected_components[i].first.first - 25, pManager->selected_components[i].first.second - 45, 50, 70);
			pIn->getWindowPtr()->SetPen(BLUE, 3);
			for (int k = pManager->selected_components[i].first.first - 30; k <pManager->selected_components[i].first.first + 30; k += 15)
			{
				for (int m = pManager->selected_components[i].first.second - 45; m < pManager->selected_components[i].first.second + 30; m += 15)


					pIn->getWindowPtr()->DrawPixel(k, m);

			}

		}
		//xold = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getgrahicsinfo().x1 + 25;
		//yold = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy))->getgrahicsinfo().y1 + 25;

		//Component * temp = pManager->find_component_with_specific_id(pManager->getComponentPosition(Cx, Cy));



		/*	kkk.x1 = xold - 25;
		kkk.y1 = yold - 25;
		temp->delete_from_Matrix(kkk);*/

		char cKeyData;

		bool goodarea = true;
		bool bDragging = false;

		iX = iY = 0;

		int iXOld = 0;
		int iYOld = 0;
		pIn->getWindowPtr()->FlushKeyQueue();
		pOut->ClearStatusBar();
		// pIn->getWindowPtr()->StoreImage(gate, RectULX, RectULY, 50, 50);

		/*pIn->getWindowPtr()->DrawImage(empty, RectULX, RectULY - 20, 50, 70);
		pIn->getWindowPtr()->SetPen(BLUE, 3);
		for (int i = RectULX + 10; i < RectULX + 50; i += 15)
		{
		for (int j = RectULY - 20; j <RectULY + 50; j += 15)


		pIn->getWindowPtr()->DrawPixel(i, j);

		}*/
		pIn->getWindowPtr()->StoreImage(screenimage, 0, 0, UI.width, UI.height);
		pIn->getWindowPtr()->StoreImage(toolbarimage, 0, 0, UI.width, UI.ToolBarHeight);
		// Loop until there escape is pressed
		pOut->getpointerwind()->SetBuffering(true);
		while (pIn->getWindowPtr()->GetKeyPress(cKeyData) != ASCII)
		{
			/*pIn->getWindowPtr()->SetPen(WHITE);
			pIn->getWindowPtr()->SetBrush(WHITE);
			pIn->getWindowPtr()->DrawRectangle(0, 0, pIn->getWindowPtr()->GetWidth() - 1, pIn->getWindowPtr()->GetHeight() - 1);
			*/

			// Dragging voodoo
			if (bDragging == false)
			{
				if (pIn->getWindowPtr()->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN)
				{
					if (((iX > RectULX) && (iX < (RectULX + RectWidth))) && ((iY > RectULY) && (iY < (RectULY + Rectlength))))
					{
						bDragging = true;
						iXOld = iX; iYOld = iY;
					}
				}
			}
			else {
				if (pIn->getWindowPtr()->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP)
				{
					bDragging = false;
				}
				else
				{
					if (iX != iXOld)
					{
						RectULX = RectULX + (iX - iXOld);
						iXOld = iX;
					}
					if (iY != iYOld)
					{
						RectULY = RectULY + (iY - iYOld);
						iYOld = iY;
					}
				}

			}

			// Draw rectangle

			/* testWindow.SetPen(ORANGE);
			testWindow.SetBrush(ORANGE);
			testWindow.DrawRectangle(RectULX, RectULY, RectULX + RectWidth, RectULY + RectWidth);
			*/
			xx = RectULX;
			yy = RectULY;
			if (xx % 15 > 7)
				xx = xx / 15 + 1;
			else
				xx = xx / 15;


			if (yy % 15 > 7)
				yy = yy / 15 + 1;
			else
				yy = yy / 15;
			xx *= 15; yy *= 15;
			// temp->setnew_grafinfo_for_drag(xx, yy);
			goodarea = true;
			pIn->getWindowPtr()->DrawImage(screenimage, 0, 0, UI.width, UI.height);
			for (int i = 0; i < pManager->selected_components.size(); i++)
			{
				int xcomp = xx + pManager->selected_components[i].second.first;
				int ycomp = yy + pManager->selected_components[i].second.second;

				if (!pManager->check_matrix(xcomp, ycomp))
				{



					//	pIn->getWindowPtr()->SetPen(BLUE, 1);
					//	pIn->getWindowPtr()->DrawLine(pManager->selected_components[i].first.first, pManager->selected_components[i].first.second, xcomp, ycomp);
					kkk.x1 = xcomp - 25;
					kkk.y1 = ycomp - 25;
					selectedcomp[i]->move(pOut, kkk);
					//pIn->getWindowPtr()->DrawImage(gate, xx - 25, yy - 25, 50, 50);

					pIn->getWindowPtr()->SetPen(RED, 3);
					pIn->getWindowPtr()->DrawRectangle(xcomp - 25, ycomp - 25, xcomp + 25, ycomp + 25, FRAME);
					pIn->getWindowPtr()->DrawImage(toolbarimage, 0, 0, UI.width, UI.ToolBarHeight);
					goodarea = false;

				}
				else
				{
					//	pIn->getWindowPtr()->DrawImage(screenimage, 0, 0, UI.width, UI.height);
					//pIn->getWindowPtr()->SetPen(BLUE, 1);
					//	pIn->getWindowPtr()->DrawLine(pManager->selected_components[i].first.first, pManager->selected_components[i].first.second, xcomp, ycomp);
					kkk.x1 = xcomp - 25;
					kkk.y1 = ycomp - 25;
					selectedcomp[i]->move(pOut, kkk);
					//pIn->getWindowPtr()->DrawImage(gate, xx - 25, yy - 25, 50, 50);
					pIn->getWindowPtr()->DrawImage(toolbarimage, 0, 0, UI.width, UI.ToolBarHeight);

				}

				if (goodarea)
					pOut->PrintMsg("Press Enter to end move ");
				else
					pOut->PrintMsg("this area is not empty !!! ");


			}
			pIn->getWindowPtr()->UpdateBuffer();
			//testWindow.DrawImage(getname, RectULX, RectULY, RectWidth, RectWidth);
			//// Draw some info 
			//testWindow.SetPen(BLACK);
			//testWindow.DrawString(5, 5, "MouseState Demo. Drag the orange box around. Press \"Escape\" to quit");

			// Update the screen buffer
			//pOut->CreateDesignToolBar();
			//pOut->CreateStatusBar();


			//pManager->UpdateInterface();



		}

		pIn->getWindowPtr()->SetBuffering(false);



		if (!goodarea)
		{

			pOut->PrintMsg("this area is not empty !!! the gate(s) returns to it's first position ");
			for (int i = 0; i < pManager->selected_components.size(); i++)
			{
				kkk.x1 = pManager->selected_components[i].first.first - 25;
				kkk.y1 = pManager->selected_components[i].first.second - 25;
				selectedcomp[i]->setnew_grafinfo_for_drag(pManager->selected_components[i].first.first, pManager->selected_components[i].first.second);

				//	temp->setnew_grafinfo_for_drag(xold, yold);
				selectedcomp[i]->updateMatrix(kkk, selectedcomp[i]->getid(), selectedcomp[i]->gettype());
				pair<pair<int, int>, pair<int, int>>emp;
				emp.second.first = emp.first.first = pManager->selected_components[i].first.first;
				emp.second.second = emp.first.second = pManager->selected_components[i].first.second;

				oldandnew[i] = emp;
				draw_new_connection_for_gate(selectedcomp[i], i);
				pManager->selected_components[i].first.first -= 25;
				pManager->selected_components[i].first.second -= 25;
			}
			pIn->getWindowPtr()->DrawImage(screenimage, 0, 0, UI.width, UI.height);
			//	pIn->getWindowPtr()->DrawImage(gate, xold - 25, yold - 25, 50, 50);
			//	pIn->getWindowPtr()->DrawImage(toolbarimage, 0, 0, UI.width, UI.ToolBarHeight);

		}
		else
		{

			for (int i = 0; i < pManager->selected_components.size(); i++)
			{
				kkk.x1 = xx + pManager->selected_components[i].second.first - 25;
				kkk.y1 = yy + pManager->selected_components[i].second.second - 25;

				selectedcomp[i]->setnew_grafinfo_for_drag(xx + pManager->selected_components[i].second.first, yy + pManager->selected_components[i].second.second);

				//	temp->setnew_grafinfo_for_drag(xold, yold);
				selectedcomp[i]->updateMatrix(kkk, selectedcomp[i]->getid(), selectedcomp[i]->gettype());
				pair<pair<int, int>, pair<int, int>>emp;
				emp.first.first = pManager->selected_components[i].first.first;
				emp.first.second = pManager->selected_components[i].first.second;
				emp.second.first = xx + pManager->selected_components[i].second.first;
				emp.second.second = yy + pManager->selected_components[i].second.second;

				oldandnew[i] = emp;
				draw_new_connection_for_gate(selectedcomp[i], i);

				pManager->selected_components[i].first.first = pManager->selected_components[i].second.first - 25;
				pManager->selected_components[i].first.second = pManager->selected_components[i].second.second - 25;
			}

		}

		/*	pIn->getWindowPtr()->SetPen(WHITE);
		pIn->getWindowPtr()->SetBrush(WHITE);
		pIn->getWindowPtr()->DrawRectangle(0, 0, pIn->getWindowPtr()->GetWidth() - 1, pIn->getWindowPtr()->GetHeight() - 1);
		pOut->CreateDesignToolBar();
		pOut->CreateStatusBar();




		*/



	}
	pManager->UpdateInterface();


	pIn->getWindowPtr()->FlushMouseQueue();
	///hebaaaaaaaa
	pManager->selected_components.clear();

	pManager->change_ALL_to_UnHI();
}

void Move::delete_gate_conection_from_bath_matrix(Component * temp)
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo g;
	vector <pair<int, int >> subdelete;//b5azen feeh el path mn awel el source l7ad el cdt

	g.x1 = g.x2 = g.y1 = g.y2 = 100;     // mlhom4 lzma 
	if (!(dynamic_cast<LED*>(temp)))   // kda 2na hdlt 2l output l7d 2wl cdt t2ablni 
	{
		int fanout_no;
		Connection ** connections;
		if (dynamic_cast<Gate*>(temp))
		{
			if ((dynamic_cast<Gate*>(temp))->get_OutputPin() != NULL) ///////////////feryal
			{
				fanout_no = (dynamic_cast<Gate*>(temp))->get_OutputPin()->get_m_Conn();
				connections = (dynamic_cast<Gate*>(temp))->get_OutputPin()->get_m_Connections();
			}
		}
		else if ((dynamic_cast<Switch*>(temp)))
			if ((dynamic_cast<Switch*>(temp))->get_OutputPin() != NULL) ///////////////feryal
			{
				fanout_no = (dynamic_cast<Switch*>(temp))->get_OutputPin()->get_m_Conn();
				connections = (dynamic_cast<Switch*>(temp))->get_OutputPin()->get_m_Connections();
			}

		for (int i = 0; i < fanout_no; i++)
		{
			if (i == 0)
			{
				//if (ApplicationManager::screenMatrix[connections[i]->path[1].second][connections[i]->path[1].second].first == ApplicationManager::screenMatrix[connections[i]->path[connections[i]->path.size() - 2].second][connections[i]->path[connections[i]->path.size() - 2].second].first)
				if (fanout_no == 1)
				{
					connections[i]->delete_from_Matrix(g);
					pOut->Clear_Connection_from_D_A(connections[i]->path);
					pair<int, int > first_point = make_pair(connections[i]->path[0].first, connections[i]->path[0].second);
					connections[i]->path.clear();
					connections[i]->path.push_back(first_point);

				}
				else
				{
					int j;
					for (j = connections[i]->path.size() - 1; j >= 0; j--)
					{
						if (ApplicationManager::screenMatrix[connections[i]->path[j].second][connections[i]->path[j].first].second != "cdt")
						{
							subdelete.push_back(make_pair(connections[i]->path[j].first, connections[i]->path[j].second));
							connections[i]->path.erase(connections[i]->path.begin() + connections[i]->path.size() - 1); /////feryal check

						}
						else
						{
							subdelete.push_back(make_pair(connections[i]->path[j].first, connections[i]->path[j].second));

							break;
						}
					}
					connections[i]->delete_from_matrix_b_path(subdelete);
					pOut->Clear_Connection_from_D_A(subdelete);

				}


			}

			else
			{
				subdelete.clear();
				int j;
				for (j = connections[i]->path.size() - 1; j >= 0; j--)
				{
					if (ApplicationManager::screenMatrix[connections[i]->path[j].second][connections[i]->path[j].first].second != "cdt")
					{
						subdelete.push_back(make_pair(connections[i]->path[j].first, connections[i]->path[j].second));
						connections[i]->path.erase(connections[i]->path.begin() + connections[i]->path.size() - 1);

					}
					else
					{
						subdelete.push_back(make_pair(connections[i]->path[j].first, connections[i]->path[j].second));

						break;
					}
				}
				//connections[i]->delete_from_matrix_b_path(subdelete);

			}





		}


	}

	// 5lst 2l output :D el7 
	// n5o4 3lla 2l input b2a 

	if (!(dynamic_cast<LED*>(temp)) && !(dynamic_cast<Switch*>(temp)))
	{

		InputPin ** inputpin;
		Connection * connection;
		subdelete.clear();
		int no_of_inputs = (dynamic_cast<Gate*>(temp))->get_InputsN();
		for (int i = 0; i < no_of_inputs; i++)
		{
			subdelete.clear();

			if ((dynamic_cast<Gate*>(temp))->get_arr_InputPins() != NULL)
			{

				if ((dynamic_cast<Gate*>(temp))->get_arr_InputPins()[i]->get_pConnect() != NULL)
				{
					connection = (dynamic_cast<Gate*>(temp))->get_arr_InputPins()[i]->get_pConnect();
					reverse(connection->path.begin(), connection->path.end());
					//a5er no2ta is the source 
					pair < int, int> a5r_no2ta = make_pair(connection->path[0].first, connection->path[0].second);
					//first no2ta is the destination
					pair < int, int> first_no2ta = make_pair(connection->path[connection->path.size() - 1].first, connection->path[connection->path.size() - 1].second);

					int j;
					for (j = connection->path.size() - 1; j >= 0; j--)
					{
						if (ApplicationManager::screenMatrix[connection->path[j].second][connection->path[j].first].second != "cdt")
						{
							subdelete.push_back(make_pair(connection->path[j].first, connection->path[j].second));
							connection->path.erase(connection->path.begin() + connection->path.size() - 1);

						}
						else
						{
							subdelete.push_back(make_pair(connection->path[j].first, connection->path[j].second));

							break;
						}
					}
					if (connection->path.size() == 0)
						connection->path.push_back(a5r_no2ta); //source of this connection

					connection->delete_from_matrix_b_path(subdelete);

					pOut->Clear_Connection_from_D_A(subdelete);

					//connection->path.push_back(a5r_no2ta);

				}



			}


		}
	}
	else if ((dynamic_cast<LED*>(temp)))
	{
		subdelete.clear();

		Connection * connection;
		if ((dynamic_cast<LED*>(temp))->get_m_InputPin() != NULL)
		{
			connection = (dynamic_cast<LED*>(temp))->get_m_InputPin()->get_pConnect();
			reverse(connection->path.begin(), connection->path.end());
			pair < int, int> a5r_no2ta = make_pair(connection->path[0].first, connection->path[0].second);
			pair < int, int> first_no2ta = make_pair(connection->path[connection->path.size() - 1].first, connection->path[connection->path.size() - 1].second);

			int j;
			for (j = connection->path.size() - 1; j >= 0; j--)
			{
				if (ApplicationManager::screenMatrix[connection->path[j].second][connection->path[j].first].second != "cdt")
				{
					subdelete.push_back(make_pair(connection->path[j].first, connection->path[j].second));
					connection->path.erase(connection->path.begin() + connection->path.size() - 1);

				}
				else
				{
					subdelete.push_back(make_pair(connection->path[j].first, connection->path[j].second));

					break;
				}
			}
			if (connection->path.size() == 0)
				connection->path.push_back(a5r_no2ta);
			connection->delete_from_matrix_b_path(subdelete);
			pOut->Clear_Connection_from_D_A(subdelete);

			//	connection->path.push_back(a5r_no2ta);   // 2a5r no2ta d hbo4ha 3l4an wna brsm 2l 5t 2l gdid hrsm mnha b3d m3ml 7aga kda t2oli 2na hrsm mn 2nhi input "24ta "



		}


	}









}

void Move::draw_new_connection_for_gate(Component * temp, int index)
{
	vector <pair<int, int>>path_gdid;
	if ((dynamic_cast<Gate*>(temp)))
	{
		int fanout_no;
		Connection ** connections;
		if ((dynamic_cast<Gate*>(temp))->get_OutputPin() != 0)
		{
			GraphicsInfo g;
			fanout_no = (dynamic_cast<Gate*>(temp))->get_OutputPin()->get_m_Conn();
			if (fanout_no != 0)
			{
				connections = (dynamic_cast<Gate*>(temp))->get_OutputPin()->get_m_Connections();
				if (connections[0] != NULL)
				{
					g.x1 = (oldandnew[index].second.first + 30) / 15; //output pin coordinates(src)
					g.y1 = (oldandnew[index].second.second) / 15; //output pin coordinates(src)
					g.x2 = connections[0]->path[connections[0]->path.size() - 1].first; //either dst pin or cdt point
					g.y2 = connections[0]->path[connections[0]->path.size() - 1].second; //either dst pin or cdt point
					path_gdid = connections[0]->choose_path_return_path(g);
					if (path_gdid[0].first == g.x1 && path_gdid[0].second == g.y1)
						std::reverse(path_gdid.begin(), path_gdid.end());

					connections[0]->updateMatrix_CONNECTION(path_gdid);

					for (int i = 0; i < fanout_no; i++)
					{
						for (int j = 0; j < path_gdid.size(); j++)
							connections[i]->path.push_back(path_gdid[j]);


					}

				}
			}
		}



	}
	else if ((dynamic_cast<Switch*>(temp)))
	{

		int fanout_no;
		Connection ** connections;
		if ((dynamic_cast<Switch*>(temp))->get_OutputPin() != 0)
		{
			GraphicsInfo g;
			fanout_no = (dynamic_cast<Switch*>(temp))->get_OutputPin()->get_m_Conn();
			if (fanout_no != 0)
			{
				connections = (dynamic_cast<Switch*>(temp))->get_OutputPin()->get_m_Connections();
				if (connections[0] != NULL)
				{
					g.x1 = (oldandnew[index].second.first + 30) / 15; //output pin coordinates(src)
					g.y1 = (oldandnew[index].second.second) / 15; //output pin coordinates(src)
					g.x2 = connections[0]->path[connections[0]->path.size() - 1].first; //either dst pin or cdt point
					g.y2 = connections[0]->path[connections[0]->path.size() - 1].second; //either dst pin or cdt point
					path_gdid = connections[0]->choose_path_return_path(g);
					if (path_gdid[0].first == g.x1 && path_gdid[0].second == g.y1)
						std::reverse(path_gdid.begin(), path_gdid.end());

					connections[0]->updateMatrix_CONNECTION(path_gdid);

					for (int i = 0; i < fanout_no; i++)
					{
						for (int j = 0; j < path_gdid.size(); j++)
							connections[i]->path.push_back(path_gdid[j]);


					}

				}
			}
		}



	}

	//5lsna el output nshof el input b2a :D

	if ((dynamic_cast<Gate*>(temp)))
	{
		InputPin ** inputpin;
		Connection * connection;
		path_gdid.clear();
		int no_of_inputs = (dynamic_cast<Gate*>(temp))->get_InputsN();
		for (int i = 0; i < no_of_inputs; i++)
		{
			path_gdid.clear();

			if ((dynamic_cast<Gate*>(temp))->get_arr_InputPins() != 0)
			{

				if ((dynamic_cast<Gate*>(temp))->get_arr_InputPins()[i]->get_pConnect() != 0)
				{
					connection = (dynamic_cast<Gate*>(temp))->get_arr_InputPins()[i]->get_pConnect();

					if (no_of_inputs == 1)
					{
						GraphicsInfo g;
						g.x1 = (oldandnew[index].second.first - 30) / 15;
						g.y1 = (oldandnew[index].second.second) / 15;
						g.x2 = connection->path[connection->path.size() - 1].first;
						g.y2 = connection->path[connection->path.size() - 1].second;
						path_gdid = connection->choose_path_return_path(g);
						if (path_gdid[0].first == g.x1 && path_gdid[0].second == g.y1)
							std::reverse(path_gdid.begin(), path_gdid.end());
						connection->updateMatrix_CONNECTION(path_gdid);

					}
					else // no of inputs = 2 or 3
					{
						if (connection->getPinNum() == 0) //upper pin
						{
							GraphicsInfo g;
							g.x1 = (oldandnew[index].second.first - 30) / 15;
							g.y1 = (oldandnew[index].second.second - 15) / 15;
							g.x2 = connection->path[connection->path.size() - 1].first;
							g.y2 = connection->path[connection->path.size() - 1].second;
							path_gdid = connection->choose_path_return_path(g);
							if (path_gdid[0].first == g.x1 && path_gdid[0].second == g.y1)
								std::reverse(path_gdid.begin(), path_gdid.end());
							connection->updateMatrix_CONNECTION(path_gdid);
						}
						else if (connection->getPinNum() == 1) //lower
						{
							GraphicsInfo g;
							g.x1 = (oldandnew[index].second.first - 30) / 15;
							g.y1 = (oldandnew[index].second.second + 15) / 15;
							g.x2 = connection->path[connection->path.size() - 1].first;
							g.y2 = connection->path[connection->path.size() - 1].second;
							path_gdid = connection->choose_path_return_path(g);
							if (path_gdid[0].first == g.x1 && path_gdid[0].second == g.y1)
								std::reverse(path_gdid.begin(), path_gdid.end());
							connection->updateMatrix_CONNECTION(path_gdid);
						}
						else //pinNum==2 //middle pin if exist
						{
							GraphicsInfo g;
							g.x1 = (oldandnew[index].second.first - 30) / 15;
							g.y1 = (oldandnew[index].second.second) / 15;
							g.x2 = connection->path[connection->path.size() - 1].first;
							g.y2 = connection->path[connection->path.size() - 1].second;
							path_gdid = connection->choose_path_return_path(g);
							if (path_gdid[0].first == g.x1 && path_gdid[0].second == g.y1)
								std::reverse(path_gdid.begin(), path_gdid.end());
							connection->updateMatrix_CONNECTION(path_gdid);
						}
					}
					//connection->path.erase(connection->path.begin() + connection->path.size() - 1);
					for (int j = 0; j < path_gdid.size(); j++)
						connection->path.push_back(path_gdid[j]);
					reverse(connection->path.begin(), connection->path.end());



				}
			}
		}

	}
	else if ((dynamic_cast<LED*>(temp)))
	{
		path_gdid.clear();
		Connection * connection;
		if ((dynamic_cast<LED*>(temp))->get_m_InputPin() != 0)
		{
			if ((dynamic_cast<LED*>(temp))->get_m_InputPin()->get_pConnect() != NULL)
			{
				connection = (dynamic_cast<LED*>(temp))->get_m_InputPin()->get_pConnect();
				GraphicsInfo g;
				g.x1 = (oldandnew[index].second.first) / 15;
				g.y1 = (oldandnew[index].second.second + 30) / 15;
				g.x2 = connection->path[connection->path.size() - 1].first;
				g.y2 = connection->path[connection->path.size() - 1].second;
				path_gdid = connection->choose_path_return_path(g);
				connection->updateMatrix_CONNECTION(path_gdid);

				//connection->path.erase(connection->path.begin() + connection->path.size() - 1);
				for (int i = 0; i < path_gdid.size(); i++)
					connection->path.push_back(path_gdid[i]);
				reverse(connection->path.begin(), connection->path.end());
			}

		}





	}

}





void Move::Undo()
{
}

void Move::Redo()
{
}

Move::Move(ApplicationManager *pApp) : Action(pApp)
{
}


Move::~Move()
{
}

