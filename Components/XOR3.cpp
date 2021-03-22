#include "XOR3.h"

#include "..\ApplicationManager.h"

XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	settype("XOR3");
}


void XOR3::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	//caclulate the output status as the XNORing of the two input pins
	int x = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i]->getStatus() == HIGH)
			x++;
	}
	if (x % 2 == 0)
		m_OutputPin->setStatus(LOW);
	else
		m_OutputPin->setStatus(HIGH);

}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR3(m_GfxInfo, getHI());
	pOut->Clear_string_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1 - 20);
	pOut->Printstring_in_D_A(getlabel(), pOut, m_GfxInfo.x1, m_GfxInfo.y1 - 20);
}



void XOR3::updateMatrix(GraphicsInfo GInfo, int ID, string type) ///team 13    //zbt alid wltype hebaaaa
{
	int Cx = GInfo.x1 + UI.XOR3_Width / 2;
	int Cy = GInfo.y1 + UI.XOR3_Height / 2;

	Cy = Cy / 15;
	Cx = Cx / 15;
	for (int i = Cy - 3; i <= Cy + 2; i++)
	{
		for (int j = Cx - 2; j <= Cx + 2; j++)
		{
			ApplicationManager::screenMatrix[i][j].first = ID;
			ApplicationManager::screenMatrix[i][j].second = type;
		}
	}




	ApplicationManager::screenMatrix[Cy - 3][Cx - 1].first = -1;                            // the text in the matrix
	ApplicationManager::screenMatrix[Cy - 3][Cx - 1].second = "label";
	ApplicationManager::screenMatrix[Cy - 3][Cx].first = -1;
	ApplicationManager::screenMatrix[Cy - 3][Cx].second = "label";
	ApplicationManager::screenMatrix[Cy - 3][Cx + 1].first = -1;
	ApplicationManager::screenMatrix[Cy - 3][Cx + 1].second = "label";

	ApplicationManager::screenMatrix[Cy][Cx + 2].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy][Cx + 2].second = "c_o";
	ApplicationManager::screenMatrix[Cy][Cx + 1].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy][Cx + 1].second = "c_o";

	ApplicationManager::screenMatrix[Cy - 1][Cx - 2].first = ID;
	ApplicationManager::screenMatrix[Cy - 1][Cx - 2].second = "c_u";
	ApplicationManager::screenMatrix[Cy - 1][Cx - 1].first = ID;
	ApplicationManager::screenMatrix[Cy - 1][Cx - 1].second = "c_u";


	ApplicationManager::screenMatrix[Cy][Cx - 2].first = ID;
	ApplicationManager::screenMatrix[Cy][Cx - 2].second = "c_m";
	ApplicationManager::screenMatrix[Cy][Cx - 1].first = ID;
	ApplicationManager::screenMatrix[Cy][Cx - 1].second = "c_m";

	ApplicationManager::screenMatrix[Cy + 1][Cx - 2].first = ID;
	ApplicationManager::screenMatrix[Cy + 1][Cx - 2].second = "c_l";
	ApplicationManager::screenMatrix[Cy + 1][Cx - 1].first = ID;
	ApplicationManager::screenMatrix[Cy + 1][Cx - 1].second = "c_l";
}
void XOR3::delete_from_Matrix(GraphicsInfo GInfo)
{
	int Cx = GInfo.x1 + UI.XOR3_Width / 2;
	int Cy = GInfo.y1 + UI.XOR3_Height / 2;

	Cy = Cy / 15;
	Cx = Cx / 15;
	for (int i = Cy - 3; i <= Cy + 2; i++)
	{
		for (int j = Cx - 2; j <= Cx + 2; j++)
		{
			ApplicationManager::screenMatrix[i][j].first = 0;
			ApplicationManager::screenMatrix[i][j].second = "empty";
		}
	}

}


//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1]->getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1]->setStatus(s);
}
XOR3:: ~XOR3()
{
	delete_from_Matrix(m_GfxInfo);
}

void XOR3::move(Output * pOut, GraphicsInfo kkk)
{
	pOut->DrawXOR3(kkk, true);

}
void XOR3::copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	XOR3 *pA = new XOR3(GInfo, XOR3_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
}
void XOR3::cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	XOR3 *pA = new XOR3(GInfo, XOR3_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
	/*pManager->Lazy_DeleteComponent(getid(), m_GfxInfo);
	pOut->Clear_Gate_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1);*/
}

void XOR3::Delete(Output*pOut)
{
	//delete output connections

	m_OutputPin->delete_m_Connections();          //mknash bnms7o
	int j = 0;
	while (m_OutputPin->get_m_Conn() != 0)
	{
		//m_OutputPin->get_m_Connections()[i]->setlazy_d(true);    GWA DELETE M_CONNECTIONS
		if (m_OutputPin->get_m_Connections()[j]->getlazy_d() == false)
			m_OutputPin->get_m_Connections()[j]->delete_connection_itself(pOut);
		//lsa delete from matrix
		//j++;
	}

	for (int i = 0; i < m_Inputs; i++)
		if (m_InputPins[i]->get_pConnect() != NULL) //in case eny 3amlt cut bdon ma akon 3amla connections
		{
			m_InputPins[i]->set_oldpConnect();
			if (m_InputPins[i]->get_pConnect()->getlazy_d() == false)
			{

				m_InputPins[i]->get_pConnect()->delete_connection_itself(pOut);

			}

		}
	delete_from_Matrix(getgrahicsinfo());
}
void XOR3::Readd()
{
	updateMatrix(getgrahicsinfo(), getid(), gettype());
	m_OutputPin->readd_m_Connections();
	for (int i = 0; i < m_Inputs; i++)
		if (m_InputPins[i]->get_pConnect() == NULL&&m_InputPins[i]->get_oldpConnect() != NULL) //zyadt a7tyat
		{
			m_InputPins[i]->raddconnection();
		}
}
