//---------------------------------------------------------------------------
#ifndef MainH
#define MainH

#include <stdio.h>
#include <stdlib.h>

#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
//====== my definitions ======
#define BACK_COLOR 255       // a token in the pseudo image for transparent
#define HEADER_SIZE 24       // size of header in icon file
#define MAX_ICONS 10000
#define MAX_COLORS 256

#define MAX_WIDTH 640       // maximum image size
#define MAX_HEIGHT 480


//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *MessageMemo;
	TOpenDialog *OpenDialog1;
	TLabel *Label1;
	TUpDown *ImageUpDown;
	TEdit *ImageEdit;
	TSaveDialog *SaveDialog1;
	TCheckBox *FullPalCB;
	TSpeedButton *LoadShpBtn;
	TSpeedButton *ShowBtn;
	TSpeedButton *WriteBmpBtn;
	TSpeedButton *LoadBmpBtn;
	TSpeedButton *CvtBmpBtn;
	TSpeedButton *InsertBtn;
	TSpeedButton *AddBtn;
	TSpeedButton *LoadPalBtn;
	TSpeedButton *ViewPalBtn;
	TCheckBox *HeaderCB;
	TSpeedButton *HelpBtn;
	TSpeedButton *CollageBtn;
	TSpeedButton *SaveCollageBtn;
	TSpeedButton *AboutBtn;
	TLabel *EditLbl;
	TSpeedButton *CancelBtn;
	TImage *IntroImage;
	TTimer *Timer1;
	TSpeedButton *SPFixBtn;
	TCheckBox *SPNoFlashCB;
        TLabel *PaletteLbl;
        TSpeedButton *TransBtn;
	void __fastcall LoadShpBtnClick(TObject *Sender);

	void __fastcall ShowBtnClick(TObject *Sender);
	void __fastcall WriteBmpBtnClick(TObject *Sender);
	void __fastcall ShowPaletteBtnClick(TObject *Sender);
	void __fastcall LoadBmpBtnClick(TObject *Sender);

	void __fastcall CvtBmpBtnClick(TObject *Sender);
	void __fastcall InsertBtnClick(TObject *Sender);
	void __fastcall LoadPalBtnClick(TObject *Sender);
	void __fastcall AddBtnClick(TObject *Sender);
	void __fastcall AboutBtnClick(TObject *Sender);
	void __fastcall HelpBtnClick(TObject *Sender);
	void __fastcall SaveImageBtnClick(TObject *Sender);

	void __fastcall CollageBtnClick(TObject *Sender);

	void __fastcall FormCreate(TObject *Sender);

	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall IntroImageClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SPFixBtnClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall TransBtnClick(TObject *Sender);
        void __fastcall MessageMemoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
    void __fastcall  TMainForm :: ShowImage();
    void __fastcall  TMainForm :: ShowImageAt(int,int);
    void __fastcall TMainForm :: ClearShpImage();
    void __fastcall TMainForm :: ClearBmpImage();
    int __fastcall TMainForm :: match_color(int,int,int);

};
//---------------------------------------------------------------
class TWaitCursor {

public:
    TWaitCursor() : oldc(Screen->Cursor){ Screen->Cursor = crHourGlass; }
    ~TWaitCursor()                         { Screen->Cursor = oldc; }
private:
    TCursor oldc;
};

//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//======== Globals ===========
extern int icon_add[MAX_ICONS];
extern int pix_pos;
extern int max_pix_x,max_pix_y; //image size info for SP
extern struct iconheader
{
  int lines;             // this is really the number of lines -1
  int width;
  int var1;
  int xstart;
  int ystart;
  int xend;
  int yend;
} header;
extern AnsiString shp_fname;
extern int icon_pal_add[MAX_ICONS];

struct palette {
   unsigned char R;
   unsigned char G;
   unsigned char B;
};
//these are for cfg file
extern int cfgFlag;
extern AnsiString Palette1Name;
extern AnsiString Palette2Name;
extern int MainWinX,MainWinY;
extern int BmpWinX,BmpWinY;
extern int ShpWinX,ShpWinY;
extern int FixWinX,FixWinY;
extern int TransWinX,TransWinY;

extern AnsiString start_path;

extern palette pal[MAX_COLORS];
extern palette pinfo[MAX_COLORS];
extern unsigned char image[MAX_WIDTH][MAX_HEIGHT];
extern struct palette bkcolor;
extern int icons;
// ======= NON-class functions =========
void __fastcall put_pix(int y, int clr);
void __fastcall  clear_image();
void read_header(FILE*,int );
void __fastcall read_shp(FILE *, int );
void Error_Message(char *);
int __fastcall read_palette(FILE *,int);

//---------------------------------------------------------------------------
#endif
