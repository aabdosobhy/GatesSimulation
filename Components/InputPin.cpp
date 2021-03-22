#include "InputPin.h"
#include"..\Components\Connection.h"
InputPin::InputPin()
{
	pConnect = NULL;
	oldpConnect = NULL;
	pComp = NULL;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}

bool InputPin::set_pConnect(Connection* r_connect)
{
	if (pConnect != NULL)
	{
		if (r_connect == NULL)
		{
			pConnect = NULL;
		}
		return false;
	}
	else
	{
		pConnect = r_connect;
		return true;
	}
}

Connection * InputPin::get_pConnect()
{
	return pConnect;
}
Connection * InputPin::get_oldpConnect()
{
	return oldpConnect;
}

void InputPin::set_oldpConnect()
{
	oldpConnect = pConnect;
}

void InputPin::raddconnection()
{
	//pConnect = oldpConnect;
	//pConnect ->setlazy_d(false); 
	oldpConnect->Readd();
	//pConnect->updateMatrix_CONNECTION(pConnect->path); 
	
}
