//---------------------------------------------------------------------------
#ifndef ShpImH
#define ShpImH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TShpForm : public TForm
{
__published:	// IDE-managed Components
	TImage *ShpImage;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TShpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TShpForm *ShpForm;
//---------------------------------------------------------------------------
#endif
