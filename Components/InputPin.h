#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Connection;
class Component; //Forward class declaration

class InputPin: public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	//me7tageen ptr to connection 
	Connection* pConnect;
	Component* oldpComp;
	Connection* oldpConnect;
public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this input pin
	bool set_pConnect(Connection* r_connect);
	Connection* get_pConnect();
	Connection * get_oldpConnect();
	void set_oldpConnect();
	void raddconnection();
};

#endif