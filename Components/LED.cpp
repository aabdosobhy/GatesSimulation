#include "LED.h"
#include"Connection.h"
//#include "..\ApplicationManager.h"//malosh lazma el include da
#include<fstream>
using namespace std;

int LED::lbl = 0;
LED::LED()
{
	string r = "L";
	lbl++;
	SetLbl(r + (char)(lbl + 48));
}
void LED::Save(ofstream &out)
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

Component * LED::load(string Typ, string Lbl, GraphicsInfo Gfx, int ID)
{
	this->setID(ID);
	this->SetLbl(Lbl);
	this->updateMatrix(Gfx, ID, Typ);

	return this;

}


LED::LED(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	settype("LED");
	m_InputPin = new InputPin;
	m_InputPin->setComponent(this);
	ON = false;
	string r = "L";
	lbl++;
	SetLbl(r + (char)(lbl + 48));
}


void LED::Operate()
{
	// changes the LED into ON if input Status is HIGH 
	if (m_InputPin->getStatus() == HIGH)
		ON = true;
	else ON = false;
	//Add you code here
}


// Function Draw
// Draws LED
void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (ON)
		pOut->DrawLED_sim(m_GfxInfo,false);
	else  pOut->DrawLED(m_GfxInfo, getHI());
	pOut->Clear_string_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1 - 20);
	pOut->Printstring_in_D_A(getlabel(), pOut, m_GfxInfo.x1, m_GfxInfo.y1 - 20);
}


void LED::updateMatrix(GraphicsInfo GInfo, int ID, string type) ///team 13    //zbt alid wltype hebaaaa
{
	int Cx = GInfo.x1 + UI.LED_Width / 2;
	int Cy = GInfo.y1 + UI.LED_Height / 2;

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

	ApplicationManager::screenMatrix[Cy + 2][Cx].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy + 2][Cx].second = "c_u";
	ApplicationManager::screenMatrix[Cy + 1][Cx].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy + 1][Cx].second = "c_u";
	ApplicationManager::screenMatrix[Cy ][Cx].first = ID;                            //the connections in the matrix 
	ApplicationManager::screenMatrix[Cy ][Cx].second = "c_u";

}
void LED::delete_from_Matrix(GraphicsInfo GInfo)
{
	int Cx = GInfo.x1 + UI.LED_Width / 2;
	int Cy = GInfo.y1 + UI.LED_Height / 2;

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
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	return m_InputPin->getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin->setStatus(s);
}
LED:: ~LED()
{
	delete_from_Matrix(m_GfxInfo);
}

InputPin * LED::get_m_InputPin()
{
	return m_InputPin;
}

void LED::move(Output * pOut, GraphicsInfo kkk)
{
	pOut->DrawLED(kkk, true);

}
void LED::copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	LED *pA = new LED(GInfo);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
}
void LED::cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo;
	GInfo.x1 = x;
	GInfo.y1 = y;
	GInfo.x2 = x + 50;
	GInfo.y2 = y + 50;
	LED *pA = new LED(GInfo);
	pManager->AddComponent(pA);
	pA->updateMatrix(GInfo, pA->getid(), pA->gettype());
	iddones2.push_back(pA->getid());
	/*pManager->Lazy_DeleteComponent(getid(), m_GfxInfo);
	pOut->Clear_Gate_from_D_A(m_GfxInfo.x1, m_GfxInfo.y1);*/
}

void LED::Delete(Output*pOut)
{
	//delete input connections

		if (m_InputPin->get_pConnect() != NULL) //in case eny 3amlt cut bdon ma akon 3amla connections
		{
			m_InputPin->set_oldpConnect();
			if (m_InputPin->get_pConnect()->getlazy_d() == false)
			{

				m_InputPin->get_pConnect()->delete_connection_itself(pOut);

			}

		}
	delete_from_Matrix(getgrahicsinfo());
}
void LED::Readd()
{
	updateMatrix(getgrahicsinfo(), getid(), gettype());
		if (m_InputPin->get_pConnect() == NULL&&m_InputPin->get_oldpConnect() != NULL) //zyadt a7tyat
		{
			m_InputPin->raddconnection();
		}
}
