#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

	
	/*pWind->SetPen(BLUE, 3);
	for (int i = 0; i < 1000; i += 15)
	{
		for (int j = 100; j < 650; j++)


			pWind->DrawPixel(i, j);

	}*/

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
window * Output::getpointerwind()
{
	return  pWind;
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor);            //
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
	//Sleep(1500);
}
/////////////////////////////////////////////////////////////////////////////hebaaaaa
void  Output::Printstring_in_D_A(string msg, Output* pOut,int x, int y) const
{
	
	if (msg != "")   //3lshan lw 3ml escabe mystnash click
	{
		
		pWind->SetFont(17, BOLD | ITALICIZED, BY_NAME, "Arial");
		pWind->SetPen(UI.MsgColor);            
		
		pWind->DrawString(x, y, msg);
		pOut->ClearStatusBar();
	}
	else
	{
		pOut->ClearStatusBar();
	}
	
}

void Output::Clear_Gate_from_D_A(int X, int Y)const
{
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(X - 5, Y - 20, X + 55, Y + 55);

}
//////////////////////////////end hebaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//////////////////////////////////////////////////////////////////////////////////
void Output::Clear_string_from_D_A(int MsgX, int MsgY)const                                        //     ???????
{
	
	// Set the Message offset from the Status Bar
	
	
	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX-3, MsgY, MsgX + 55, MsgY+20);   //3 lla7tyaat
}
void Output::Clear_string_for_connection(int x,int y,string msg)const
{
	pWind->SetFont(17, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);

	pWind->DrawString(x, y, msg);
}
void Output::Clear_Connection_from_D_A(vector<pair<int, int>> path)
{
	pWind->SetPen(UI.BkGrndColor, 4);
	for (int i = path.size() - 1; i > 0; i--)
	{
		pWind->DrawLine(path[i].first * 15, path[i].second * 15, path[i - 1].first * 15, path[i - 1].second * 15);
	}
	pWind->SetPen(WHITE, 10);
	pWind->DrawCircle(path[0].first * 15, path[0].second * 15, 5, FILLED);
	pWind->DrawCircle(path[path.size() - 1].first * 15, path[path.size() - 1].second * 15, 5, FILLED);
}
void Output::ClearStatusBar()const
{                                                //////hebaaaaaaaa 
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	pWind->SetPen(BLUE, 3);
	for (int i = 0; i < UI.width; i += 15)
	{
		for (int j = 90; j <UI.height-50; j+=15)


			pWind->DrawPixel(i, j);

	}
	
}

void Output::Cleartoolbar() const               //hebaaa
{
	
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode                                       

	//You can draw the tool bar icons in any way you want.
	
	//First prepare List of images for each menu item

	pWind->DrawImage("images\\Menu\\DSNBAR.jpg", 0, 0);

	//Draw a line under the toolbar
	pWind->SetPen(BLUE,3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

	pWind->SetPen(BLUE, 3);
	for (int i = 0; i < UI.width; i += 15)
	{
		for (int j = 90; j < UI.height-50; j+=15)


			pWind->DrawPixel(i, j);

	}
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode
pWind->DrawImage("images\\Menu\\SIMBar.jpg", 0, 0);

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	
	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	
	
}

void Output::CreateAddToolBar() const
{

	UI.AppMode = ADD;	//Design Mode                                       

							//You can draw the tool bar icons in any way you want.

							//First prepare List of images for each menu item
	
	pWind->DrawImage("images\\Menu\\AddTOOL.jpg", 0, 0);


	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::Createtruthtablebar() const
{
	UI.AppMode = TruthTable;
	string MenuItemImages[ITM_truth_CNT];
	MenuItemImages[ITM_switch_back2] = "images\\Menu\\Menu_Switchback.jpg";
	for (int i = 0; i<ITM_truth_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\Gate_AND2_Hi.jpg";
	else  
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.AND2_Width,UI.AND2_Height);
}
//TODO: Add similar functions to draw all components
void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.NAND2_Width,UI.NAND2_Height);
}
void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.OR2_Width,UI.OR2_Height);
}
void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.NOR2_Width,UI.NOR2_Height);
}
void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.XOR2_Width,UI.XOR2_Height);
}
void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.XNOR2_Width,UI.XNOR2_Height);
}
void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.NOR3_Width,UI.NOR3_Height);
}
void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.XOR3_Width,UI.XOR3_Height);
}
void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.AND3_Width,UI.AND3_Height);
}
void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOT.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOT.jpg";

	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.Inverter_Width,UI.Inverter_Height);
}
void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_Buffer.HI.jpg";
	else
		GateImage = "Images\\Gates\\Gate_Buffer.jpg";

	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.Buffer_Width,UI.Buffer_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\LED.HI.jpg";
	else
		GateImage = "Images\\Gates\\LED.jpg";
//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.LED_Width,UI.LED_Height);
}
void Output::DrawLED_sim(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
		//use image in the highlighted case
		GateImage = "Images\\Gates\\LED.light.jpg";
/*	else
		GateImage = "Images\\Gates\\LED.jpg";*/
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.LED_Width,UI.LED_Height);
}
//////////////////////fun
void Output::DrawLED1(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	GateImage = "Images\\Gates\\LED1.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.LED_Width,UI.LED_Height);
}
//////////////////
void Output::DrawSWITCHON(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;


		GateImage = "Images\\Gates\\SWITCH.OFF.jpg";

//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1,UI.Switch_Width,UI.Switch_Height);
}
void Output::DrawSWITCHOFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;

if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\SWITCH.ON.HI.jpg";
	else
		GateImage = "Images\\Gates\\SWITCH.ON.jpg";

//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Switch_Width, UI.Switch_Height);
}

void Output::DrawConnection(vector<pair<int, int>> path, bool selected,  STATUS mnwr) const
{

	//TODO: Add code to draw connection
	//GraphicsInfo G;
	if (UI.AppMode == SIMULATION&&mnwr == HIGH)
	{

		pWind->SetPen(GREEN, 4);
		for (int i = path.size() - 1; i >0; i--)
		{
			pWind->DrawLine(path[i].first * 15, path[i].second * 15, path[i - 1].first * 15, path[i - 1].second * 15);

		}
		pWind->SetPen(GREEN, 10);
		pWind->DrawCircle(path[0].first * 15, path[0].second * 15, 5, FILLED);
		pWind->DrawCircle(path[path.size() - 1].first * 15, path[path.size() - 1].second * 15, 5, FILLED);
		//if (tfri3a)
		//	pWind->DrawCircle(makn_tfri3a.first * 15, makn_tfri3a.second * 15, 7, FILLED);

		// pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2);
	}

	else if (selected)
	{
		// aabdo's ta3dil 
		pWind->SetPen(BLUE, 4);
		for (int i = path.size() - 1; i >0; i--)
		{
			pWind->DrawLine(path[i].first * 15, path[i].second * 15, path[i - 1].first * 15, path[i - 1].second * 15);

		}
		pWind->SetPen(BLUE, 10);
		pWind->DrawCircle(path[0].first * 15, path[0].second * 15, 5, FILLED);
		pWind->DrawCircle(path[path.size() - 1].first * 15, path[path.size() - 1].second * 15, 5, FILLED);
		//if (tfri3a)
		//	pWind->DrawCircle(makn_tfri3a.first * 15, makn_tfri3a.second * 15, 7, FILLED);
	}
	else
	{
		pWind->SetPen(BLACK, 4);
		for (int i = path.size() - 1; i >0; i--)
		{
			pWind->DrawLine(path[i].first * 15, path[i].second * 15, path[i - 1].first * 15, path[i - 1].second * 15);

		}
		pWind->SetPen(BLACK, 10);
		pWind->DrawCircle(path[0].first * 15, path[0].second * 15, 5, FILLED);
		pWind->DrawCircle(path[path.size() - 1].first * 15, path[path.size() - 1].second * 15, 5, FILLED);
		//if (tfri3a)
			//pWind->DrawCircle(makn_tfri3a.first * 15, makn_tfri3a.second * 15, 7, FILLED);
	}
}

void Output::DrawTT(int SW, int  LD, int**S, int**O, string* STch, string* LEDs) {


	int m = 1;
	pWind->SetPen(BLACK, 4);
	pWind->SetFont(25, 4, SWISS);
	pWind->SetBrush(BLUE);

	for (int i = 0; i < SW; i++) m *= 2;
	//Drawing vertical lines
	for (int i = 0; i < SW + LD; i++)
		pWind->DrawLine((i + 1) * 50, UI.ToolBarHeight, (i + 1) * 50, UI.ToolBarHeight + m * 30 + 30);
	//Drawing horizontal lines
	for (int i = 0; i < m + 1 && UI.ToolBarHeight + (i + 1)<UI.height - UI.StatusBarHeight; i++)
		pWind->DrawLine(0, UI.ToolBarHeight + (i + 1) * 30, (SW + LD) * 50, UI.ToolBarHeight + (i + 1) * 30);


	string M = "S";
	//Drawing swithes and leds labels
	pWind->SetPen(GREEN, 4);
	for (int i = 0; i < SW; i++)

	{
		pWind->DrawString(20 + i * 50, UI.ToolBarHeight, STch[i]);
	}
	M = "L";
	for (int i = SW; i <LD + SW; i++)
		pWind->DrawString(20 + i * 50, UI.ToolBarHeight, LEDs[i - SW]);


	pWind->SetPen(RED, 4);

	for (int i = 0; i < m; i++)
	{
		{
			for (int j = 0; j < SW + LD; j++)
			{
				if (j < SW)
				{
					if (S[i][j] == 1) pWind->SetPen(GREEN,4);
					else pWind->SetPen(BLACK,4);
					pWind->DrawInteger(20 + j * 50, UI.ToolBarHeight + 30 * (i + 1), S[i][j]);
				}

				else
				{
					if (O[i][j - SW] == 1) pWind->SetPen(GREEN, 4);
					else pWind->SetPen(BLACK, 4);
					pWind->DrawInteger(20 + j * 50, UI.ToolBarHeight + 30 * (i + 1), O[i][j - SW]);
				}
			}
		}
	}
	

}

Output::~Output()
{
	delete pWind;
}





