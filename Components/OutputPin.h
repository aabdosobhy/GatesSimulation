#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H
#include<queue>
/*class OutputPin 
  ---------------
 An output pin obtains its value as a result of calculating the outputs of
 a component. The output pin propagates its value immediately to the associated connections
*/
#include "Pin.h"
#include "Connection.h"

class Connection;	//Forward class declartion


class OutputPin: public Pin	//inherited from class Pin
{
private:
	//Array of connections (poniters) to be connected to that OutputPin
	//For simplicity, we consider it a constant length
	Component* pComp;
	Connection* m_Connections[MAX_CONNS];
	Connection* oldm_Connections[MAX_CONNS];
	int m_FanOut;	//Maximum No. of connections connected to that output pin (depends on the component)
	int m_Conn;		//Actual No. of connections connected to that output pin
	int oldm_Conn;
public:
	OutputPin(int r_FanOut);
	void setComponent(Component * pCmp);
	bool ConnectTo(Connection *r_Conn);	//connect to a new connection
	Connection** get_m_Connections();
	void delete_m_Connections();
	void readd_m_Connections();
	void delete_SPECIFIC_m_Connections(int i);
	int get_m_Conn();
	int get_old_m_Conn();
	int getactualfanout();
	void setm_conn(int x);
	void setm_fanout(int x);
	int getm_fanout()
	{
		return m_FanOut;
	}
	Connection * get_connec_with_dist_path(int x, int y);
	int getnoofcdtat_certian_position(pair<int, int> temp);
	void set_children_visited(queue<Component*>& help_sequential); //set visited for all input pins connectd to this output pin
	void set_children_visited_and_set_status(queue<Component*>& components);
	Component* getComponent()
	{
		return pComp;
	}
};

#endif