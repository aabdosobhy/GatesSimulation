#ifndef _AND2_H
#define _AND2_H

/*
  Class AND2
  -----------
  represent the 2-input AND gate
*/

#include "Gate.h"
class ApplicationManager;
class AND2:public Gate
{
public:
	////leeh mafesh destructor???????????????
	AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	void updateMatrix(GraphicsInfo GInfo, int ID, string type);

	void delete_from_Matrix(GraphicsInfo GInfo);
	virtual void copy(ApplicationManager *pManager,int x, int y, vector<int>& iddones2);

	virtual void cut(ApplicationManager *pManager,int x, int y, vector<int>& iddones2);
	virtual void Delete(Output*pOut);
	void Readd();
	virtual void move(Output *pOut, GraphicsInfo kkk);

};

#endif