//---------------------------------------------------------------------------
#ifndef SPFH
#define SPFH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSPFix : public TForm
{
__published:	// IDE-managed Components
	TImage *MagImage;
	TEdit *OldXSizeEdit;
	TEdit *OldYSizeEdit;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *OldXOffsEdit;
	TEdit *OldYOffsEdit;
	TEdit *OldLeftEdit;
	TEdit *OldTopEdit;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *OldRightEdit;
	TEdit *OldBottomEdit;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *NewXSizeEdit;
	TEdit *NewYSizeEdit;
	TEdit *NewXOffsEdit;
	TEdit *NewYOffsEdit;
	TEdit *NewLeftEdit;
	TEdit *NewTopEdit;
	TEdit *NewRightEdit;
	TEdit *NewBottomEdit;
	TLabel *Label10;
	TUpDown *XUpDown;
	TButton *MagShowBtn;
	TEdit *WidthEdit;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *HeightEdit;
	TUpDown *YUpDown;
	TButton *WriteBtn;
	TLabel *NumberLbl;
	TLabel *NameLbl;
	void __fastcall MagShowBtnClick(TObject *Sender);
	
	
	void __fastcall YUpDownClick(TObject *Sender, TUDBtnType Button);
	void __fastcall XUpDownClick(TObject *Sender, TUDBtnType Button);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall WriteBtnClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TSPFix(TComponent* Owner);
    void __fastcall  TSPFix :: ShowMagImage();
    void __fastcall TSPFix::Xline(int x);
    void __fastcall TSPFix::Yline(int x);
    void __fastcall TSPFix::UnYline(int y);
    void __fastcall TSPFix::UnXline(int x);
};
//---------------------------------------------------------------------------
extern TSPFix *SPFix;
//---------------------------------------------------------------------------
#endif
