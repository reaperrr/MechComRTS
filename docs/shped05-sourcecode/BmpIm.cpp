//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "BmpIm.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TBmpForm *BmpForm;
//---------------------------------------------------------------------------
__fastcall TBmpForm::TBmpForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBmpForm::FormCreate(TObject *Sender)
{
   BmpForm->Left=BmpWinX;
   BmpForm->Top=BmpWinY;
}
//---------------------------------------------------------------------------
void __fastcall TBmpForm::FormClose(TObject *Sender, TCloseAction &Action)
{
   
   BmpWinX=BmpForm->Left;
   BmpWinY=BmpForm->Top;
}
//---------------------------------------------------------------------------
