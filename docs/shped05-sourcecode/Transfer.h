//---------------------------------------------------------------------------
#ifndef TransferH
#define TransferH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TTransForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *TransGrid;
        TCheckBox *AutoCB;
        TButton *TransBtn;
        TLabel *FromLbl;
        TLabel *ToLbl;
        TCheckBox *PaletteCB;
        TButton *PaletteBtn;
        TLabel *PaletteLbl;
        TOpenDialog *OpenDialog1;
        TButton *LoadScriptBtn;
        TButton *SaveScriptBtn;
        TSaveDialog *SaveDialog1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall TransBtnClick(TObject *Sender);
        void __fastcall TransGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PaletteBtnClick(TObject *Sender);
        void __fastcall LoadScriptBtnClick(TObject *Sender);
        void __fastcall SaveScriptBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTransForm(TComponent* Owner);
        void __fastcall TransSelection(int select);
        int __fastcall  match_color(int r, int g, int b);
};
//---------------------------------------------------------------------------
extern PACKAGE TTransForm *TransForm;
//---------------------------------------------------------------------------
#endif
