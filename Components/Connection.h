#pragma once
#ifndef _CONNECTION_H
#define _CONNECTION_H
#include <iostream>
using namespace std;

#include "InputPin.h"
#include "OutputPin.h"
#include<vector>
#include<queue>
#include<map>
#include "Component.h"


#include "..\ApplicationManager.h"
class Input;
class Output;
class Component;
class  OutputPin;
class ApplicationManager;
class InputPin;

class Connection : public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	int		DestPin;		//The Input pin to which this connection is linked
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
	OutputPin* oldSrcPin;
	InputPin* oldDstPin;
	OutputPin* SrcPin_redo;
	InputPin* DstPin_redo;
	OutputPin* SrcPin_undo;
	InputPin* DstPin_undo;
	pair<int, int> Dst;
	pair<int, int> source;

	bool mtfr3;
	pair<int, int>tafree3a;
	vector <std::pair<int, int>> oldpath;
	vector <std::pair<int, int>> oldsub_path;
public:
	vector <std::pair<int, int>> path; //ha7tafez b kol el points bta3t el connection
	vector <std::pair<int, int>> sub_path;
	vector <std::pair<int, int>> sub_path_redo;
	vector <std::pair<int, int>> path_redo;
	vector <std::pair<int, int>> sub_path_undo;
	vector <std::pair<int, int>> path_undo;
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin);

	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself
	virtual void updateMatrix(GraphicsInfo, int, string) {}
	virtual void updateMatrix_CONNECTION(vector<pair<int, int >>);
	void Save(ofstream & out);
	Connection * load(string Typ, string Lbl, GraphicsInfo GInfo, int ID);
	virtual void delete_from_Matrix(GraphicsInfo);
	///hebaaaaaaaaaaaaaaa
	virtual void delete_from_Matrix_gdida();
	void choosePath(GraphicsInfo GfxInfo);

	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();

	virtual void move(Output *pOut, GraphicsInfo) {}

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	void setm_GfxInfo(GraphicsInfo G) { m_GfxInfo = G; }
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	void  delete_connection_from_gate(Output*pOut);
	void readd_connection_from_gate();
	void delete_connection_itself(Output*pOut);
	void Readd();
	void set_DstPair(pair<int, int > r_Dst);
	void set_sourcePair(pair<int, int > r_Dst);
	pair<int, int > get_dst_pair();
	pair<int, int > get_source_pair();
	//void Lazy_DeleteConnetion();
	pair<int, int> gettafree3a();
	bool getmtfr3();
	void settafree3a(pair<int, int>);

	void setmtfr3(bool r_mtfr3);       // aabdo w fatema 
	int noofcdt(pair<int, int > temp);

	int getPinNum() { return DestPin; }
	void SetPinNum(int r) { DestPin = r; }
	void help_redo();
	void help_undo();
	void Readd_redo();
	void Readd_undo();

	void delete_from_matrix_b_path(vector<pair<int, int>> r_path);

	vector<pair<int, int>> choose_path_return_path(GraphicsInfo GfxInfo);

};
#endif 

