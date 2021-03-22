#include "Connection.h"
#include<fstream>
#include"Gate.h"
using namespace std;
Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin)
//:Component(r_GfxInfo)	
{
	m_GfxInfo = r_GfxInfo; //m3rfsh faydetha eeh
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	settype("connection");
	mtfr3 = false;
}
void Connection::delete_from_Matrix_gdida()
{
	if (mtfr3 == true)
	{
		int i = 0;
		while (i<path.size() - 1 && path[i] != tafree3a)
		{
			sub_path.push_back(path[i]);
			i++;
		}
		if (i<path.size() - 1)
			sub_path.push_back(path[i]);
	}
	else
	{
		sub_path = path;
	}
	for (int i = 1; i < sub_path.size() - 1; i++)
	{
		ApplicationManager::screenMatrix[sub_path[i].second][sub_path[i].first].second = "empty";
	}
	
}
void Connection::choosePath(GraphicsInfo GfxInfo)
{
	/*GfxInfo.x1/= 15;
	GfxInfo.x2 /= 15;
	GfxInfo.y1 /= 15;
	GfxInfo.y2 /= 15;*/
	bool mapped = false;
	bool visited[UI.height / 15 + 1][UI.width / 15 + 1];
	map<pair<int, int>, pair<int, int>> map_bta3t_kolo; //34an kol el nodes tb2a mt save-ya 34an ngeeb el parent
	queue<pair<pair<int, int>, pair<int, int>>> queueForALL; //hanpush feeh kol el nodes elly fadya
	for (int j = 0; j < UI.height / 15 + 1; j++)
		for (int i = 0; i < UI.width / 15 + 1; i++)
			visited[j][i] = false;

	visited[GfxInfo.y1][GfxInfo.x1] = true;  //source point
	pair<pair<int, int>, pair<int, int>> source;
	source.first.first = (GfxInfo.x1);
	source.first.second = (GfxInfo.y1);
	source.second.first = (GfxInfo.x1);
	source.second.second = (GfxInfo.y1);
	queueForALL.push(source);
	pair<pair<int, int>, pair<int, int>> parent;

	while (!queueForALL.empty())

	{
		mapped = false;
		parent = queueForALL.front();
		queueForALL.pop();

		pair<pair<int, int>, pair<int, int>> child;


		if (parent.first.first + 1 <= UI.width / 15 && !visited[parent.first.second][parent.first.first + 1])                 // right child 
		{

			visited[parent.first.second][parent.first.first + 1] = true;
			child.first.first = (parent.first.first + 1);
			child.first.second = (parent.first.second);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);

			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				path.push_back(child.first);
				path.push_back(child.second);
				/*while (!(map_bta3t_kolo[path[path.size() - 1]].first == source.first.first&&map_bta3t_kolo[path[path.size() - 1]].second == source.first.second))
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);*/
				while (path[path.size() - 1] != source.first)
					path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				//path.push_back(source.first);
				return;
			}

			if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;

			}
			else if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[0] == 'c'&&
				ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[1] == 'v' ||
					ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;
				}
			}


		}

		if (parent.first.first - 1 >= 0 && !visited[parent.first.second][parent.first.first - 1])			// left child 
		{
			visited[parent.first.second][parent.first.first - 1] = true;
			child.first.first = (parent.first.first - 1);
			child.first.second = (parent.first.second);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);
			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				path.push_back(child.first);
				path.push_back(child.second);
				/*while (!(map_bta3t_kolo[path[path.size() - 1]].first == source.first.first&&map_bta3t_kolo[path[path.size() - 1]].second == source.first.second))
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);*/
				while (path[path.size() - 1] != source.first)
					path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				//path.push_back(source.first);
				return;
			}
			if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;
			}
			else if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[0] == 'c'
				&&ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[1] == 'v' ||
					ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;

				}
			}

		}

		if (parent.first.second - 1 >= 0 && !visited[parent.first.second - 1][parent.first.first])			// up child 
		{
			visited[parent.first.second - 1][parent.first.first] = true;
			child.first.first = (parent.first.first);
			child.first.second = (parent.first.second - 1);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);
			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				path.push_back(child.first);
				path.push_back(child.second);
				/*while (!(map_bta3t_kolo[path[path.size() - 1]].first == source.first.first&&map_bta3t_kolo[path[path.size() - 1]].second == source.first.second))
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);*/
				while (path[path.size() - 1] != source.first)
					path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				//path.push_back(source.first);
				return;
			}
			if (ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;
			}
			else if (ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[0] == 'c'
				&&ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[1] == 'h'
					|| ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;
				}
			}
		}

		if (parent.first.second + 1<UI.height&&!visited[parent.first.second + 1][parent.first.first])			// down child 
		{
			visited[parent.first.second + 1][parent.first.first] = true;
			child.first.first = (parent.first.first);
			child.first.second = (parent.first.second + 1);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);
			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				path.push_back(child.first);
				path.push_back(child.second);
				/*while (!(map_bta3t_kolo[path[path.size() - 1]].first == source.first.first&&map_bta3t_kolo[path[path.size() - 1]].second == source.first.second))
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				path.push_back(map_bta3t_kolo[path[path.size() - 1]]);*/
				while (path[path.size() - 1] != source.first)
					path.push_back(map_bta3t_kolo[path[path.size() - 1]]);
				//path.push_back(source.first);
				return;
			}
			if (ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;
			}
			else if (ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[0] == 'c'&&
				ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[1] == 'h'
					|| ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;
				}
			}
		}

		if (mapped == true)
			map_bta3t_kolo.insert(parent /*pair<pair<int, int>, pair<int, int>>(parent.first,parent.second)*/);
	}
}

void Connection::delete_from_Matrix(GraphicsInfo g)
{
	bool mtfr3;


	if (this->getSourcePin()->getactualfanout() == 1)
	{
		for (int i = 1; i < path.size() - 1; ++i)
		{
			//checking for any intersecting line
			if (ApplicationManager::screenMatrix[path[i].second][path[i].first].second == "cd")
			{	// intersecting with horizontal line
				if (ApplicationManager::screenMatrix[path[i].second][path[i].first - 1].first == ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first &&!(ApplicationManager::screenMatrix[path[i].second][path[i].first - 1].first == 0 || ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first == 0) && (ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first != this->getid() || ApplicationManager::screenMatrix[path[i].second][path[i].first - 1].first != this->getid()))
					ApplicationManager::screenMatrix[path[i].second][path[i].first].first = ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first;
				else // intersecting with vertical line
					if (ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first == ApplicationManager::screenMatrix[path[i].second - 1][path[i].first].first&& !(ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first == 0 || ApplicationManager::screenMatrix[path[i].second - 1][path[i].first].first == 0) && (ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first != this->getid() || ApplicationManager::screenMatrix[path[i].second - 1][path[i].first].first != this->getid()))
						ApplicationManager::screenMatrix[path[i].second][path[i].first].first = ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first;

					else
					{
						ApplicationManager::screenMatrix[path[i].second][path[i].first].first = 0;
						ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "empty";
					}
			}

			else
			{
				ApplicationManager::screenMatrix[path[i].second][path[i].first].first = 0;
				ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "empty";
			}
		}
		// delete from fanout && delete 2l connection nfso 
		return;
	}

	if (ApplicationManager::screenMatrix[path[path.size() - 2].second][path[path.size() - 2].first].first == ApplicationManager::screenMatrix[path[1].second][path[1].first].first)
	{
		int i;
		bool l2aittfri3a = false;
		for (i = 1; i < path.size() - 1; i++)
		{
			if (ApplicationManager::screenMatrix[path[i].second][path[i].first].second == "cdt")
				l2aittfri3a = true;
			if (!l2aittfri3a)
			{
				//checking for any intersecting line
				if (ApplicationManager::screenMatrix[path[i].second][path[i].first].second == "cd")
				{	// intersecting with horizontal line
					if (ApplicationManager::screenMatrix[path[i].second][path[i].first - 1].first == ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first &&!(ApplicationManager::screenMatrix[path[i].second][path[i].first - 1].first == 0 || ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first == 0) && (ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first != this->getid() || ApplicationManager::screenMatrix[path[i].second][path[i].first - 1].first != this->getid()))
						ApplicationManager::screenMatrix[path[i].second][path[i].first].first = ApplicationManager::screenMatrix[path[i].second][path[i].first + 1].first;
					else // intersecting with vertical line
						if (ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first == ApplicationManager::screenMatrix[path[i].second - 1][path[i].first].first&& !(ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first == 0 || ApplicationManager::screenMatrix[path[i].second - 1][path[i].first].first == 0) && (ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first != this->getid() || ApplicationManager::screenMatrix[path[i].second - 1][path[i].first].first != this->getid()))
							ApplicationManager::screenMatrix[path[i].second][path[i].first].first = ApplicationManager::screenMatrix[path[i].second + 1][path[i].first].first;

						else
						{
							ApplicationManager::screenMatrix[path[i].second][path[i].first].first = 0;
							ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "empty";
						}
				}

				else
				{
					ApplicationManager::screenMatrix[path[i].second][path[i].first].first = 0;
					ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "empty";
				}
			}
			else break;


		}
		Connection * tempcon = SrcPin->get_connec_with_dist_path(path[i].first, path[i].second);
		int id = tempcon->getid();
		pair<int, int>paii2 = make_pair(path[i].first, path[i].second);
		if (noofcdt(paii2) == 1)
			ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "cd";
		for (i; i < path.size() - 1; i++)
		{
			ApplicationManager::screenMatrix[path[i].second][path[i].first].first = id;

		}

		pair<int, int > temppair = make_pair(path[path.size() - 2].first, path[path.size() - 2].second);
		tempcon->setmtfr3(false);
		tempcon->settafree3a(temppair);

		// delete from fanout && delete 2l connection nfso 
		return;
	}
	else
	{

		bool tfr3ti = false;
		bool tfri3atanya = false;
		int i;
		for (i = 1; i < path.size() - 1; i++)
		{
			if (ApplicationManager::screenMatrix[path[i].second][path[i].first].second == "cdt"&&!(path[i].first == tafree3a.first&&path[i].second == tafree3a.second))
			{
				tfri3atanya = true;
				break;
			}
			if (path[i].first == tafree3a.first&&path[i].second == tafree3a.second)
				tfr3ti = true;

			if (!tfr3ti)
			{


				ApplicationManager::screenMatrix[path[i].second][path[i].first].first = 0;
				ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "empty";



			}
			else break;

		}
		pair<int, int>paii2 = make_pair(path[i].first, path[i].second);
		if (noofcdt(paii2) == 1)
			ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "cd";

		if (tfri3atanya)
		{
			Connection * tempcon = SrcPin->get_connec_with_dist_path(path[i].first, path[i].second);
			int id = tempcon->getid();

			for (i; i < path.size() - 1; i++)
			{

				if (path[i].first == tafree3a.first&&path[i].second == tafree3a.second)
					break;
				ApplicationManager::screenMatrix[path[i].second][path[i].first].first = id;



			}
			pair<int, int > temppair = tafree3a;
			tempcon->setmtfr3(true);
			tempcon->settafree3a(temppair);

		}
	}
}

void Connection::updateMatrix_CONNECTION(vector<pair<int, int >>path)
{
	int i = path.size() - 2;
	if (path[i].first == path[i - 1].first) //check 3ala awel point 
	{
		ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "cv";
		ApplicationManager::screenMatrix[path[i - 1].second][path[i - 1].first].second = "cv";
		ApplicationManager::screenMatrix[path[i].second][path[i].first].first = getid();
		ApplicationManager::screenMatrix[path[i - 1].second][path[i - 1].first].first = getid();
	}
	else
	{
		ApplicationManager::screenMatrix[path[i].second][path[i].first].second = "ch";
		ApplicationManager::screenMatrix[path[i - 1].second][path[i - 1].first].second = "ch";
		ApplicationManager::screenMatrix[path[i].second][path[i].first].first = getid();
		ApplicationManager::screenMatrix[path[i - 1].second][path[i - 1].first].first = getid();
	}
	for (int j = path.size() - 3; j > 1; j--)
	{
		if (path[j].first == path[j - 1].first)
		{
			if (ApplicationManager::screenMatrix[path[j].second][path[j].first].second == "ch")
			{
				ApplicationManager::screenMatrix[path[j].second][path[j].first].second = "cd";
				ApplicationManager::screenMatrix[path[j].second][path[j].first].first = getid();
			}

			if (ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].second == "ch")
			{
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].second = "cd";
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].first = getid();
			}
			else
			{
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].second = "cv";
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].first = getid();
			}
		}
		else
		{
			if (ApplicationManager::screenMatrix[path[j].second][path[j].first].second == "cv")
			{
				ApplicationManager::screenMatrix[path[j].second][path[j].first].second = "cd";
				ApplicationManager::screenMatrix[path[j].second][path[j].first].first = getid();
			}

			if (ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].second == "cv")
			{
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].second = "cd";
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].first = getid();
			}
			else
			{
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].second = "ch";
				ApplicationManager::screenMatrix[path[j - 1].second][path[j - 1].first].first = getid();
			}

		}
	}

	ApplicationManager::screenMatrix[path[1].second][path[1].first].second = "cd";


}

void Connection::Save(ofstream &out)
{

	//out <<  ApplicationManager::screenMatrix[sub_path[sub_path.size()-1].second] [sub_path[sub_path.size()-1].first].first<< "\t";

	out << ApplicationManager::screenMatrix[path[this->path.size() - 1].second][path[this->path.size() - 1].first ].first << "\t";
	out << ApplicationManager::screenMatrix[path[0].second ][path[0].first ].first << "\t";
	out << this->getPinNum() << "\n";
}

Connection * Connection::load(string Typ, string Lbl, GraphicsInfo GInfo, int ID)
{
	this->setID(ID);
	this->SetLbl(Lbl);
	this->settype(Typ);
	//this->choosePath(GInfo);
	////////ta3deeeeeeeeeeeeeel
	int xzyada, yzyada;
	if ((ApplicationManager::screenMatrix[GInfo.y1][GInfo.x1].second) == "c_u" ||
		(ApplicationManager::screenMatrix[GInfo.y1][GInfo.x1].second) == "c_l" ||
		(ApplicationManager::screenMatrix[GInfo.y1][GInfo.x1].second) == "c_m")
	{
		xzyada = GInfo.x1;
		yzyada = GInfo.y1;
		GInfo.x1 = GInfo.x1 - 1;
		choosePath(GInfo);
		int f = 2;
		while (path.size() == 0 && (SrcPin->getactualfanout() + f)< SrcPin->get_m_Connections()[0]->path.size())
		{
			GInfo.y2 = SrcPin->get_m_Connections()[0]->path[SrcPin->get_m_Connections()[0]->path.size()-SrcPin->getactualfanout() - f].second;
			GInfo.x2= SrcPin->get_m_Connections()[0]->path[SrcPin->get_m_Connections()[0]->path.size() - SrcPin->getactualfanout() - f].first;
			choosePath(GInfo);
			f++;
		}
	}
	else
	{

		xzyada = GInfo.x2;
		yzyada = GInfo.y2;
		GInfo.x2 = GInfo.x2 - 1;
		choosePath(GInfo);
		int f = 2;
		while (path.size() == 0&& (SrcPin->getactualfanout() + f)< SrcPin->get_m_Connections()[0]->path.size())
		{
			GInfo.y1 = SrcPin->get_m_Connections()[0]->path[SrcPin->get_m_Connections()[0]->path.size() - SrcPin->getactualfanout() - f].second;
			GInfo.x1 = SrcPin->get_m_Connections()[0]->path[SrcPin->get_m_Connections()[0]->path.size() - SrcPin->getactualfanout() - f].first;
			choosePath(GInfo);
			f++;
		}
	}
	pair<int, int>zyada;
	zyada.first = xzyada;
	zyada.second = yzyada;
	//endddddddddddddddddddddddddddd




	//if(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second==c_o)

	

	/*if (path.size() == 0)
	{
		pOut->PrintMsg("This connection can't be drawen as there is no space");
		return;
	}*/
	if (path.size() != 0)
	{
		//ta3deeeeeeeeelllllll
		// kda al source daymn hykon fe a5r al path 
		//||(ApplicationManager::screenMatrix[pA->path[0].second][pA->path[0].first].second.size() == 2
		if (((ApplicationManager::screenMatrix[path[0].second][path[0].first].second) == "c_o" ||
			(ApplicationManager::screenMatrix[path[0].second][path[0].first].second) == "cdt"))

		{
			path.push_back(zyada);
			std::reverse(path.begin(),path.end());
		}
		else
		{
			path.insert(path.begin(), zyada);
		}
		sub_path = path;
		
		//endddddddddddddddddddd

		//source is a connection
		if ((ApplicationManager::screenMatrix[path[path.size() - 1].second][path[path.size() - 1].first].second[1]) != '_')
		{
			//ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].second = "cdt"; // set this point as a tafree3a 
			//set the source pin as the source in of the original connection
			//Connection * source = ((Connection*)pManager->find_component_with_specific_id(ApplicationManager::screenMatrix[pA->path[pA->path.size() - 1].second][pA->path[pA->path.size() - 1].first].first));
			/*if (source->getSourcePin()->ConnectTo(pA) == false) //reached max.fanout
			{
				pOut->PrintMsg("this connection can not be drawn as this output pin has its max num of fanout");
				delete pA;
				pA = NULL;
				return;
			}
			pA->setSourcePin(source->getSourcePin());
			*/
			set_DstPair(path[0]);
			settafree3a(path[path.size() - 1]);
			setmtfr3(true);
			//completing the path to the source pin
			int end = SrcPin->get_m_Connections()[0]->path.size();
			for (int i = 0; i < end; i++)
			{
				if (SrcPin->get_m_Connections()[0]->path[i] == gettafree3a())
				{
					Connection *temp = SrcPin->get_m_Connections()[0];
					for (int j = i; j < end; j++)
					{
						path.push_back(temp->path[j]);
					}
					break;
				}

			}
			set_sourcePair(path[path.size() - 1]);
			SrcPin->ConnectTo(this);
			// destination
			//if destination is a led 
			if (DstPin->getComponent()->gettype() == "LED")
			{
				DstPin->set_pConnect(this);

				SetPinNum(0);



			}
			//if destination is the upper pin of the gate
			else if (ApplicationManager::screenMatrix[path[0].second][path[0].first].second[2] == 'u')
			{
				DstPin->set_pConnect(this);
				SetPinNum(0);

			}
			//if destination is the lower pin of the gate
			else if (ApplicationManager::screenMatrix[path[0].second][path[0].first].second[2] == 'l')
			{
				DstPin->set_pConnect(this);
				SetPinNum(1);


			}
			//if destination is the middle pin of the gate in case it has three input pins 
			else if (((Gate*)DstPin->getComponent())->get_InputsN() == 3)
			{
				if (ApplicationManager::screenMatrix[path[0].second][path[0].first].second[2] == 'm')
				{
					DstPin->set_pConnect(this);
					SetPinNum(2);

				}
			}
			//if destination gate has only one input pin

			else if (((Gate*)DstPin->getComponent())->get_InputsN() == 1)
			{

				DstPin->set_pConnect(this);
				SetPinNum(0);


			}
		}
		//source is a gate or a switch 
		else if (ApplicationManager::screenMatrix[path[path.size() - 1].second][path[path.size() - 1].first].second[2] == 'o')
		{
			//source is a switch 
			if (SrcPin->getComponent()->gettype() == "Switch")
			{
				set_DstPair(path[0]);
			
				SrcPin->ConnectTo(this);
			}

			else {
				set_DstPair(path[0]);

				SrcPin->ConnectTo(this);
			}
			// destination
			//if destination is a led 
			if (DstPin->getComponent()->gettype() == "LED")
			{
				DstPin->set_pConnect(this);

				SetPinNum(0);



			}
			//if destination is the upper pin of the gate
			else if (ApplicationManager::screenMatrix[path[0].second][path[0].first].second[2] == 'u')
			{
				DstPin->set_pConnect(this);
				SetPinNum(0);

			}
			//if destination is the lower pin of the gate
			else if (ApplicationManager::screenMatrix[path[0].second][path[0].first].second[2] == 'l')
			{
				DstPin->set_pConnect(this);
				SetPinNum(1);


			}
			//if destination is the middle pin of the gate in case it has three input pins 
			else if (((Gate*)DstPin->getComponent())->get_InputsN() == 3)
			{
				if (ApplicationManager::screenMatrix[path[0].second][path[0].first].second[2] == 'm')
				{
					DstPin->set_pConnect(this);
					SetPinNum(2);

				}
			}
			//if destination gate has only one input pin

			else if (((Gate*)DstPin->getComponent())->get_InputsN() == 1)
			{

				DstPin->set_pConnect(this);
				SetPinNum(0);


			}
		}
		updateMatrix_CONNECTION(sub_path);
	}
	
	return this;
}

void Connection::setSourcePin(OutputPin *pSrcPin)
{
	SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin()
{
	return SrcPin;
}


void Connection::setDestPin(InputPin *pDstPin)
{
	DstPin = pDstPin;
}

InputPin* Connection::getDestPin()
{
	return DstPin;
}

void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}
void Connection::Draw(Output* pOut)
{

	if (path.size() != 0)
	{
		/*GraphicsInfo g;
		g.x1 = path[path.size() / 3].first * 15+2;
		g.y1 = path[path.size() / 3].second * 15 - 13;
		g.x2 = path[path.size() / 3].first * 15 + 50;
		g.y2 = path[path.size() / 3].second * 15 - 2;*/
		int x, y;

		x = path[path.size() / 2].first * 15 + 1;
		y = path[path.size() / 2].second * 15 - 16;


		pOut->DrawConnection(path, getHI(), SrcPin->getStatus());
		pOut->Clear_string_for_connection(x, y, getlastlabel());
		pOut->Clear_string_for_connection(x, y, getlastlabel());
		pOut->Clear_string_for_connection(x, y, getlastlabel());
		pOut->Clear_string_for_connection(x, y, getlastlabel());
		pOut->Printstring_in_D_A(getlabel(), pOut, x, y);
	}
	//hebaaaaaaa
	//updateMatrix_CONNECTION(sub_path);
	if (mtfr3 == true)
		ApplicationManager::screenMatrix[sub_path[sub_path.size() - 1].second][sub_path[sub_path.size() - 1].first].second = "cdt";
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

void Connection::delete_connection_from_gate(Output*pOut)
{
	pOut->Clear_Connection_from_D_A(path);
	oldDstPin = DstPin;
	oldSrcPin = SrcPin;
	setDestPin(NULL);
	setSourcePin(NULL);
	oldpath = path;
	path.clear();
}
void Connection::readd_connection_from_gate()
{
	DstPin = oldDstPin;
	SrcPin = oldSrcPin;
	path = oldpath;
	updateMatrix_CONNECTION(path);
	DstPin->set_pConnect(this);
	SrcPin->ConnectTo(this);

}
void Connection::delete_connection_itself(Output * pOut)
{
	GraphicsInfo g;
	g.y1 = g.x1 = 90;
	g.y2 = g.x2 = 78;

	pOut->Clear_Connection_from_D_A(path);
	delete_from_Matrix_gdida();    //g mlhash lazma
	/*int max_hbl = SrcPin->getm_fanout();
	int actual_hbl = SrcPin->get_m_Conn();
	delete_from_Matrix(g);
	SrcPin->setm_conn(actual_hbl);
	SrcPin->setm_fanout(max_hbl);
	*/
	oldDstPin = DstPin;
	oldSrcPin = SrcPin;
	//if(DstPin !=NULL)
	setlazy_d(true);
	DstPin->set_pConnect(NULL);
	//if(SrcPin!=NULL)
	SrcPin->delete_SPECIFIC_m_Connections(getid());
	setDestPin(NULL);
	setSourcePin(NULL);
	oldpath = path;
	oldsub_path = sub_path;
	path.clear();
	sub_path.clear();
}

void Connection::Readd()
{
	DstPin = oldDstPin;
	SrcPin = oldSrcPin;
	if (DstPin->set_pConnect(this) && SrcPin->ConnectTo(this))
	{
		setlazy_d(false);
		path = oldpath;
		sub_path = oldsub_path;
		updateMatrix_CONNECTION(sub_path);
	}
	else
	{

		DstPin = NULL;
		SrcPin = NULL;
	}

}

void Connection::set_DstPair(pair<int, int> r_Dst)
{
	Dst = r_Dst;
}

void Connection::set_sourcePair(pair<int, int> r_Dst)
{
	source = r_Dst;
}

pair<int, int> Connection::get_dst_pair()
{
	return Dst;
}

pair<int, int> Connection::get_source_pair()
{
	return source;
}

pair<int, int> Connection::gettafree3a()
{
	return tafree3a;
}

bool Connection::getmtfr3()
{
	return mtfr3;
}

void Connection::settafree3a(pair<int, int> p)
{
	tafree3a = p;
}

void Connection::setmtfr3(bool l)
{
	mtfr3 = l;
}

/*void Connection::Lazy_DeleteConnetion()
{
//cleaned = false;
setlazy_d(true);
//find_component_with_specific_id(i)->delete_from_Matrix();  htt3ml lsa rbna yshl
}*/

int Connection::noofcdt(pair<int, int> temp)
{
	return SrcPin->getnoofcdtat_certian_position(temp);
}

void Connection::help_redo()
{
	if (mtfr3 == true)
	{
		int i = 0;
		while (i<path.size() - 1 && path[i] != tafree3a)
		{
			sub_path.push_back(path[i]);
			i++;
		}
		if (i<path.size() - 1)
			sub_path.push_back(path[i]);
	}
	else
	{
		sub_path = path;
	}
	SrcPin_redo = SrcPin;
	DstPin_redo = DstPin;
	sub_path_redo = sub_path;
	path_redo = path;
}

void Connection::help_undo()
{
	if (mtfr3 == true)
	{
		int i = 0;
		while (i<path.size()-1 && path[i] != tafree3a)
		{
			sub_path.push_back(path[i]);
			i++;
		}
		if (i<path.size()-1)
			sub_path.push_back(path[i]);
	}
	else
	{
		sub_path = path;
	}
	SrcPin_undo = SrcPin;
	DstPin_undo = DstPin;
	sub_path_undo = sub_path;
	path_undo = path;
}

void Connection::Readd_redo()
{
	DstPin = DstPin_redo;
	SrcPin = SrcPin_redo;
	if (DstPin->set_pConnect(this) && SrcPin->ConnectTo(this))
	{
		setlazy_d(false);
		path = path_redo;
		sub_path = sub_path_redo;
		updateMatrix_CONNECTION(sub_path);
	}
	else
	{

		DstPin = NULL;
		SrcPin = NULL;
	}

}

void Connection::Readd_undo()
{
	DstPin = DstPin_undo;
	SrcPin = SrcPin_undo;
	if (DstPin->set_pConnect(this) && SrcPin->ConnectTo(this))
	{
		setlazy_d(false);
		path = path_undo;
		sub_path = sub_path_undo;
		updateMatrix_CONNECTION(sub_path);
	}
	else
	{

		DstPin = NULL;
		SrcPin = NULL;
	}
}
void Connection::delete_from_matrix_b_path(vector<pair<int, int>> r_path)
{
	for (int i = 1; i < r_path.size() - 1; ++i)
	{
		//checking for any intersecting line
		if (ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].second == "cd")
		{	// intersecting with horizontal line
			if (ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first - 1].first == ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first + 1].first &&!(ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first - 1].first == 0 || ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first + 1].first == 0) && (ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first + 1].first != this->getid() || ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first - 1].first != this->getid()))
				ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].first = ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first + 1].first;
			else // intersecting with vertical line
				if (ApplicationManager::screenMatrix[r_path[i].second + 1][r_path[i].first].first == ApplicationManager::screenMatrix[r_path[i].second - 1][r_path[i].first].first&& !(ApplicationManager::screenMatrix[r_path[i].second + 1][r_path[i].first].first == 0 || ApplicationManager::screenMatrix[r_path[i].second - 1][r_path[i].first].first == 0) && (ApplicationManager::screenMatrix[r_path[i].second + 1][r_path[i].first].first != this->getid() || ApplicationManager::screenMatrix[r_path[i].second - 1][r_path[i].first].first != this->getid()))
					ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].first = ApplicationManager::screenMatrix[r_path[i].second + 1][r_path[i].first].first;

				else
				{
					ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].first = 0;
					ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].second = "empty";
				}
		}

		else
		{
			ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].first = 0;
			ApplicationManager::screenMatrix[r_path[i].second][r_path[i].first].second = "empty";
		}
	}
}

vector<pair<int, int>> Connection::choose_path_return_path(GraphicsInfo GfxInfo)
{
	bool mapped = false;

	bool visited[UI.height / 15 + 1][UI.width / 15 + 1];
	map<pair<int, int>, pair<int, int>> map_bta3t_kolo; //34an kol el nodes tb2a mt save-ya 34an ngeeb el parent
	queue<pair<pair<int, int>, pair<int, int>>> queueForALL; //hanpush feeh kol el nodes elly fadya
	for (int j = 0; j < UI.height / 15 + 1; j++)
		for (int i = 0; i < UI.width / 15 + 1; i++)
			visited[j][i] = false;
	vector <pair <int, int >> r_path;
	visited[GfxInfo.y1][GfxInfo.x1] = true;  //source point
	pair<pair<int, int>, pair<int, int>> source;
	source.first.first = (GfxInfo.x1);
	source.first.second = (GfxInfo.y1);
	source.second.first = (GfxInfo.x1);
	source.second.second = (GfxInfo.y1);
	queueForALL.push(source);
	pair<pair<int, int>, pair<int, int>> parent;

	while (!queueForALL.empty())

	{
		mapped = false;
		parent = queueForALL.front();
		queueForALL.pop();

		pair<pair<int, int>, pair<int, int>> child;


		if (parent.first.first + 1 <= UI.width / 15 && !visited[parent.first.second][parent.first.first + 1])                 // right child 
		{

			visited[parent.first.second][parent.first.first + 1] = true;
			child.first.first = (parent.first.first + 1);
			child.first.second = (parent.first.second);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);

			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				r_path.push_back(child.first);
				r_path.push_back(child.second);
				/*while (!(map_bta3t_kolo[r_path[r_path.size() - 1]].first == source.first.first&&map_bta3t_kolo[r_path[r_path.size() - 1]].second == source.first.second))
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);*/
				while (r_path[r_path.size() - 1] != source.first)
					r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				//r_path.push_back(source.first);
				return r_path;
			}

			if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;

			}
			else if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[0] == 'c'&&
				ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[1] == 'v' ||
					ApplicationManager::screenMatrix[parent.first.second][parent.first.first + 1].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;
				}
			}
		}

		if (parent.first.first - 1 >= 0 && !visited[parent.first.second][parent.first.first - 1])			// left child 
		{
			visited[parent.first.second][parent.first.first - 1] = true;
			child.first.first = (parent.first.first - 1);
			child.first.second = (parent.first.second);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);
			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				r_path.push_back(child.first);
				r_path.push_back(child.second);
				/*while (!(map_bta3t_kolo[r_path[r_path.size() - 1]].first == source.first.first&&map_bta3t_kolo[r_path[r_path.size() - 1]].second == source.first.second))
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);*/
				while (r_path[r_path.size() - 1] != source.first)
					r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				//r_path.push_back(source.first);
				return r_path;
			}
			if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;
			}
			else if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[0] == 'c'
				&&ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[1] == 'v' ||
					ApplicationManager::screenMatrix[parent.first.second][parent.first.first - 1].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;

				}
			}

		}

		if (parent.first.second - 1 >= 0 && !visited[parent.first.second - 1][parent.first.first])			// up child 
		{
			visited[parent.first.second - 1][parent.first.first] = true;
			child.first.first = (parent.first.first);
			child.first.second = (parent.first.second - 1);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);
			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				r_path.push_back(child.first);
				r_path.push_back(child.second);
				/*while (!(map_bta3t_kolo[r_path[r_path.size() - 1]].first == source.first.first&&map_bta3t_kolo[r_path[r_path.size() - 1]].second == source.first.second))
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);*/
				while (r_path[r_path.size() - 1] != source.first)
					r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				//r_path.push_back(source.first);
				return r_path;
			}
			if (ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;
			}
			else if (ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[0] == 'c'
				&&ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[1] == 'h'
					|| ApplicationManager::screenMatrix[parent.first.second - 1][parent.first.first].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;
				}
			}

		}


		if (parent.first.second + 1<UI.height&&!visited[parent.first.second + 1][parent.first.first])			// down child 
		{
			visited[parent.first.second + 1][parent.first.first] = true;
			child.first.first = (parent.first.first);
			child.first.second = (parent.first.second + 1);
			child.second.first = (parent.first.first);
			child.second.second = (parent.first.second);
			if (child.first.first == GfxInfo.x2&& child.first.second == GfxInfo.y2)
			{
				map_bta3t_kolo.insert(parent); //34an ana m7taga acesso m4 hynfa3 astana ll25er
				r_path.push_back(child.first);
				r_path.push_back(child.second);
				/*while (!(map_bta3t_kolo[r_path[r_path.size() - 1]].first == source.first.first&&map_bta3t_kolo[r_path[r_path.size() - 1]].second == source.first.second))
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);*/
				while (r_path[r_path.size() - 1] != source.first)
					r_path.push_back(map_bta3t_kolo[r_path[r_path.size() - 1]]);
				//r_path.push_back(source.first);
				return r_path;
			}
			if (ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second == "empty")
			{
				queueForALL.push(child);
				mapped = true;
			}
			else if (ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[0] == 'c'&&
				ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[1] != 'd')
			{
				if (ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[1] == 'h'
					|| ApplicationManager::screenMatrix[parent.first.second + 1][parent.first.first].second[1] == '_')
				{
					queueForALL.push(child);
					mapped = true;
				}
			}


		}

		if (mapped == true)
			map_bta3t_kolo.insert(parent /*pair<pair<int, int>, pair<int, int>>(parent.first,parent.second)*/);
	}

}