#include"Connection.h"
#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo, string type, string label) :id(++last_id)   //dft 7gat
{
	m_GfxInfo = r_GfxInfo;	
	HI = false;
	lazy_deleted = false;
	calculated = false;
}

void Component::setlazy_d(bool l)
{
	lazy_deleted = l;
}

bool Component::getlazy_d()
{
	return lazy_deleted;
}
Component::Component() :id(++last_id)      //dft 7gat
{
	m_Label = "";
	last_label = "";
	HI = false;
	lazy_deleted = false;
	calculated = false;
}


Component::~Component()    
{}
void Component::change_to_UnHI()
{
	HI = false;
}

void Component::change_to_HI()
{
	HI = true;
}

bool Component::getHI()
{
	return HI;
}

GraphicsInfo Component::getgrahicsinfo()
{
	return m_GfxInfo;
}

void Component::setnew_grafinfo_for_drag(int x, int y)
{
	m_GfxInfo.x1 = x - 25;
	m_GfxInfo.y1 = y - 25;
	m_GfxInfo.x2 = x + 25;
	m_GfxInfo.y2 = y + 25;
}

////hebaaaaa
int Component::getid()
{
	return id;
}
string Component::gettype()
{
	return type;
}
void Component::settype(string t)
{
	type = t;
}
string Component::getlabel()
{
	return m_Label;
}
string Component::getlastlabel()
{
	return last_label;
}
void Component::edit_label(string label)
{
	last_label = m_Label;
	m_Label = label;
}
GraphicsInfo Component::getm_GfxInfo()
{
	return m_GfxInfo;
}
int Component::last_id = 0;


void Component::copy(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
}

void Component::cut(ApplicationManager *pManager, int x, int y, vector<int>& iddones2)
{
}

