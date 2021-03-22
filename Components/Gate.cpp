#include "Gate.h"
#include<fstream>
using namespace std;
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut)/*:m_OutputPin(r_FanOut)*/
{
	m_OutputPin = new OutputPin(r_FanOut);
	m_OutputPin->setComponent(this);
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin*[r_Inputs];
	
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	for (int i = 0; i < m_Inputs; i++)
		m_InputPins[i] = new InputPin;
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i]->setComponent(this);
}


void Gate::Save(ofstream &out)
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
Gate* Gate::load(string  Typ, string Lbl, GraphicsInfo Gfx, int ID)
{
	this->setID(ID);
	this->SetLbl(Lbl);
	this->updateMatrix(Gfx, ID, Typ);

	return this;

}

void Gate::set_input_pins_unvisted()
{
	for (int i = 0; i < m_Inputs; i++)
	{
		m_InputPins[i]->setvisited(false);
		m_InputPins[i]->setStatus(LOW);
	}

}

InputPin** Gate::get_arr_InputPins()
{
	return m_InputPins;
}

OutputPin* Gate::get_OutputPin()
{
	return m_OutputPin;
}

int Gate::get_InputsN()
{
	return m_Inputs;
}
void Gate::setoutputpinstatus(STATUS s)
{
	m_OutputPin->setStatus(s);
}
bool Gate::check_empty_Pin()
{
	if (m_OutputPin->get_m_Conn() == 0)
		return true;
	for (int i = 0; i < m_Inputs; i++)
		if (m_InputPins[i]->get_pConnect() == NULL)
			return true;
	return false;
}

bool Gate::check_calculated()
{
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i]->getvisited() == false)
			return false;
	}
	calculated = true;
	return true;
}
