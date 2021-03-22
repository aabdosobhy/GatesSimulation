#include "Switch.h"
#include "..\ApplicationManager.h"
#include<fstream>
using namespace std;

int Switch:: lbl=0;
Switch::Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut)
{
	m_OutputPin = new OutputPin(r_FanOut);
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	string r = "S";
	lbl++;
	SetLbl(r+(char)(lbl+48));
	m_OutputPin->setComponent(this);
	settype("Switch");
	ON = false;
}


void Switch::Save(ofstream &out)
{
	out << this->gettype() << "\t" << this->getid() << "\t";
	if (this->getlabel() == "") out << "NULL";
	else out << this->getlabel();

	out << "\t" << this->getm_GfxInfo().x1;
	out << "\t" << this->getm_GfxInfo().y1;
	out << "\t" << this->getm_GfxInfo().x2;
	out << "\t" << this->getm_GfxInfo().y2;

	out << endl;


}

Switch * Switch::load(string Typ, string Lbl, GraphicsInfo Gfx, int ID)
{
	this->setID(ID);
	this->SetLbl(Lbl);
	this->updateMatrix(Gfx, ID, Typ);

	return this;

}

void Switch::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	if (m_OutputPin->getStatus() == HIGH)
		ON = true;
	else ON = false;
	//Add you code here
}


// Function Draw
// Draws Switch
void Switch::Draw(Output* pOut)
{
	if(ON)
		pOut->DrawSWITCHON(m_GfxInfo);
	//Call output class and pass gate drawing info to it.
	else pOut->DrawSWITCHOFF(m_GfxInfo, getHI());		///temporarly fatema
	pOut->Clear_string_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1 - 20);
	pOut->Printstring_in_D_A(getlabel(), pOut, m_GfxInfo.x1, m_GfxInfo.y1 - 20);
}

#include"..\ApplicationManager.h"

void Switch::updateMatrix(GraphicsInfo GInfo, int ID, string type) ///team 13    //zbt alid wltype hebaaaa
{
	int Cx = GInfo.x1 + UI.Switch_Width / 2;
	int Cy = GInfo.y1 + UI.Switch_Height / 2;

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
	ApplicationManager::screenMatrix[Cy][Cx ].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy][Cx ].second = "c_o";

	


}
void Switch::delete_from_Matrix(GraphicsInfo GInfo)
{
	int Cx = GInfo.x1 + UI.Switch_Width / 2;
	int Cy = GInfo.y1 + UI.Switch_Height / 2;

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
int Switch::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}

void Switch::setoutputpinstatus(STATUS s)
{
	m_OutputPin->setStatus(s);
}

void Switch::setInputPinStatus(int n, STATUS s)
{
	/////////l fn. by3ml 7aga fe mkan tane w inherated 3'sb 3ne :'(
	OutputPin m_InputPin(3);
	m_InputPin.setStatus(s);
}
//returns status of Inputpin #n
int Switch::GetInputPinStatus(int n)
{
	return -1;	//n starts from 1 but array index starts from 0.
}

Switch:: ~Switch()
{
	delete_from_Matrix(m_GfxInfo);
}

OutputPin * Switch::get_OutputPin()
{
	return m_OutputPin;
}

void Switch::move(Output * pOut, GraphicsInfo kkk)
{
	pOut->DrawSWITCHOFF(kkk, true);

}
void Switch::copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	Switch *pA = new Switch(GInfo, Switch_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
}
void Switch::cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	Switch *pA = new Switch(GInfo, Switch_FANOUT);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
	/*pManager->Lazy_DeleteComponent(getid(), m_GfxInfo);
	pOut->Clear_Gate_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1);*/
}

void Switch::Delete(Output*pOut)
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

	

		
	delete_from_Matrix(getgrahicsinfo());
}
void Switch::Readd()
{
	updateMatrix(getgrahicsinfo(), getid(), gettype());
	m_OutputPin->readd_m_Connections();
	
}
void Switch::change_status()
{
	if (m_OutputPin->getStatus() == LOW)
	{
		m_OutputPin->setStatus(HIGH);
		ON = true;
	}
	else {
		m_OutputPin->setStatus(LOW);
		ON = false;
	}

}
