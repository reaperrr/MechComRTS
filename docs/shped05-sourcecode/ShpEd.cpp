//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ShpEd.res");
USEFORM("SPF.cpp", SPFix);
USEFORM("Help.cpp", HelpForm);
USEFORM("Main.cpp", MainForm);
USEUNIT("Shp_ed.cpp");
USEFORM("ShpIm.cpp", ShpForm);
USEFORM("BmpIm.cpp", BmpForm);
USEFORM("Transfer.cpp", TransForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->HelpFile = "F:\\BCB4\\Work\\ShpEd\\Shped050.hlp";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TSPFix), &SPFix);
                 Application->CreateForm(__classid(THelpForm), &HelpForm);
                 Application->CreateForm(__classid(TShpForm), &ShpForm);
                 Application->CreateForm(__classid(TBmpForm), &BmpForm);
                 Application->CreateForm(__classid(TTransForm), &TransForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
