#include "AND2.h"
#include"..\ApplicationManager.h"
AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	settype("AND2");
}


void AND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	STATUS x=HIGH;
	for (int i = 0; i < m_Inputs; i++)
		{
			x = STATUS(x&m_InputPins[i]->getStatus());
		}
	m_OutputPin->setStatus(x);
	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawAND2(m_GfxInfo,getHI()); //feryal
	pOut->Clear_string_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1 - 20);
	pOut->Printstring_in_D_A(getlabel(), pOut, m_GfxInfo.x1, m_GfxInfo.y1 - 20);
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1]->getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1]->setStatus(s);
}

#include"../ApplicationManager.h"
void AND2::updateMatrix(GraphicsInfo GInfo, int ID, string type) ///team 13    //zbt alid wltype hebaaaa
{
	int Cx = GInfo.x1 + UI.AND2_Width / 2;
	int Cy = GInfo.y1 + UI.AND2_Height / 2;

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

	ApplicationManager::screenMatrix[Cy-3][Cx-1].first = -1;                            // the text in the matrix
	ApplicationManager::screenMatrix[Cy - 3][Cx - 1].second = "label";
	ApplicationManager::screenMatrix[Cy - 3][Cx].first = -1;
	ApplicationManager::screenMatrix[Cy - 3][Cx ].second = "label";
	ApplicationManager::screenMatrix[Cy - 3][Cx + 1].first = -1;
	ApplicationManager::screenMatrix[Cy - 3][Cx + 1].second = "label";

	ApplicationManager::screenMatrix[Cy][Cx +2].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy ][Cx +2].second = "c_o";
	ApplicationManager::screenMatrix[Cy][Cx + 1].first = ID;                            //the connections in the matrix //ta3deel heba w feryal 7-5
	ApplicationManager::screenMatrix[Cy][Cx + 1].second = "c_o";

	ApplicationManager::screenMatrix[Cy - 1][Cx - 2].first = ID;
	ApplicationManager::screenMatrix[Cy - 1][Cx - 2].second = "c_u";
	ApplicationManager::screenMatrix[Cy - 1][Cx - 1].first = ID;
	ApplicationManager::screenMatrix[Cy - 1][Cx - 1].second = "c_u";

	ApplicationManager::screenMatrix[Cy +1][Cx - 2].first = ID;
	ApplicationManager::screenMatrix[Cy + 1][Cx - 2].second = "c_l";
	ApplicationManager::screenMatrix[Cy + 1][Cx - 1].first = ID;
	ApplicationManager::screenMatrix[Cy + 1][Cx - 1].second = "c_l";
		
}
void AND2::delete_from_Matrix(GraphicsInfo GInfo)
{
	/*
	for (int j = GInfo.y1 - 20; j < GInfo.y2 + 5; j++)
		for (int i = GInfo.x1 - 5; i < GInfo.x2 + 5; i++)
		{
			ApplicationManager::screenMatrix[j][i].first = 0;/// ID needed to be identified
			ApplicationManager::screenMatrix[j][i].second = "empty";/// ID needed to be identified
		}
	*/
	int Cx = GInfo.x1 + UI.AND2_Width / 2;
	int Cy = GInfo.y1 + UI.AND2_Height / 2;

	Cy = Cy / 15;
	Cx = Cx / 15;
	for (int i = Cy - 3; i <= Cy + 2; i++)
	{
		for (int j = Cx - 2; j <= Cx + 2; j++)
		{
			ApplicationManager::screenMatrix[i][j].first =0;
			ApplicationManager::screenMatrix[i][j].second = "empty"; 
		}
	}


}

void AND2::copy(ApplicationManager *pManager,int x,int y, vector<int>& iddones2)
{
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x+50;
	GInfo.y2 = y+50;
	AND2 *pA = new AND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
}
void AND2::cut(ApplicationManager *pManager,int x,int y, vector<int>& iddones2)
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	AND2 *pA = new AND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
	/*pManager->Lazy_DeleteComponent(getid(), m_GfxInfo);
	pOut->Clear_Gate_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1);*/
}

void AND2::Delete(Output*pOut)
{
	//delete output connections
	
	m_OutputPin->delete_m_Connections();          //mknash bnms7o
	int j = 0;
	while( m_OutputPin->get_m_Conn()!=0)
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
void AND2::Readd()
{
	updateMatrix(getgrahicsinfo(), getid(), gettype());
	m_OutputPin->readd_m_Connections();
	for (int i = 0; i < m_Inputs; i++)
		if (m_InputPins[i]->get_pConnect() == NULL&&m_InputPins[i]->get_oldpConnect()!=NULL) //zyadt a7tyat
		{
			m_InputPins[i]->raddconnection();
		}
}
void AND2::move(Output * pOut, GraphicsInfo kkk)
{

	pOut->DrawAND2(kkk, true);
}
