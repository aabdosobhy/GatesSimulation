#pragma once
#include"..\GUI\Output.h"
#include "OutputPin.h"
#include "Component.h"

class Switch :
	public Component
{
protected:
	OutputPin* m_OutputPin;	//The switch output pin
	bool ON; // if true short circuit (O/P= HIGH)
public:
	//Switch( int r_FanOut);	////////////////msh 3arfa a3ml zero construtor wla no    
	/////TODOOOOO:
	///// fn. to turn on and off the switch
	 static int lbl;
	Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	void Save(ofstream & out);
	Switch * load(string Typ, string Lbl, GraphicsInfo Gfx, int ID);
	//void Save(ofstream & out);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	 //Draws 2-input gate
	virtual void updateMatrix(GraphicsInfo GInfo, int ID, string type);
	virtual void delete_from_Matrix(GraphicsInfo);
	virtual int GetOutPinStatus();
	void setoutputpinstatus(STATUS s);
	int GetInputPinStatus(int n);	//returns status of outputpin if LED, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual ~Switch();
	OutputPin* get_OutputPin();
	virtual void move(Output *pOut, GraphicsInfo kkk);
	virtual void copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2);

	virtual void cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2);
	virtual void Delete(Output*pOut);
	void Readd();

	void change_status();


};

