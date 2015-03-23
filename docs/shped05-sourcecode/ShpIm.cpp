//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "ShpIm.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TShpForm *ShpForm;
//---------------------------------------------------------------------------
__fastcall TShpForm::TShpForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TShpForm::FormCreate(TObject *Sender)
{
   ShpForm->Top=ShpWinY;
   ShpForm->Left=ShpWinX;
}
//---------------------------------------------------------------------------
void __fastcall TShpForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  ShpWinY=ShpForm->Top;
  ShpWinX=ShpForm->Left;
}
//---------------------------------------------------------------------------
