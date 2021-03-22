#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"          
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class ApplicationManager;
class Component
{
private:
	string m_Label;
	int id;
	static int last_id;
	string type;
	bool HI; //feryal needed for select action////////////////////
	bool lazy_deleted;
	string last_label;  //for the label of connections only 
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	//GraphicsInfo label_GfxInfo;  ////The parameters required to draw a label hebaaaaaaaaaaaa
	bool calculated; //ready to be calculated simulation mode (needed to check if there is sequential)

public:
	Component(const GraphicsInfo &r_GfxInfo,string type="notype",string label=""); //zwdt altype,label
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	virtual void updateMatrix(GraphicsInfo,  int, string) =0; //team 13 ///HEBAAA RG3THAAAAAAAAA
	virtual void updateMatrix_CONNECTION(vector<pair<int, int>> path){}
	virtual void delete_from_Matrix(GraphicsInfo) = 0; //team 13 ///HEBAAA RG3THAAAAAAAA
	virtual void copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2);
	virtual void cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2);
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	virtual void change_to_HI(); //feryal 
	virtual bool getHI();
	GraphicsInfo getgrahicsinfo();  // aabdo 
	void setnew_grafinfo_for_drag(int x, int y);   //aabdo brdo 
	virtual void  Delete(Output* pOut) {}
	virtual void Readd(){}
	virtual void move(Output *pOut, GraphicsInfo) = 0;
	virtual void Save(ofstream&) = 0;
	virtual Component*load(string, string, GraphicsInfo, int) = 0;

	void setID(int i) { id = i; }
	void SetLbl(string l)
	{ m_Label = l; }

    
	int getid();
	string gettype();
	void settype(string t);
	string getlabel();
	string getlastlabel();
	void edit_label(string label);
	GraphicsInfo getm_GfxInfo();
	virtual void change_to_UnHI(); //feryal 
	void setlazy_d(bool l);
	bool getlazy_d();
	void setcalculated(bool c)
	{
		calculated = c;
	}
	bool getcalculated()
	{
		return calculated;
	}
	Component();	
	virtual bool check_calculated() { return false; }
	//Destructor must be virtual
	virtual ~Component();

};

#endif
