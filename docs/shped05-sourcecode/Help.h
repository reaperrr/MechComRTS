//---------------------------------------------------------------------------
#ifndef HelpH
#define HelpH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------
class THelpForm : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *HelpRichEdit;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THelpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern THelpForm *HelpForm;
//---------------------------------------------------------------------------
#endif
