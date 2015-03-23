//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USERES("Shp_ed.res");
USEFORM("ShpIm.cpp", ShpForm);
USEFORM("BmpIm.cpp", BmpForm);
USEFORM("SPF.cpp", SPFix);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TShpForm), &ShpForm);
		Application->CreateForm(__classid(TBmpForm), &BmpForm);
		Application->CreateForm(__classid(TSPFix), &SPFix);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
