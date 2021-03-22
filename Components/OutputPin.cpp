#include "OutputPin.h"
#include"..\Components\LED.h"


OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS: r_FanOut;	//set the fan out of the pin.
	///////////////feryal-1//////////////////////
	for (int i = 0; i < m_FanOut; i++)
		m_Connections[i] = NULL;
	for (int i = 0; i < m_FanOut; i++)
		oldm_Connections[i] = NULL;
	/*if (m_FanOut = r_FanOut)
		for (int i = 0; i < r_FanOut; i++)
			m_Connections[i] = NULL;
	else
		for (int i = 0; i < r_FanOut; i++)
		m_Connections[i] = NULL;*/
}
void OutputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if(m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}

Connection** OutputPin::get_m_Connections()
{
	return m_Connections;
}
void OutputPin::delete_m_Connections()
{ 
	
	int j = 0;  oldm_Conn = 0;
	for (int i = 0; i < m_Conn; i++)
	{
		//m_Connections[i]->setlazy_d(true);
		oldm_Connections[j] = m_Connections[i];
		j++;
		oldm_Conn++;
		//m_Connections[i] = NULL;

	}
	//m_Conn = 0;
}
void OutputPin::readd_m_Connections()
{
	for (int i = 0; i < oldm_Conn; i++)
	{
		//oldm_Connections[i]->setlazy_d(false);
		oldm_Connections[i]->Readd();
		//ConnectTo(oldm_Connections[i]);
	}
	oldm_Conn = 0;
}
void OutputPin::delete_SPECIFIC_m_Connections(int i)
{

	for (int j = 0; j < m_Conn; j++)
	{
		if (m_Connections[j]->getid() == i)
		{
			m_Connections[j]->setlazy_d(true);
			swap(m_Connections[j], m_Connections[m_Conn - 1]);
			m_Connections[m_Conn-1] = NULL;
			m_Conn--;
			break;
		}
	}
}
int OutputPin::get_m_Conn()
{
	return m_Conn;
}

int OutputPin::get_old_m_Conn()
{
	return oldm_Conn;
}

int OutputPin::getactualfanout()
{
	return m_Conn;
}
void OutputPin::setm_conn(int x)
{
	m_Conn = x;
}
void OutputPin::setm_fanout(int x)
{
	m_FanOut = x;
}
Connection * OutputPin::get_connec_with_dist_path(int x, int y)
{
	pair <int, int >temp = make_pair(x, y);
	for (int i = 0; i < m_Conn; i++)
		if (m_Connections[i]->gettafree3a() == temp)
			return m_Connections[i];

}

int OutputPin::getnoofcdtat_certian_position(pair<int, int> temp)
{
	int x = 0;
	for (int i = 0; i < m_Conn; i++)
		if (m_Connections[i]->gettafree3a() == temp)
			x++;
	return x;
}
void OutputPin::set_children_visited(queue<Component*>& help_sequential)
{
	for (int i = 0; i < m_Conn; i++)
	{
		m_Connections[i]->getDestPin()->setvisited(true);
		if (m_Connections[i]->getDestPin()->getComponent()->check_calculated());
		if (dynamic_cast<LED*>(m_Connections[i]->getDestPin()->getComponent()))
			((LED*)m_Connections[i]->getDestPin()->getComponent())->setcalculated(true);
		else if (m_Connections[i]->getDestPin()->getComponent()->check_calculated())
		{
			help_sequential.push(m_Connections[i]->getDestPin()->getComponent());
		}

	}
}

void OutputPin::set_children_visited_and_set_status(queue<Component*>& components)
{

	for (int i = 0; i < m_Conn; i++)
	{
		m_Connections[i]->getDestPin()->setvisited(true);
		m_Connections[i]->getDestPin()->setStatus(getStatus());

		if (dynamic_cast<LED*>(m_Connections[i]->getDestPin()->getComponent()))
		{
			((LED*)m_Connections[i]->getDestPin()->getComponent())->setcalculated(true);
			m_Connections[i]->getDestPin()->getComponent()->Operate();
		}
		else if (m_Connections[i]->getDestPin()->getComponent()->check_calculated())
		{
			m_Connections[i]->getDestPin()->getComponent()->Operate();
			components.push(m_Connections[i]->getDestPin()->getComponent());
		}

	}
}
