#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"
class Connection;
class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	int sx, sy;         //hysa3dony fe action un select all hebaaaaaaaaaaaaa

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetSrting(Output*);		//Returns a string entered by the user
	window *getWindowPtr();
	ActionType GetUserAction() ; //Reads the user click and maps it to an action

	//////5LEEEEEEEEEEEET ALY FOO MSH CONST FN
	int getsx()              ///hebaaaaaaaaaaaaaaaaaaa
	{
		return sx;
	}
	int getsy()
	{
		return sy;
	}
	~Input();
};
