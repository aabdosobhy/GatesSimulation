#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include<string>
#include <queue>
#include<vector>
#include<stack>
#include<string>    

using namespace std;

//Main class that manages everything in the application.
class Connection;
class ApplicationManager
{
	enum { MaxCompCount = 200 };	//Max no of Components	

private:

	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

	bool cleaned;       //the list has at least one item to deleted but did not deleted yet
						//bool truth_table;
						//	image simulation;
public:

	vector<pair<pair<int, int>, pair<int, int>>> selected_components;
	stack<Action*>actualActions;
	stack<Action*>redoActions;
	static std::pair<int, std::string> screenMatrix[UI.height / 15 + 1][UI.width / 15 + 1];
	
	ApplicationManager(); //constructor

 // static image *CircSimag ;
	void check_Add_Connection();
	void fillmatrix();
	void change_ALL_to_UnHI();    
	int getComponentPosition(int x, int y)     //get what exists in that position
	{
		return ApplicationManager::screenMatrix[y][x].first;

	}
	void Lazy_DeleteComponent(int i, GraphicsInfo GInfo);
	void Lazy_DeleteConnetion(int i, vector<pair<int, int>> path);
	void cleaning();

	bool getcleaned()
	{
		return cleaned;
	}
	void setcleaned(bool t)
	{
		cleaned = t;
	}
	/*void settruthtable(bool t)
	{
	truth_table = t;
	}*/
	/*image getsim()
	{
	return simulation;
	}*/
	bool check_matrix(int cx, int cy);
	void help_select_area(GraphicsInfo GInfo);

	void help_unselect_area(GraphicsInfo GInfo);
	void copy_selected_components(int x, int y, vector<int>& iddones1, vector<int>& iddones2);

	void cut_selected_components(int x, int y, vector<int>& iddones1, vector<int>& iddones2);
	void save();
	void load();
	int getcopmcount()
	{
		return CompCount;
	}
	//Reads the required action from the user and returns the corresponding action type         
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

							//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	Component* find_component_with_specific_id(int component_id);   
	void Delete_selected_components(vector<int>& iddones);
	void Readd_selected_components(vector<int>& iddones);
	void change_copy_unhi(vector<int>& iddones);
	void uncopy_cut_components(vector<int>& iddones2);
	int GetNumofSw();
	int GetNumofLD();
	void GetLDs(int * &LDs,string*&);
	void switch_design();
	void run_for_simulation();
	std::string  circuit_valid();
	void DeleteCompList();
	void setSwitches(int*,string*&);
	//destructor
	~ApplicationManager();
};

#endif


