#include "Inverter.h"



Inverter::Inverter(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	settype("Inverter");
}

void Inverter::Operate()
{
	//caclulate the output status as INverting the  input pin
	for (int i = 0; i < m_Inputs; i++)
	{
		m_OutputPin->setStatus(STATUS(!(m_InputPins[i]->getStatus())));
		
	}
	//Add you code here
}

/*void Inverter::Save(ofstream &out)
{
	out << this->gettype() << "\t" << this->getid() << "\t" << this->getlabel();
	out << "\t" << this->getm_GfxInfo().x1 / 15;
	out << "\t" << this->getm_GfxInfo().y1 / 15;
	out << "\t" << this->getm_GfxInfo().x2 / 15;
	out << "\t" << this->getm_GfxInfo().y2 / 15;

	out << endl;


}*/
// Function Draw
// Draws 2-input OR gate
void Inverter::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOT(m_GfxInfo, getHI());
	pOut->Clear_string_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1 - 20);
	pOut->Printstring_in_D_A(getlabel(), pOut, m_GfxInfo.x1, m_GfxInfo.y1 - 20);
}

//returns status of outputpin
int Inverter::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int Inverter::GetInputPinStatus(int n)
{
	return m_InputPins[0]->getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void Inverter::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[0]->setStatus(s);
}

#include"..\ApplicationManager.h"

void Inverter::updateMatrix(GraphicsInfo GInfo, int ID, string type) ///team 13    //zbt alid wltype hebaaaa
{
	int Cx = GInfo.x1 + UI.Inverter_Width / 2;
	int Cy = GInfo.y1 + UI.Inverter_Height / 2;

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
	ApplicationManager::screenMatrix[Cy][Cx + 1].first = ID;                            //the connections in the matrix //ta3deel heba w feryal 7-5
	ApplicationManager::screenMatrix[Cy][Cx + 1].second = "c_o";


	ApplicationManager::screenMatrix[Cy][Cx - 2].first = ID;
	ApplicationManager::screenMatrix[Cy][Cx - 2].second = "c_m";
	ApplicationManager::screenMatrix[Cy][Cx - 1].first = ID;
	ApplicationManager::screenMatrix[Cy][Cx - 1].second = "c_m";



}
void Inverter::delete_from_Matrix(GraphicsInfo GInfo)
{

	int Cx = GInfo.x1 + UI.Inverter_Width / 2;
	int Cy = GInfo.y1 + UI.Inverter_Height / 2;

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

void Inverter::move(Output * pOut, GraphicsInfo kkk)
{
	pOut->DrawNOT(kkk, true);

}
void Inverter::copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	Inverter *pA = new Inverter(GInfo, Inverter_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
}
void Inverter::cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	Inverter *pA = new Inverter(GInfo, Inverter_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
	/*pManager->Lazy_DeleteComponent(getid(), m_GfxInfo);
	pOut->Clear_Gate_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1);*/
}

void Inverter::Delete(Output*pOut)
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

			//m_InputPins[i]->get_pConnect()->setlazy_d(true); // 3mltha bl size bta3 al path


			//hna kont 3aiza andah fnk lazy delete connection aly fe al abb 
			//bs mnf3sh 3shan mfeesh pointer 3leeeh 
			//fmlt aly hy bt3mlo hna
			//m_InputPins[i]->get_pConnect()->delete_from_Matrix();  hnshoof baa lsa
			//m_InputPins[i]->set_oldpConnect(m_InputPins[i]->get_pConnect());
			//m_InputPins[i]->set_pConnect(NULL);   //mknash bnms7o
		}
	delete_from_Matrix(getgrahicsinfo());
}
void Inverter::Readd()
{
	updateMatrix(getgrahicsinfo(), getid(), gettype());
	m_OutputPin->readd_m_Connections();
	for (int i = 0; i < m_Inputs; i++)
		if (m_InputPins[i]->get_pConnect() == NULL&&m_InputPins[i]->get_oldpConnect() != NULL) //zyadt a7tyat
		{
			m_InputPins[i]->raddconnection();
		}
}
