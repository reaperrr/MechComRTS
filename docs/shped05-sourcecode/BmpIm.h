//---------------------------------------------------------------------------
#ifndef BmpImH
#define BmpImH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBmpForm : public TForm
{
__published:	// IDE-managed Components
	TImage *BmpImage;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TBmpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TBmpForm *BmpForm;
//---------------------------------------------------------------------------
#endif
