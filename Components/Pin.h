#ifndef _PIN_H
#define _PIN_H
#include "..\Defs.h"

class Pin
{
protected:
	STATUS m_Status;	//Status of the Pin
	bool visited; //(needed to check if there is a loop during validation of circuit )

public:
	Pin();
	void setStatus(STATUS r_Status);
	STATUS getStatus();
	bool getvisited()
	{
		return visited;
	}
	void setvisited(bool v)
	{
		visited = v;
	}
	
};

#endif