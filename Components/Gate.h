#ifndef _GATE_H
#define _GATE_H

#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/

class Gate:public Component
{
protected:
	InputPin** m_InputPins;	//Array of input pins of the Gate
	OutputPin* m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.

public:
	Gate(int r_Inputs, int r_FanOut);
	void Save(ofstream & out);
	Gate * load(string Typ, string Lbl, GraphicsInfo Gfx, int ID);
	void set_input_pins_unvisted();
	InputPin** get_arr_InputPins();
	OutputPin* get_OutputPin();
	int get_InputsN();
	void setoutputpinstatus(STATUS s);
	virtual void move(Output *pOut, GraphicsInfo) {}
	bool check_empty_Pin(); //if returned true then there is an input pin with no connection
	virtual bool check_calculated();

};

#endif
