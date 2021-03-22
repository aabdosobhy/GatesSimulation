#pragma once
//#include "Component.h"
#include"..\GUI\Output.h"
#include "InputPin.h"
class LED :
	public Component
{
protected:
	InputPin* m_InputPin;	//Input pin of the Gate
	bool ON; // led is lighted

public:
	static int lbl;
	LED();
	void Save(ofstream & out);
	Component * load(string Typ, string Lbl, GraphicsInfo Gfx, int ID);
	//void Save(ofstream & out);
	LED(const GraphicsInfo & r_GfxInfo);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	virtual void updateMatrix(GraphicsInfo GInfo, int ID, string type);
	virtual void delete_from_Matrix(GraphicsInfo);
	virtual int GetOutPinStatus(); 	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual ~LED();
	InputPin* get_m_InputPin();
	virtual void move(Output *pOut, GraphicsInfo kkk);
	virtual void copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2);

	virtual void cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2);
	virtual void Delete(Output*pOut);
	void Readd();

};

