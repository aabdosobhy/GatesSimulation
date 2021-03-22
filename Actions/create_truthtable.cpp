#include "create_truthtable.h"
#include"..\Components\Switch.h"
#include<fstream>
using namespace std;


create_truthtable::create_truthtable(ApplicationManager *pApp) :Action(pApp)
{
}


create_truthtable::~create_truthtable()
{
}

void create_truthtable::ReadActionParameters()
{
}




void generate(ofstream& out, int len, string s = "")
{

	if (s.length() == len)
	{
		out << s << endl;
		return;
	}
	generate(out, len, s + '0');
	generate(out, len, s + '1');

}

void create_truthtable::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (UI.AppMode == SIMULATION)
	{
		//pIn->getWindowPtr()->StoreImage(pManager->getsim(), 0, UI.ToolBarHeight + 4, UI.width, UI.height - UI.StatusBarHeight - 4);
		pOut->ClearDrawingArea();
		pOut->Cleartoolbar();
		pOut->Createtruthtablebar();   //whna hyd5l fe al truth table mode
		ofstream out;
		out.open("Combination.txt");


		int numComb = 1, numS = pManager->GetNumofSw(), numLD = pManager->GetNumofLD();
		for (int i = 0; i < numS; i++) numComb *= 2;
		string *S = new string[numComb];


		generate(out, numS);
		out.close();

		ifstream in;
		in.open("Combination.txt");

		for (int i = 0; i < numComb; i++)
			in >> S[i];

		/*out.open("Combination.txt", ios::out);
		for (int i = 0; i < numComb; i++)
		{
			for (int j = 0; j < numS; j++)
				out << "\t" << S[i][j];
			out << endl;
		}*/

		string *LEDS = new string[numLD];
		string *SW = new string[numS];
		int **IPs = new int*[numComb];
		for (int i = 0; i < numComb; i++)
			IPs[i] = new int[numS];

		for (int i = 0; i < numComb; i++)
		{
			for (int j = 0; j <numS; j++)
			{
				IPs[i][j] = S[i][j] - 48;
			}
		}

		int **OPs = new int*[numComb];
		for (int i = 0; i < numComb; i++)
			OPs[i] = new int[numLD];

		for (int w = 0; w < numComb; w++)
		{
			pManager->setSwitches(IPs[w], SW);
			pManager->run_for_simulation();
			pManager->GetLDs(OPs[w], LEDS);
		}

		if (numS < 5)
		{
			pOut->DrawTT(numS, pManager->GetNumofLD(), IPs, OPs, SW, LEDS);
		}
		else
		{
			OFile(IPs, OPs, SW, LEDS);
			pOut->getpointerwind()->DrawString(UI.width / 2 - 500, UI.height / 2, "Inputs are more than 4,The Output is in (TruthTable.txt).");

		}

		
		delete[]S;
		for (int i = 0; i < numComb; i++)
		{
			delete IPs[i];
			delete OPs[i];
		}
		delete[]OPs;
		delete[]IPs;

	}
	else if (UI.AppMode == TruthTable)
	{
		pOut->ClearDrawingArea();
		pOut->Cleartoolbar();
		pOut->CreateSimulationToolBar();
		pManager->switch_design();   //3lshan arg3 kol 7aga off

	}



}
void  create_truthtable::OFile(int**IPs, int**OPs, string* SW, string* LEDS)
{
	int numComb = 1, numS = pManager->GetNumofSw(), numLD = pManager->GetNumofLD();
	for (int i = 0; i < numS; i++) numComb *= 2;


	ofstream out;
	out.open("TruthTable.txt");
	for (int i = 0; i < numS; i++)
		out << SW[i] << "\t";

	for (int i = numS; i < numLD + numS; i++)
		out << LEDS[i - numS] << "\t";
	out << endl;

	for (int i = 0; i < numComb; i++)
	{
		for (int j = 0; j < numS; j++)
		{
			out << IPs[i][j] << "\t";
		}

		for (int j = 0; j <numLD; j++)
		{
			out << OPs[i][j] << "\t";
		}
		out << endl;
	}



}

void create_truthtable::Undo()
{
	
}

void create_truthtable::Redo()
{
}
