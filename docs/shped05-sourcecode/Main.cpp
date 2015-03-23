//---------------------------------------------------------------------------
//  Source code for ShpEd Version 0.50
//    Copyright by Fred Chlanda
//          June 1999
//----------------------------------------------------------------------
#include <vcl\vcl.h>

#pragma hdrstop

#include <io.h>
#include <stdio.h>
#include "Main.h"
#include "Help.h"
#include "ShpIm.h"
#include "BmpIm.h"
#include "SPF.h"
#include "Transfer.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

TMainForm *MainForm;

AnsiString Version="Version 0.50";

//these are things that are saved in the cfg file
int cfgFlag;
AnsiString cfgName="ShpEd.cfg";
AnsiString Palette1Name="default";
AnsiString Palette2Name="default";
int MainWinX,MainWinY;
int BmpWinX,BmpWinY;
int ShpWinX,ShpWinY;
int FixWinX,FixWinY;
int TransWinX,TransWinY;

Boolean autoload; //flag for command line load

struct palette pal[MAX_COLORS];
struct palette bkcolor={255,225,225};
//changed this to 0-255 scale for Version 0.42
//struct palette pinfo[256] =  {{ 0, 0, 0},
//{ 0,36,49}, { 0,42, 0}, { 0,42,42}, {42, 0, 0}, {42, 0,42},/*   5 */
//{42,21, 0}, {42,42,42}, {21,21,21}, {21,21,63}, {21,63,21},/*  10 */
//{21,63,63}, {63,21,21}, {63,21,63}, {63,63,21}, {63,63,63},/*  15 */
//{19, 0, 0}, {26, 0, 0}, {33, 0, 0}, {41, 1, 0}, {48, 2, 0},/*  20 */
//{55, 4, 0}, {63, 0, 0}, {63,20, 4}, {63,32, 9}, {63,43,14},/*  25 */
//{63,52,19}, {63,60,24}, {60,63,30}, {63,63,63}, {55,58,55},/*  30 */
//{48,52,48}, {41,47,41}, {34,42,34}, {29,37,29}, {23,32,23},/*  35 */
//{18,27,18}, {14,22,14}, {10,17,10}, {63,63,63}, {56,57,60},/*  40 */
//{53,54,58}, {50,52,57}, {47,49,56}, {45,47,55}, {42,45,54},/*  45 */
//{40,43,52}, {37,40,51}, {34,38,50}, {32,36,49}, {30,34,47},/*  50 */
//{28,32,46}, {26,30,45}, {24,29,44}, {22,27,43}, {63,63,63},/*  55 */
//{57,59,59}, {52,54,54}, {47,50,50}, {42,46,46}, {37,42,42},/*  60 */
//{33,38,38}, {29,34,34}, {24,30,30}, {21,26,26}, {17,22,22},/*  65 */
//{13,18,18}, {10,14,14}, { 7,10,10}, { 3, 6, 6}, { 1, 2, 2},/*  70 */
//{63,60,35}, {61,57,33}, {59,54,31}, {57,52,30}, {56,49,29},/*  75 */
//{54,47,27}, {52,44,26}, {51,42,25}, {46,48, 9}, {62,60,41},/*  80 */
//{59,58,40}, {56,56,39}, {53,53,37}, {49,50,36}, {46,47,35},/*  85 */
//{43,44,33}, {39,41,32}, {36,38,30}, {33,35,28}, {55,54,30},/*  90 */
//{51,51,29}, {48,48,29}, {44,44,28}, {40,41,27}, {37,38,26},/*  95 */
//{34,35,25}, {31,32,23}, {28,29,22}, {48,48,29}, {12, 9, 6},/* 100 */
//{13,10, 7}, {15,11, 8}, {17,13, 9}, {18,14,10}, {20,16,10},/* 105 */
//{22,17,12}, {23,19,13}, {25,20,14}, {27,22,15}, {47,32,11},/* 110 */
//{56, 0,63}, {63,21,63}, {63,21,63}, {27,22,15}, {28,23,16},/* 115 */
//{63,21,63}, {63,21,63}, {34,29,20}, {63,63,21}, { 0,42, 0},/* 120 */
//{21,21,63}, { 0, 0,42}, {33,35,28}, {39,41,32}, { 7,55,63},/* 125 */
//{50,52,57}, {57,52,42}, {14, 0, 0}, {20, 0, 0}, {25, 0, 0},/* 130 */
//{31, 1, 0}, {36, 2, 0}, {41, 3, 0}, {47, 0, 0}, {47,15, 3},/* 135 */
//{47,24, 7}, {47,32,11}, {47,39,14}, {47,45,18}, {45,47,23},/* 140 */
//{47,47,47}, {41,44,41}, {36,39,36}, {31,35,31}, {26,32,26},/* 145 */
//{22,28,22}, {17,24,17}, {14,20,14}, {11,17,11}, { 8,13, 8},/* 150 */
//{47,47,47}, {42,43,45}, {40,41,44}, {38,39,43}, {35,37,42},/* 155 */
//{34,35,41}, {32,34,41}, {30,32,39}, {28,30,38}, {26,29,38},/* 160 */
//{24,27,37}, {23,26,35}, {21,24,35}, {20,23,34}, {18,22,33},/* 165 */
//{17,20,32}, {47,47,47}, {43,44,44}, {39,41,41}, {35,38,38},/* 170 */
//{32,35,35}, {28,32,32}, {25,29,29}, {22,26,26}, {18,23,23},/* 175 */
//{16,20,20}, {13,17,17}, {10,14,14}, { 8,11,11}, { 5, 8, 8},/* 180 */
//{ 2, 5, 5}, { 1, 2, 2}, {47,45,26}, {46,43,25}, {44,41,23},/* 185 */
//{43,39,23}, {42,37,22}, {41,35,20}, {39,33,20}, {38,32,19},/* 190 */
//{35,36, 7}, {47,45,31}, {44,44,30}, {42,42,29}, {40,40,28},/* 195 */
//{37,38,27}, {35,35,26}, {32,33,25}, {29,31,24}, {27,29,23},/* 200 */
//{25,26,21}, {41,41,23}, {38,38,22}, {36,36,22}, {33,33,21},/* 205 */
//{30,31,20}, {28,29,20}, {26,26,19}, {23,24,17}, {21,22,17},/* 210 */
//{36,36,22}, {36,31,21}, {38,33,22}, {40,35,23}, {63,21,63},/* 215 */
//{63,21,63}, {46,41,28}, {48,43,29}, {50,45,31}, {52,47,32},/* 220 */
//{54,49,34}, {35,22, 7}, {63,21,63}, {47,47,28}, {63,21,63},/* 225 */
//{63,21,63}, {57,53,36}, {59,55,38}, {61,57,40}, {63,59,42},/* 230 */
//{47,47,16}, { 0,32, 0}, {16,16,47}, { 0, 0,32}, {25,26,21},/* 235 */
//{29,31,24}, {17,41,47}, {38,39,43}, {43,39,32}, {33,35,28},/* 240 */
//{39,41,32}, {63, 8, 8}, {10,49,45}, {10,42,49}, {10,31,49},/* 245 */
//{10,20,49}, {11,10,49}, {22,10,49}, {33,10,49}, {44,10,49},/* 250 */
//{49,10,43}, {49,10,32}, {49,10,21}, {49,10,10}, { 0, 0, 0}};/* 255 */
// end of obsolete code

// pinfo holds the default palette
struct palette pinfo[256] =  {
{   0,   0,   0},{   0,   0, 171},{   0, 171,   0},  // 0-2
{   0, 171, 171},{ 171,   0,   0},{ 171,   0, 171},  // 3-5
{ 171,  87,   0},{ 171, 171, 171},{  87,  87,  87},  // 6-8
{  87,  87, 255},{  87, 255,  87},{  87, 255, 255},  // 9-11
{ 255,  87,  87},{ 255,  87, 255},{ 255, 255,  87},  // 12-14
{ 255, 255, 255},{  79,   0,   0},{ 107,   0,   0},  // 15-17
{ 135,   0,   0},{ 167,   7,   0},{ 195,  11,   0},  // 18-20
{ 223,  19,   0},{ 255,   0,   0},{ 255,  83,  19},  // 21-23
{ 255, 131,  39},{ 255, 175,  59},{ 255, 211,  79},  // 24-26
{ 255, 243,  99},{ 243, 255, 123},{ 255, 255, 255},  // 27-29
{ 223, 235, 223},{ 195, 211, 195},{ 167, 191, 167},  // 30-32
{ 139, 171, 139},{ 119, 151, 119},{  95, 131,  95},  // 33-35
{  75, 111,  75},{  59,  91,  59},{  43,  71,  43},  // 36-38
{ 255, 255, 255},{ 227, 231, 243},{ 215, 219, 235},  // 39-41
{ 203, 211, 231},{ 191, 199, 227},{ 183, 191, 223},  // 42-44
{ 171, 183, 219},{ 163, 175, 211},{ 151, 163, 207},  // 45-47
{ 139, 155, 203},{ 131, 147, 199},{ 123, 139, 191},  // 48-50
{ 115, 131, 187},{ 107, 123, 183},{  99, 119, 179},  // 51-53
{  91, 111, 175},{ 255, 255, 255},{ 231, 239, 239},  // 54-56
{ 211, 219, 219},{ 191, 203, 203},{ 171, 187, 187},  // 57-59
{ 151, 171, 171},{ 135, 155, 155},{ 119, 139, 139},  // 60-62
{  99, 123, 123},{  87, 107, 107},{  71,  91,  91},  // 63-65
{  55,  75,  75},{  43,  59,  59},{  31,  43,  43},  // 66-68
{  15,  27,  27},{   7,  11,  11},{ 255, 243, 143},  // 69-71
{ 247, 231, 135},{ 239, 219, 127},{ 231, 211, 123},  // 72-74
{ 227, 199, 119},{ 219, 191, 111},{ 211, 179, 107},  // 75-77
{ 207, 171, 103},{ 187, 195,  39},{ 251, 243, 167},  // 78-80
{ 239, 235, 163},{ 227, 227, 159},{ 215, 215, 151},  // 81-83
{ 199, 203, 147},{ 187, 191, 143},{ 175, 179, 135},  // 84-86
{ 159, 167, 131},{ 147, 155, 123},{ 135, 143, 115},  // 87-89
{ 223, 219, 123},{ 207, 207, 119},{ 195, 195, 119},  // 90-92
{ 179, 179, 115},{ 163, 167, 111},{ 151, 155, 107},  // 93-95
{ 139, 143, 103},{ 127, 131,  95},{ 115, 119,  91},  // 96-98
{ 195, 195, 119},{  51,  39,  27},{  55,  43,  31},  // 99-101
{  63,  47,  35},{  71,  55,  39},{  75,  59,  43},  // 102-104
{  83,  67,  43},{  91,  71,  51},{  95,  79,  55},  // 105-107
{ 103,  83,  59},{ 111,  91,  63},{ 191, 131,  47},  // 108-110
{ 254, 254, 254},{ 255, 255, 151},{ 255,  87, 255},  // 111-113 111=blink white
                                                     // 112= blink gold
{ 111,  91,  63},{ 115,  95,  67},{ 123, 103,  71},  // 114-116
{ 131, 111,  75},{ 139, 119,  83},{ 255, 255,  87},  // 117-119
{   0, 171,   0},{  87,  87, 255},{   0,   0, 171},  // 120-122
{ 135, 143, 115},{ 159, 167, 131},{  95, 223, 255},  // 123-125
{ 203, 211, 231},{ 231, 211, 171},{  59,   0,   0},  // 126-128
{  83,   0,   0},{ 103,   0,   0},{ 127,   7,   0},  // 129-131
{ 147,  11,   0},{ 167,  15,   0},{ 191,   0,   0},  // 132-134
{ 191,  63,  15},{ 191,  99,  31},{ 191, 131,  47},  // 135-137
{ 191, 159,  59},{ 191, 183,  75},{ 183, 191,  95},  // 138-140
{ 191, 191, 191},{ 167, 179, 167},{ 147, 159, 147},  // 141-143
{ 127, 143, 127},{ 107, 131, 107},{  91, 115,  91},  // 144-146
{  71,  99,  71},{  59,  83,  59},{  47,  71,  47},  // 147-149
{  35,  55,  35},{ 191, 191, 191},{ 171, 175, 183},  // 150-152
{ 163, 167, 179},{ 155, 159, 175},{ 143, 151, 171},  // 153-155
{ 139, 143, 167},{ 131, 139, 167},{ 123, 131, 159},  // 156-158
{ 115, 123, 155},{ 107, 119, 155},{  99, 111, 151},  // 159-161
{  95, 107, 143},{  87,  99, 143},{  83,  95, 139},  // 162-164
{  75,  91, 135},{  71,  83, 131},{ 191, 191, 191},  // 165-167
{ 175, 179, 179},{ 159, 167, 167},{ 143, 155, 155},  // 168-170
{ 131, 143, 143},{ 115, 131, 131},{ 103, 119, 119},  // 171-173
{  91, 107, 107},{  75,  95,  95},{  67,  83,  83},  // 174-176
{  55,  71,  71},{  43,  59,  59},{  35,  47,  47},  // 177-179
{  23,  35,  35},{  11,  23,  23},{   7,  11,  11},  // 180-182
{ 191, 183, 107},{ 187, 175, 103},{ 179, 167,  95},  // 183-185
{ 175, 159,  95},{ 171, 151,  91},{ 167, 143,  83},  // 186-188
{ 159, 135,  83},{ 155, 131,  79},{ 143, 147,  31},  // 189-191
{ 191, 183, 127},{ 179, 179, 123},{ 171, 171, 119},  // 192-194
{ 163, 163, 115},{ 151, 155, 111},{ 143, 143, 107},  // 195-197
{ 131, 135, 103},{ 119, 127,  99},{ 111, 119,  95},  // 198-200
{ 103, 107,  87},{ 167, 167,  95},{ 155, 155,  91},  // 201-203
{ 147, 147,  91},{ 135, 135,  87},{ 123, 127,  83},  // 204-206
{ 115, 119,  83},{ 107, 107,  79},{  95,  99,  71},  // 207-209
{  87,  91,  71},{ 147, 147,  91},{ 147, 127,  87},  // 210-212
{ 155, 135,  91},{ 163, 143,  95},{ 171, 151, 103},  // 213-215
{ 179, 155, 107},{ 187, 167, 115},{ 195, 175, 119},  // 216-218
{ 203, 183, 127},{ 211, 191, 131},{ 219, 199, 139},  // 219-221
{ 143,  91,  31},{ 255,  87, 255},{ 191, 191, 115},  // 222-224 224=blink dark
{ 255,  87, 255},{ 223, 207, 143},{ 231, 215, 147},  // 225-227
{ 239, 223, 155},{ 247, 231, 163},{ 255, 239, 171},  // 228-230
{ 191, 191,  67},{   0, 131,   0},{  67,  67, 191},  // 231-233
{   0,   0, 131},{ 103, 107,  87},{ 119, 127,  99},  // 234-236
{  71, 167, 191},{ 155, 159, 175},{ 175, 159, 131},  // 237-239
{ 135, 143, 115},{ 159, 167, 131},{ 255,  35,  35},  // 240-242
{  43, 199, 183},{  43, 171, 199},{  43, 127, 199},  // 243-245
{  43,  83, 199},{  47,  43, 199},{  91,  43, 199},  // 246-248
{ 135,  43, 199},{ 179,  43, 199},{ 199,  43, 175},  // 249-251
{ 199,  43, 131},{ 199,  43,  87},{ 199,  43,  43},  // 252-254
{ 255, 119, 123}};                                   // 255

Boolean CancelFlag=false;

int tcount;

int icons;
int icon_add[MAX_ICONS];
int icon_pal_add[MAX_ICONS];
int new_icon_add[MAX_ICONS];
int new_icon_pal_add[MAX_ICONS];

int max_width;
int max_height;

int pix_pos;     // x position in pseudo image
int max_pix_x,max_pix_y; //image size info for SP

AnsiString shp_fname;
AnsiString tempname="New_shp.sdf"; // a converted image stored here
AnsiString bignew_name_only="Bignew.shp"; //only name
AnsiString bignew;    // the edited shp file with path
AnsiString start_path;             // startup Directory
AnsiString temp_old_name="~temp.shp"; // name to copy current shp file too
AnsiString edit_path;
AnsiString bmp_path;
AnsiString new_shp="New_shp.shp";

unsigned char image[MAX_WIDTH][MAX_HEIGHT];
struct palette bmpimage[MAX_WIDTH][MAX_HEIGHT];

/*
struct iconheader
{
  int lines;             // this is really the number of lines -1
  int width;
  long var1;
  long xstart;
  long ystart;
  long xend;
  long yend;
}header;
*/

struct iconheader header;

struct BitmapHeader{
//  WORD  bfType;    // we have to omit this because
                     // compiler uses double word alignment adding 2
                     // extra bytes here when turned off by -a2
                     // everythin crashes. Neat.
  DWORD bfSize;
  WORD  bfRes1;
  WORD  bfRes2;
  DWORD bfOffbytes; // where data starts
  DWORD biSize;     // DIB Header size
  DWORD biWidth;    // width of image
  DWORD biHeight;   // height of image
  WORD  biPlanes;   // color planes (1)
  WORD  biBitCount; // bits/pixel (24 for us)
  DWORD biCompress; // compression
  DWORD biImageSize; // the size of image 0x36+this = bfSize
  DWORD biXPels;     // not used
  DWORD biYPels;     // not used
  DWORD biClrUsed;   // not used
  DWORD biClrImport;  // not used
 } ;

struct BitmapHeader bmpheader={ 0,  // size (the BM signature hadled separately
                                0,0,        // reserved
                                0x36,       // where data starts
                                0x28,       // DIB header size
                                0,0,        // width and height
                                1,24,       // planes and bpp
                                0,0         // compression, data size


                               };
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{


}
//---------------------------------------------------------------

// Message Box for Errors
void Error_Message(char *estr)
{
   Application->MessageBox(estr,"Sorry, an error!",MB_OK);


}


//---------------------------------------------------------------------
 // clear the shp out image
void __fastcall TMainForm :: ClearShpImage()
{
   TRect r;

   r.Top=0; r.Left=0;
   r.Bottom=ShpForm->ShpImage->Height;
   r.Right=ShpForm->ShpImage->Width;

   ShpForm->ShpImage->Canvas->Brush->Color=clAqua;
   ShpForm->ShpImage->Canvas->FillRect(r);
   ShpForm->ShpImage->Update();
}

// clear the bmp image
void __fastcall TMainForm :: ClearBmpImage()
{
   TRect r;

   r.Top=0; r.Left=0;
   r.Bottom=BmpForm->BmpImage->Height;
   r.Right=BmpForm->BmpImage->Width;

   BmpForm->BmpImage->Canvas->Brush->Color=clLtGray;
   BmpForm->BmpImage->Canvas->FillRect(r);
   BmpForm->BmpImage->Update();
}


//----------------------------------------------------------------
// take the three values and convert to a color number
long __fastcall rgb(int r, int g, int b)
{
    long clr;

    clr=r;
    clr+=g<<8;
    clr+=b<<16;

    return clr;
}
// -------------------------------------------------
// read next 4 bytes and return as long
// point past the number
long read_long(FILE *inf)
{
  int i;
  long shft[4]={0x1,0x100,0x10000,0x1000000};
  long v=0,ch;

  for (i=0; i<4; ++i)
  {
    ch=fgetc(inf);
    v+=ch*shft[i];
  }
  return v;
}
// ---------------------------------------------------------------
// place the color number in the pseudo image and bump pix_pos
void __fastcall put_pix(int y, int clr)
{
  if (pix_pos>=max_pix_x) max_pix_x=pix_pos+1;  //some SP info
  if (y>=max_pix_y) max_pix_y=y+1;
  image[pix_pos][y]=(unsigned char)clr;
  ++pix_pos;
}

// ----------------------------------------------------------------
// setup the pseudo image as the background byte
void __fastcall  clear_image()
{
  int x,y;

  for (x=0; x<MAX_WIDTH; ++x)
    for (y=0; y<MAX_HEIGHT; ++y)
      image[x][y]=BACK_COLOR;
}
// ----------------------------------------------------------------
// set inf to point to the header first
void read_header(FILE *inf,int n)
{
   fseek(inf,icon_add[n],0);
   header.lines=fgetc(inf)+256*fgetc(inf);
   header.width=fgetc(inf)+256*fgetc(inf);
   header.var1=read_long(inf);
   header.xstart=read_long(inf);
   header.ystart=read_long(inf);
   header.xend=read_long(inf);
   header.yend=read_long(inf);
}

//---------------------------------------------------------------------------
int __fastcall read_palette(FILE *inf,int n)
{
  long clrs;
  int clr_num,i;

  if (n>=icons) return 1;
  for (i=0; i<MAX_COLORS; ++i)
  {
    pal[i].R=0;
    pal[i].G=0;
    pal[i].B=0;
  }
  fseek(inf,icon_pal_add[n],0);
  clrs=read_long(inf);
  for (i=0; i<clrs; ++i)
  {
   clr_num=fgetc(inf);
   if (clr_num>=MAX_COLORS ) clr_num=MAX_COLORS-1; //an error. avoid diaster
   pal[clr_num].R=(unsigned char)(4* fgetc(inf));
   pal[clr_num].G=(unsigned char)(4* fgetc(inf));
   pal[clr_num].B=(unsigned char)(4* fgetc(inf));
  }
  return 0;
}

//-----------------------------------------------------------
// read the shp data (for icon n) into the pseudo image
void __fastcall read_shp(FILE *inf, int n)
{
   int l; // first line the counter
   int lf; // last line
   int ch,b,r,i;


   fseek(inf,icon_add[n]+HEADER_SIZE,0);
   if (header.ystart<0)
   {
   // a trial
    //  lf=header.yend+(header.var1>>16);
    //  l=header.ystart+(header.var1>>16);
    l=0; lf=header.yend+abs(header.ystart);
   }
   else
   {
     l=header.ystart;
     lf=header.yend;
   }
   if (header.xstart<0)
    // a trial
   // pix_pos=header.xstart+(header.var1&0xFFF);
      pix_pos=0;
   else
    pix_pos=header.xstart;
   do
   {
     // skip to xstart
  //   for (i=0; i<header.xstart; ++i)
  //     put_pix(l,BACK_COLOR);

     // read data  and decode
     ch=fgetc(inf);
     r=ch%2;
     b=ch/2;
     if (b==0 && r==1) // a skip over
     {
        ch=fgetc(inf);
        for (i=0; i<ch; ++i)
          put_pix(l,BACK_COLOR);
     }
     else if (b==0)   // end of line
     {
       ++l;
       if (header.xstart<0)
       {
         pix_pos=0;
        // a trial
       // pix_pos=header.xstart+(header.var1&0xFFF);
       }
       else pix_pos=header.xstart;
     }
     else if (r==0) // a run of bytes
     {
       ch=fgetc(inf); // the color #
       for (i=0; i<b; ++i)
        put_pix(l,ch);
     }
     else // b!0 and r==1 ... read the next b bytes as color #'s
     {
       for (i=0; i<b; ++i)
       {
         ch=fgetc(inf);
         put_pix(l,ch);
       }
     }
   } while (l<=lf);
}
//----------------------------------------------------------
void __fastcall  TMainForm :: ShowImage()
{
   int l_max,w_max;
   int y,x,r,g,b;

   l_max=header.lines+1;
   w_max=header.width+1;
   //ShpForm->ShpImage->Width=w_max;
   //ShpForm->ShpImage->Height=l_max;
   ShpForm->ShpImage->Update();
   for ( y=0; y<l_max; ++y)
   {
     for (x=0; x<w_max; ++x)
     {
       if (image[x][y]==BACK_COLOR)
       {
          ShpForm->ShpImage->Canvas->Pixels[x][y]=
            (TColor)RGB(bkcolor.R,bkcolor.G,bkcolor.B);
       }
       else
       {
         r=pal[image[x][y]].R;
         g=pal[image[x][y]].G;
         b=pal[image[x][y]].B;
         ShpForm->ShpImage->Canvas->Pixels[x][y]=(TColor)RGB(r,g,b);
       }

     }
     if (y%10==0) ShpForm->ShpImage->Update();
     if (y%50==0) Application->ProcessMessages();
     if (CancelFlag) return;
   }
}
//----------------------------------------------------------
void __fastcall  TMainForm :: ShowImageAt(int x0, int y0)
{
   int l_max,w_max;
   int y,x,r,g,b;

   l_max=header.lines+1;
   w_max=header.width+1;

   for ( y=0; y<l_max; ++y)
   {
     for (x=0; x<w_max; ++x)
     {
       if (image[x][y]==BACK_COLOR)
       {
          ShpForm->ShpImage->Canvas->Pixels[x+x0][y+y0]=
            (TColor)RGB(bkcolor.R,bkcolor.G,bkcolor.B);
       }
       else
       {
         r=pal[image[x][y]].R;
         g=pal[image[x][y]].G;
         b=pal[image[x][y]].B;
         ShpForm->ShpImage->Canvas->Pixels[x+x0][y+y0]=(TColor)RGB(r,g,b);
       }

     }
     if (y%10==0) ShpForm->ShpImage->Update();
   }
}
// -------------------------------------------------------
void __fastcall TMainForm::LoadShpBtnClick(TObject *Sender)
{
  AnsiString s1,s2;
  int pos,i;
  FILE *inf;
  char error[256];

  if (!autoload)  //skip this for command line
  {
    if (edit_path.Length()>2) OpenDialog1->InitialDir=edit_path;
    OpenDialog1->Filter="shp files (*.shp)| *.SHP| All files	(*.*)|*.*";
    if (!OpenDialog1->Execute()) return;
  }
  shp_fname=OpenDialog1->FileName;
  edit_path=
       OpenDialog1->FileName.
      SubString(1,OpenDialog1->FileName.LastDelimiter("\\"));
  bignew=edit_path+bignew_name_only;
  if (shp_fname.Length()>33)
  {
    s1=shp_fname.SubString(0,12)+"...";
    s2=shp_fname.SubString(shp_fname.Length()-18,19);
  }
  else
  {
    s1=shp_fname;
    s2="";
  }
  EditLbl->Caption="Editing: "+s1+s2;
  MessageMemo->Clear();
  s1=OpenDialog1->FileName;
  pos=s1.LastDelimiter("\\");
  s2=s1.SubString(pos+1,15);

  inf=fopen(s1.c_str(),"rb");
  if (!inf)
  {
   // add some error stuff
   sprintf(error,"Could not open file %s.",s1.c_str());
   return;
  }
  read_long(inf);
  icons=read_long(inf);
  MessageMemo->Update();
  MessageMemo->Lines->Add(s2);
  if (icons>MAX_ICONS)
  {
    MessageMemo->Lines->Add(IntToStr(icons)+" icons exceeds");
    MessageMemo->Lines->Add(IntToStr(MAX_ICONS)+" maximum");
    fclose(inf);
    return;
  }
  MessageMemo->Lines->Add(IntToStr(icons)+" Icons");
  max_height=0; max_width=0;
  for (i=0; i<icons; ++i)
  {
    icon_add[i]=read_long(inf);
    icon_pal_add[i]=read_long(inf);
  }
  for (i=0; i<icons; ++i)
  {
    fseek(inf,icon_add[i],0);
    read_header(inf,i);
    if (header.lines>max_height) max_height=header.lines;
    if (header.width>max_width) max_width=header.width;
  }
  MessageMemo->Lines->Add(IntToStr(max_height)+" Max Height");
  MessageMemo->Lines->Add(IntToStr(max_width)+" Max Width");

  // enable buttons
  ShowBtn->Enabled=true;
  CollageBtn->Enabled=true;
  ViewPalBtn->Enabled=true;


  ImageUpDown->Max=(short)icons;
  //delete
 // InsertUpDown->Max=(short)icons;
  ImageUpDown->Min=1;
  ImageUpDown->Position=1;
  fclose(inf);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowBtnClick(TObject *Sender)
{
  int image_number,i;
  FILE *inf;
  char str[256];

  CancelFlag=false;
  max_pix_x=0; max_pix_y=0;
  ShpForm->Show();     // show the window
  image_number=ImageUpDown->Position-1;
  inf=fopen(shp_fname.c_str(),"rb");
  if (!inf)
  {
    sprintf(str,"Could not open file %s",shp_fname.c_str());
    Error_Message(str);
    return;
  }
  clear_image();
  read_header(inf,image_number);
  if (header.xstart>641 || header.xstart<-100||
               header.ystart>481 || header.ystart<-100)
  {
    MessageMemo->Lines->Add("No image #"+IntToStr(image_number+1));
    fclose(inf);
    return;
  }
  if (header.xstart<0||header.ystart<0)
    MessageMemo->Lines->Add("#"+IntToStr(image_number+1)+" Problem??");

  if (icon_pal_add[image_number]>0 && !FullPalCB->Checked)
      read_palette(inf,image_number);
  else
  for (i=0; i<MAX_COLORS; ++i) // there was no palette use std?
  {
    pal[i].R=pinfo[i].R;
    pal[i].G=pinfo[i].G;
    pal[i].B=pinfo[i].B;
  }
  read_shp(inf,image_number);
  fclose(inf);
  ClearShpImage();
  ShowImage();
  MessageMemo->Lines->Add("cols "+IntToStr(max_pix_x)+", lines "+
    IntToStr(max_pix_y) );
  //enable the save bmp buttons
  WriteBmpBtn->Enabled=true;
  SaveCollageBtn->Enabled=true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::WriteBmpBtnClick(TObject *Sender)
{
   FILE *outf;
   long datasize,x,y;
   int linebyte,pixcount;
   TWaitCursor w;
   char str[256];

   if (bmp_path.Length()>2) SaveDialog1->InitialDir=bmp_path;
   SaveDialog1->Filter="Bitmaps (*.bmp)|*.BMP|All files (*.*)|*.*";
   SaveDialog1->DefaultExt="BMP";
   SaveDialog1->Title="Save Windows Bitmap";
   if (!SaveDialog1->Execute()) return;
   bmp_path=SaveDialog1->FileName.
    SubString(1,SaveDialog1->FileName.LastDelimiter("\\"));

   outf=fopen(SaveDialog1->FileName.c_str(),"wb");
   if (!outf)
   {
     sprintf(str,"Could not open bmp file %s",
          SaveDialog1->FileName.c_str());
     Error_Message(str);     
     return; // add some error
   }
   // put sizes into the header
   // a line must have bytes ending on 4 byte boundary
   linebyte=3*(header.width+1);
   while (linebyte%4) ++linebyte;
   datasize=linebyte*(header.lines+1);
   bmpheader.bfSize=datasize+0x36;
   bmpheader.biImageSize=datasize;
   bmpheader.biHeight=header.lines+1;
   bmpheader.biWidth=header.width+1;
   fputc('B',outf);
   fputc('M',outf);
   fwrite(&bmpheader,sizeof(bmpheader),1,outf);
   for (y=header.lines; y>=0; --y) // write from the bottom
   {
     pixcount=0;
     for (x=0; x<header.width+1; ++x)
     {
      if (image[x][y]==255)    //background color
      {
        fputc(bkcolor.B,outf);
        fputc(bkcolor.G,outf);
        fputc(bkcolor.R,outf);
      }
      else
      {
        fputc(pal[image[x][y]].B,outf);
        fputc(pal[image[x][y]].G,outf);
        fputc(pal[image[x][y]].R,outf);
      }
      pixcount+=3;
     }
     // add bytes at end of line
     while (pixcount%4) { fputc(0,outf); ++pixcount;}
   }
   fclose(outf);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowPaletteBtnClick(TObject *Sender)
{
  int i;
  int xblk,yblk,x0,y0;
  int count;
  TRect rec;

  ClearShpImage();
  ShpForm->Show();
  x0=0; y0=0; yblk=20; xblk=13;
  ShpForm->ShpImage->Canvas->Brush->Color=
     (TColor)RGB(pal[0].R,pal[0].G,pal[0].B);
  rec.Left=x0; rec.Top=y0;
  rec.Bottom=rec.Top+ShpForm->ShpImage->Height/yblk;
  rec.Right=rec.Left+ShpForm->ShpImage->Width/xblk;
  ShpForm->ShpImage->Canvas->FillRect(rec);
  count=1;
  for (i=1; i<254; ++i)
  {
    if ( (pal[i].R +pal[i].G +pal[i].B)>0)
    {
      x0=(count%xblk)*(ShpForm->ShpImage->Width/xblk);
      y0=(count/xblk)*(ShpForm->ShpImage->Height/yblk);
      ShpForm->ShpImage->Canvas->Brush->Color=
         (TColor)RGB(pal[i].R,pal[i].G,pal[i].B);
      rec.Left=x0; rec.Top=y0;
      rec.Bottom=rec.Top+ShpForm->ShpImage->Height/yblk;
      rec.Right=rec.Left+ShpForm->ShpImage->Width/xblk;
      ShpForm->ShpImage->Canvas->FillRect(rec);
      ++count;
    }
  }
 // enable save collage
 SaveCollageBtn->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadBmpBtnClick(TObject *Sender)
{
  FILE *inf;
  int ch1,ch2,x,y;
  int line_length;
  long line_pos;
  TColor clr;
  TWaitCursor w;
  char str[128];

  if (bmp_path.Length()>2) OpenDialog1->InitialDir=bmp_path;
  OpenDialog1->Filter="Windows Bitmap (*.bmp) | *.BMP";
  if (!OpenDialog1->Execute()) return;
  ClearBmpImage();
  bmp_path=OpenDialog1->FileName.
    SubString(1,OpenDialog1->FileName.LastDelimiter("\\"));
  inf=fopen(OpenDialog1->FileName.c_str(),"rb");
  if (!inf)
  {
   sprintf(str,"Could not open %s.",OpenDialog1->FileName.c_str());
   return; // add error code
  }
  fseek(inf,0x12L,0);
  ch1=fgetc(inf); ch2=fgetc(inf); // width data
  bmpheader.biWidth=ch1+256*ch2;
  fseek(inf,0x16L,0);
  ch1=fgetc(inf); ch2=fgetc(inf); // height data
  bmpheader.biHeight=ch1+256*ch2;
  fseek(inf,0x0A,0);
  ch1=fgetc(inf);ch2=fgetc(inf);
  bmpheader.bfOffbytes=ch1+256*ch2; // where data starts

  BmpForm->Show();

  // it would be real nice to load the bitmap using LoadFromFile
  // but there are changes in the color numbers eg
  // background E1E1FF became E4E8FF
  line_length=bmpheader.biWidth*3;
  while (line_length%4) ++line_length;
  for (y=0; y<bmpheader.biHeight; ++y)
  {
    line_pos=bmpheader.bfOffbytes+(bmpheader.biHeight-(y+1))*line_length;
    fseek(inf,line_pos,0);
    for (x=0; x<bmpheader.biWidth; ++ x)
    {
      bmpimage[x][y].B=fgetc(inf);
      bmpimage[x][y].G=fgetc(inf);
      bmpimage[x][y].R=fgetc(inf);
    }
  }
  fclose(inf);
  for (y=0; y<bmpheader.biHeight; ++y)
  {
    for (x=0; x<bmpheader.biWidth; ++x)
    {
      clr=(TColor)bmpimage[x][y].R;
      clr+=(TColor)(bmpimage[x][y].G<<8);
      clr+=(TColor)(bmpimage[x][y].B<<16);
      BmpForm->BmpImage->Canvas->Pixels[x][y]=clr;


    }
    if (y%10==0)BmpForm->BmpImage->Update();
  }
  CvtBmpBtn->Enabled=true;
}
//-------------------------------------------------------
// if this is a flashing color return true
Boolean SP_Flash(int n)
{

  if ((n>111 && n<128) || (n>223) ) return true;
  else
  return false;
}

//---------------------------------------------------------------------------
int __fastcall TMainForm :: match_color(int r,int g,int b)
{
  int i,dr,dg,db;
  int d,min_d,best;


  // we need an exact match for background ... ie color 255
  i=255;
  //d=abs(pinfo[i].R-r)+abs(pinfo[i].G-g)+abs(pinfo[i].B-b);
  //this is fixed with version 0.48d
  d=abs(bkcolor.R-r)+abs(bkcolor.G-g)+abs(bkcolor.B-b);
  if (d==0)
  return 255;

  // but don't look for it again

  for (i=0; i<MAX_COLORS-1; ++i)
  {
    if (SPNoFlashCB->Checked && SP_Flash(i))
      d=100000;
    else
      d=abs(pinfo[i].R-r)+abs(pinfo[i].G-g)+abs(pinfo[i].B-b);
      //d=abs(pal[i].R-r)+abs(pal[i].G-g)+abs(pal[i].B-b);
    if (i==0 || d<min_d)
    {
       min_d=d;
       best=i;
    }

  }
  return best;
}
//-------------------------------------------------------------------
void __fastcall TMainForm::CvtBmpBtnClick(TObject *Sender)
{
   int x,y,cnum,i;
   int xstart,ystart,xend,yend;
   boolean lines_start=false,line_has_pix;
   long color,bclr;
   FILE *outf,*inf;
   int endi, cti;
   unsigned char cmp[2048];
   long data_size;
   TWaitCursor w;
   char str[128];

   header.lines=bmpheader.biHeight-1;
   header.width=bmpheader.biWidth-1;
   bclr=rgb(bkcolor.R,bkcolor.G,bkcolor.B);
   xstart=MAX_WIDTH; xend=0;
   // now we scan the bitmap array to find blank lines at top and bottom
   // and pixels to left and right not used.
   for (y=0; y<bmpheader.biHeight; ++y)
   {
     line_has_pix=false;
     // think need to include = to maintain width
     for (x=0; x<bmpheader.biWidth; ++x)
     {
       color=rgb(bmpimage[x][y].R,bmpimage[x][y].G,bmpimage[x][y].B);
       if (color!=bclr)
       {
         line_has_pix=true;
         if (x>xend) xend=x;
         if (x<xstart) xstart=x;
       }
       if (!lines_start && color!=bclr) // first line
       {
         lines_start=true;
         ystart=y;
       }


     }  // end for x
     if (line_has_pix) yend=y;
   }
  header.xstart=xstart;
  header.xend=xend;
  header.yend=yend;
  header.ystart=ystart;

  // match the colors and put them in image
  clear_image();
  for (y=ystart; y<=yend; ++y)
    for (x=xstart; x<=xend; ++x)
    {
      color=rgb(bmpimage[x][y].R,bmpimage[x][y].G,bmpimage[x][y].B);
      if (color==bclr) cnum=255;
      else cnum=match_color(bmpimage[x][y].R,bmpimage[x][y].G,
                       bmpimage[x][y].B);

      image[x][y]=cnum;
    }
   // copy the complete palette to pal and show the image
   for (i=0; i<MAX_COLORS; ++i)
   {
     pal[i].R=pinfo[i].R;
     pal[i].G=pinfo[i].G;
     pal[i].B=pinfo[i].B;
   }
   pal[MAX_COLORS-1].R=bkcolor.R;
   pal[MAX_COLORS-1].G=bkcolor.G;
   pal[MAX_COLORS-1].B=bkcolor.B;
   ShpForm->Show();
   ClearShpImage();
   ShowImage();

  // take the data in image and convert it, placing in tempname
  outf=fopen(tempname.c_str(),"wb");
  if (!outf)
  {
     sprintf(str,"Could not open %s.",tempname.c_str());
     Error_Message(str);
     return;
  }

    // write a new header
    fputc(header.lines%256,outf);
    fputc(header.lines/256,outf);
    fputc(header.width%256,outf);
    fputc(header.width/256,outf);
    // trial
    // fwrite(&header.var1,4,1);
    fputc(0,outf); fputc(0,outf); fputc(0,outf); fputc(0,outf);
    fputc(header.xstart%256,outf); fputc(header.xstart/256,outf);
    fputc(0,outf); fputc(0,outf);
    fputc(header.ystart%256,outf); fputc(header.ystart/256,outf);
    fputc(0,outf); fputc(0,outf);
    fputc(header.xend%256,outf); fputc(header.xend/256,outf);
    fputc(0,outf); fputc(0,outf);
    fputc(header.yend%256,outf); fputc(header.yend/256,outf);
    fputc(0,outf); fputc(0,outf);

  data_size=HEADER_SIZE;
  //now get info from image and compress to shp format
  for (y=ystart; y<=yend; ++y)
  {
    // compress a line of data
    // we will write a line of compressed data to cmp
    // keeping track of the end position in it with
    // endi and the counter position with cti;
    // x will be the position in image
    x=xstart; endi=0; cti=0;
    do
    {
      cmp[endi]=0;
      if (image[x][y]==BACK_COLOR) // transparent area
      {
        cmp[endi]=1; // ie repeat transparent
        ++endi;
        cti=endi;
        cmp[endi]=0;
        ++endi;     // next place to write in cmp
        cmp[endi]=0;
        //while (image[x][y]==BACK_COLOR && x<=xend) //Version 0.45 <=
        while (image[x][y]==BACK_COLOR && x<=xend && cmp[cti]<255) //Version 0.48g <=
        {
          ++cmp[cti];
          ++x;
        }                 // Version >= npt ==
        if (x>=xend && endi>2)     // this is transparent finishing row;
                         // add && endi>2 for blank line...0.46
        {
         --endi; --endi;
         cmp[endi]=0;
        }
      } // end run of back color
      else if (image[x][y]==image[x+1][y]&&
            image[x][y]==image[x+2][y]) // a run of at least 3 same
      {
        cti=endi;
        ++endi;
        cmp[cti]=2; // even is same
        cmp[endi]=image[x][y];
        cnum=image[x][y];
        ++endi;
        cmp[endi]=0;
        ++x;
       // while (cnum==image[x][y] && x<xend &&cmp[cti]<0xFE) V 0.42
        while (cnum==image[x][y] && x<=xend &&cmp[cti]<0xFE) //V0.45
        {
          ++x;
          cmp[cti]+=2;
        }
      }    // end run of same
      else // a run of different
      {
         cti=endi;
         cmp[cti]=1;  // odd for a run of different
         ++endi;
         while ((image[x][y]!=image[x+1][y]|| image[x][y]!=image[x+2][y])
                   && x<=xend && cmp[cti]<0xFF  //Version 0.45 <= not <
                   && image[x][y]!=BACK_COLOR)  //added 1/5/98
         {
           cmp[cti]+=2;
           cmp[endi]=image[x][y];
           ++endi;
           cmp[endi]=0;
           ++x;
         }
      } // end run of different
   // }while (x<xend); Version 0.42
    }while (x<=xend);  //Version 0.45
    // write the line
    if (endi>0)
    for (i=0; i<=endi; ++i)
    {
      fputc(cmp[i],outf);
      ++data_size;
    }
  }
  fclose(outf);

  // write a test shp file
  inf=fopen(tempname.c_str(),"rb");
  if (!inf)
  {
     sprintf(str,"Could not open file %s.",tempname.c_str());
     Error_Message(str);
     return;
  }
  outf=fopen(new_shp.c_str(),"wb");
  if (!outf)
  {
     fclose(inf);
     sprintf(str,"Could not open file %s.",new_shp.c_str());
     Error_Message(str);
     return;
  }
  // add error

  fputc(0x31,outf); fputc(0x2E,outf); fputc(0x31,outf); fputc(0x30,outf);
  fputc(1,outf); fputc(0,outf); fputc(0,outf); fputc(0,outf);
  fputc(16,outf); fputc(0,outf); fputc(0,outf); fputc(0,outf);  // start
  data_size+=16;  // palette address
  //trial
  fwrite(&data_size,4,1,outf);
  //fputc(data_size%256,outf); fputc(data_size/256,outf);
  //fputc(0,outf); fputc(0,outf);
  for (i=0; i<data_size-16; ++i) //bytes to copy
  {
    fputc(fgetc(inf),outf);
  }
  fclose(inf);

  // write palette
  fputc(240,outf); fputc(0,outf); fputc(0,outf); fputc(0,outf);
  for (i=0; i<240; ++i)
  {
    fputc(i,outf);
    fputc(pinfo[i].R,outf);
    fputc(pinfo[i].G,outf);
    fputc(pinfo[i].B,outf);
  }
  fclose(outf);
  InsertBtn->Enabled=true;
  AddBtn->Enabled=true;

}
//-------------------------------------------------------------------
long next_icon_add(int i)
{
  int n;

  n=i+1;
  while (icon_add[n]<=icon_add[i]) ++n;
  return icon_add[n];
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::InsertBtnClick(TObject *Sender)
{
   // before doing this the shp file to be modified must be loaded
   // the current shp data in tempname will be inserted into shp_fname
   // replacing the icon # selected

   long new_size,old_size;
   FILE *inf_new,*inf_old,*outf;
   int rnum,i,ch;
   long delta;
   TWaitCursor w;
   char str[128];

   inf_new=fopen(tempname.c_str(),"rb");
   if (!inf_new)
   {
    sprintf(str,"Could not open file %s.",tempname.c_str());
    Error_Message(str);
    return;
   }
   new_size=filelength(fileno(inf_new));


   // we need to adjust positions ... this should
   // handle cases when icon is next to a palette

   rnum=ImageUpDown->Position-1;
   if ((rnum+1)==icons)
        old_size=icon_pal_add[rnum]-icon_add[rnum];
   else if (icon_pal_add[rnum]<icon_add[rnum+1] && icon_pal_add[rnum]>0)
        old_size=icon_pal_add[rnum]-icon_add[rnum];
   //else old_size=icon_add[rnum+1]-icon_add[rnum];
   //modified for 0.48c to take care of out of order addresses
   //that were giving the wrong delta
   else old_size=next_icon_add(rnum)-icon_add[rnum];
   delta=new_size-old_size;


   // now construct a new table of addresses
   for (i=0; i<icons; ++i)
   {
//     if (i>rnum) new_icon_add[i]=icon_add[i]+delta;
// changed 0.48b to handle battle.shp that has out of
//order icon addresses !!!
     if (icon_add[i]>icon_add[rnum]) new_icon_add[i]=icon_add[i]+delta;
     else new_icon_add[i]=icon_add[i];

     if (icon_pal_add[i]>icon_add[rnum])
       new_icon_pal_add[i]=delta+icon_pal_add[i];
     else  new_icon_pal_add[i]=icon_pal_add[i];
   }

   // open the old shp file
   inf_old=fopen(shp_fname.c_str(),"rb");
   if (!inf_old)
   {
     sprintf(str,"Could not open file %s.",shp_fname.c_str());
     Error_Message(str);
     fcloseall();
     return;
   }
     
   // here we copy old_shp file being edited to temp_old_name
   outf=fopen(temp_old_name.c_str(),"wb");
   if (!outf)
   {
     sprintf(str,"Could not open file %s.",temp_old_name.c_str());
     Error_Message(str);
     fcloseall();
     return;
   }
   while ((ch=fgetc(inf_old))!=EOF) fputc(ch,outf);
   fclose(outf);
   fclose(inf_old);
   inf_old=fopen(temp_old_name.c_str(),"rb"); //use the temp file as source

   // open the new shp file
   outf=fopen(bignew.c_str(),"wb");
   if (!outf)
   {
     sprintf(str,"Could not open file %s.",bignew.c_str());
     Error_Message(str);
     fcloseall();
     return;
   }


   for (i=0; i<8; ++i)  // copy header and num icons
    fputc(getc(inf_old),outf);

   for (i=0; i<icons; ++i) // write the new address table
   {
     fwrite(&(new_icon_add[i]),4,1,outf);
     fwrite(&(new_icon_pal_add[i]),4,1,outf);
   }
   // now copy the old file to new up to the address of the
   // replace icon
   // the position of outf is now at 1st icon data
   fseek(inf_old,icon_add[0],0);

   // copy up to icon
   while (ftell(inf_old)<icon_add[rnum]) fputc(fgetc(inf_old),outf);

   // copy the temp data file with the new icon info
   fseek(inf_new,0,0);
   if (HeaderCB->Checked) // copy the old header! Steel Panth.
   {
     for (i=0; i<HEADER_SIZE; ++i)
     {
       fputc(fgetc(inf_old),outf);  // copy
       fgetc(inf_new);              // skip
     }
     for (i=0; i<new_size-HEADER_SIZE; ++i)
       fputc(fgetc(inf_new),outf);
   }
   else  // use the new header
   for (i=0; i<new_size; ++i)
     fputc(fgetc(inf_new),outf);
   // now write the rest of the old shp file
   // condition added to fix bug writing last icon (old_size<0)
   // (happens with SP which has no palette) as of Vers 0.48
   if (old_size>0) // if last icon, no more to write
   {
     fseek(inf_old,icon_add[rnum]+old_size,0);
     while ((ch=fgetc(inf_old))!=EOF) fputc(ch,outf);
   }
   fcloseall();

   // Version 0.48 if we are editing bignew, we need to adjust addresses
   if (shp_fname==bignew)
   {
      for (i=0; i<icons; ++i)
      {
        icon_add[i]=new_icon_add[i];
        icon_pal_add[i]=new_icon_pal_add[i];
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadPalBtnClick(TObject *Sender)
{
   FILE *inf;
   int i,clrs,r,g,b;
   char input[128];
   char str[128];

   OpenDialog1->InitialDir=start_path;
   OpenDialog1->Filter=
           "Paintshop pal (*.pal)|*.PAL|All files (*.*)|*.*";
   OpenDialog1->FileName="";

   if (!OpenDialog1->Execute()) return;
   inf=fopen(OpenDialog1->FileName.c_str(),"rt");
   Palette1Name=OpenDialog1->FileName;

   if (!inf)
   {
      sprintf(str,"Could not open file %s.",
        OpenDialog1->FileName.c_str());
      Error_Message(str);
      return;
   }
   fgets(input,127,inf);
   fgets(input,127,inf);
   fgets(input,127,inf); // number of colors
   sscanf(input,"%d",&clrs);
   if (clrs>MAX_COLORS) clrs=MAX_COLORS;
   for (i=0; i<clrs; ++i)
   {
     fgets(input,127,inf);
     sscanf(input,"%d %d %d",&r,&g,&b);
     pinfo[i].R=r;
     pinfo[i].G=g;
     pinfo[i].B=b;
     pal[i].R=r;
     pal[i].G=g;
     pal[i].B=b;

   }
   fclose(inf);
   Palette1Name=ExtractFileName(Palette1Name);
   PaletteLbl->Caption=Palette1Name;
   ViewPalBtn->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AddBtnClick(TObject *Sender)
{
   // stick a converted bitmap on the end of the shp file
   long new_size,new_add;
   FILE *inf_new, *inf_old, *outf;
   long old_icons,new_icons,temp;
   int ch,i;
   TWaitCursor w;
   char str[128];

   // open the temp converted bitmap
   inf_new=fopen(tempname.c_str(),"rb");
   if (!inf_new)
   {
     sprintf(str,"Could not open file %s.",tempname.c_str());
     Error_Message(str);
     fcloseall();
     return;
     return;
   }
   new_size=filelength(fileno(inf_new));

   // open the old shp file
   inf_old=fopen(shp_fname.c_str(),"rb");
   if (!inf_old)
   {
     sprintf(str,"Could not open file %s.",shp_fname.c_str());
     Error_Message(str);
     fcloseall();
     return;
   }
   new_add=filelength(fileno(inf_old))+8; // old file end +8 more in table

   // here we copy old_shp file being edited to temp_old_name
   outf=fopen(temp_old_name.c_str(),"wb");
   if (!outf)
   {
     sprintf(str,"Could not open file %s.",temp_old_name.c_str());
     Error_Message(str);
     fcloseall();
     return;
   }
   while ((ch=fgetc(inf_old))!=EOF) fputc(ch,outf);
   fclose(outf);
   fclose(inf_old);

   // file to copy from
   inf_old=fopen(temp_old_name.c_str(),"rb"); //use the temp file as source
   if (!inf_old)
   {
     sprintf(str,"Could not open file %s.",temp_old_name.c_str());
     Error_Message(str);
     fcloseall();
    }

   // open the new shp file
   outf=fopen(bignew.c_str(),"wb");
   if (!outf)
   {
     sprintf(str,"Could not open file %s.",bignew.c_str());
     Error_Message(str);
     fcloseall();
     return;
   }

   fread(&temp,4,1,inf_old);
   fwrite(&temp,4,1,outf);

   fread(&old_icons,4,1,inf_old);
   new_icons=old_icons+1;
   fwrite(&new_icons,4,1,outf);

   // copy the old table with  to addresses +8
   // since the new table will be 8 bytes bigger
   for (i=0; i<old_icons; ++i)
   {
     // icon add
     fread(&temp,4,1,inf_old);
     temp+=8;
     fwrite(&temp,4,1,outf);
     // palette add
     fread(&temp,4,1,inf_old);
     //added condition in version 0.48e to prevent
     //a fictious palette in SP resulting in problem
     //when inserting.
     if (temp>0) temp+=8;
     fwrite(&temp,4,1,outf);
   }
   // now write the new table entry
   fwrite(&new_add,4,1,outf);
   fwrite(&temp,4,1,outf);  // the palette address
   // copy the old shp file to the new shp file
   while ((ch=fgetc(inf_old))!=EOF) fputc(ch,outf);

   // apend the new data saved in the temp file
   fseek(inf_new,0,0);
   while ((ch=fgetc(inf_new))!=EOF) fputc(ch,outf);
   fcloseall();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AboutBtnClick(TObject *Sender)
{
   char about[256];

   sprintf(about,"Panzer General Shp File Editor\n\
   PG Shp Ed %s\n   Copyright F. P. Chlanda \n\
   June 1999.",Version.c_str());
   Application->MessageBox(about, "About PG Shp Ed",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpBtnClick(TObject *Sender)
{
   Application->HelpJump("Features");
   //HelpForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveImageBtnClick(TObject *Sender)
{
   if (bmp_path.Length()>2) SaveDialog1->InitialDir=bmp_path;
   SaveDialog1->FileName="";
   SaveDialog1->Filter=
    "Windows Bitmaps (*.bmp)|*.BMP|All files (*.*)|*.*";
   SaveDialog1->DefaultExt="*.BMP";
   if (!SaveDialog1->Execute()) return;
   bmp_path=OpenDialog1->FileName.
    SubString(1,OpenDialog1->FileName.LastDelimiter("\\"));
   ShpForm->ShpImage->Picture->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CollageBtnClick(TObject *Sender)
{
   int x0,y0,next_x,next_y=0;
   int i_num, maxy,i;
   FILE *inf;
   //TWaitCursor w;

   CancelFlag=false; // set to true by cancel btn

   x0=0; y0=0;
   i_num=ImageUpDown->Position-1;
   clear_image();
   ClearShpImage();
   ShpForm->Show();     // show the window
   maxy=0;
   do
   {
     clear_image();
     inf=fopen(shp_fname.c_str(),"rb");
     read_header(inf,i_num);
     if (header.xstart>641 || header.xstart<-100||
               header.ystart>481 || header.ystart<-100)
     {
      MessageMemo->Lines->Add("No image #"+IntToStr(i_num+1));
      fclose(inf);
     }

     if (icon_pal_add[i_num]>0 && !FullPalCB->Checked)
      read_palette(inf,i_num);
     else if (x0==0 && y0==0) //do once
     for (i=0; i<MAX_COLORS; ++i) // there was no palette use std?
     {
       pal[i].R=pinfo[i].R;
       pal[i].G=pinfo[i].G;
       pal[i].B=pinfo[i].B;
     }
     read_shp(inf,i_num);
     fclose(inf);

     Application->ProcessMessages();
     if (CancelFlag) return;

     if ((header.lines+1)>maxy) maxy=header.lines+1;
     next_x=x0+header.width+2;
     if (next_x>=MAX_WIDTH) // start a new line
     {


      y0+=maxy+1;
      next_y=y0+header.lines+1;
      x0=0;
      next_x=x0+header.width+2;
      maxy=0;
     }
     if (next_y<MAX_HEIGHT)
     {
       ShowImageAt(x0,y0);
     }
     ++i_num;
     x0=next_x;

   } while (next_y<MAX_HEIGHT && i_num<icons);
   if (i_num<icons)  --i_num;
   MessageMemo->Lines->Add("Last #"+IntToStr(i_num));

   //enable buttons
   SaveCollageBtn->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{

   int i,r,g,b,clrs;
   char input[256];
   FILE *inf;
   int infh;

   // Set up help
  // Application->HelpFile="Shped050.hlp";
    KeyPreview = true;   //get the F1 for help

   // setup to write temp files to home directory
   start_path=ParamStr(0).SubString(1,ParamStr(0).LastDelimiter("\\"));
   tempname=start_path+tempname;
   temp_old_name=start_path+temp_old_name;

   // show the Inrobitmap
   IntroImage->Top=8;
   IntroImage->Left=35;
   IntroImage->Width=325;
   IntroImage->Height=200;
   IntroImage->BringToFront();
   // some controls show thru!
   ImageEdit->Visible=false;
   ImageUpDown->Visible=false;
   MessageMemo->Visible=false;
   HeaderCB->Visible=false;
   FullPalCB->Visible=false;
   SPNoFlashCB->Visible=false;
   //set a timer in case some doesn't know enough to click
   Timer1->Enabled=true;
   tcount=0;

  //disable the buttons taht can't be used yet
   ShowBtn->Enabled=false;
   CollageBtn->Enabled=false;
   WriteBmpBtn->Enabled=false;
   SaveCollageBtn->Enabled=false;
   CvtBmpBtn->Enabled=false;
   InsertBtn->Enabled=false;
   AddBtn->Enabled=false;
   ViewPalBtn->Enabled=false;

   //Load info from the config file if there
   //is one and it is active
   AnsiString Pstr=ExtractFileDir(ParamStr(0));
   cfgName=Pstr+"\\"+cfgName;
   inf=fopen(cfgName.c_str(),"rt");

   if (inf)  //if there is a config file read it
   {
      fgets(input,255,inf);       //if line 1 is 0 don't use file
      sscanf(input,"%d",&cfgFlag);
      if (cfgFlag) //use the config files if enabled
      {
        //get the palette names
        fgets(input,255,inf);
        AnsiString P1(input);
        Palette1Name=Pstr+"\\"+P1.TrimRight();
        fgets(input,255,inf);
        AnsiString P2(input);
        Palette2Name=Pstr+"\\"+P2.TrimRight();
        //read window positions
        fgets(input,255,inf);   //main
        sscanf(input,"%d %d",&MainWinX,&MainWinY);
        fgets(input,255,inf);   //bmp
        sscanf(input,"%d %d",&BmpWinX,&BmpWinY);
        fgets(input,255,inf);   //shp
        sscanf(input,"%d %d",&ShpWinX,&ShpWinY);
        fgets(input,255,inf);   //fix
        sscanf(input,"%d %d",&FixWinX,&FixWinY);
        fgets(input,255,inf);   //transfer
        sscanf(input,"%d %d",&TransWinX,&TransWinY);
      }
      fclose(inf);

   } //end read config file
   //set window positions
   if (cfgFlag)
   {
       MainForm->Top=MainWinY;
       MainForm->Left=MainWinX;
       //we will set others on activate
    }
    // load palette 1 the main palette
    if (cfgFlag)
    {
       inf=fopen(Palette1Name.c_str(),"rt");
       if (inf)
       {
          fgets(input,127,inf);
          fgets(input,127,inf);
          fgets(input,127,inf); // number of colors
          sscanf(input,"%d",&clrs);
          if (clrs>MAX_COLORS) clrs=MAX_COLORS;
          for (i=0; i<clrs; ++i)
          {
            fgets(input,127,inf);
            sscanf(input,"%d %d %d",&r,&g,&b);
            pinfo[i].R=r;
            pinfo[i].G=g;
            pinfo[i].B=b;
            pal[i].R=r;
            pal[i].G=g;
            pal[i].B=b;
          }
          fclose(inf);
          Palette1Name=ExtractFileName(Palette1Name);
          PaletteLbl->Caption=Palette1Name;
          FullPalCB->Checked=true;
          ViewPalBtn->Enabled=true;
      }  // end load palette  if possible
      Palette1Name=ExtractFileName(Palette1Name);
      Palette2Name=ExtractFileName(Palette2Name);


   }
   //try to load a shp file if it is passed on the command line
   AnsiString PrStr=ParamStr(1).LowerCase();
   PrStr=ExtractFileExt(PrStr);
   if (ParamCount()>0 && PrStr==".shp")
   {
     autoload=true; //flag to skip open dialog in file load
     OpenDialog1->FileName=ParamStr(1).LowerCase();
     LoadShpBtnClick(Sender);
     autoload=false;
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMainForm::CancelBtnClick(TObject *Sender)
{
   CancelFlag=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IntroImageClick(TObject *Sender)
{
   IntroImage->Visible=false;
   IntroImage->Width=0;
  // some controls show thru! Restore them
  ImageEdit->Visible=true;
  ImageUpDown->Visible=true;
  MessageMemo->Visible=true;
  HeaderCB->Visible=true;
  FullPalCB->Visible=true;
  SPNoFlashCB->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
  ++tcount;
  if (tcount>9)
  {
   Timer1->Enabled=false;
   if (IntroImage->Visible)
   IntroImage->OnClick(Sender);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
  if (Key==VK_F1) HelpBtn->OnClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SPFixBtnClick(TObject *Sender)
{
   SPFix->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
   FILE *outf;

   //write the configuartion file
   if (cfgFlag)
   {
     
     outf=fopen(cfgName.c_str(),"wt");
     fprintf(outf,"%d\n",cfgFlag);
     fprintf(outf,"%s\n",Palette1Name.c_str());
     fprintf(outf,"%s\n",Palette2Name.c_str());
     fprintf(outf,"%d %d\n", MainForm->Left,MainForm->Top);
     fprintf(outf,"%d %d\n", BmpForm->Left,BmpForm->Top);
     fprintf(outf,"%d %d\n", ShpForm->Left,ShpForm->Top);
     fprintf(outf,"%d %d\n", SPFix->Left,SPFix->Top);
     fprintf(outf,"%d %d\n", TransForm->Left,TransForm->Top);
     fclose(outf);
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TransBtnClick(TObject *Sender)
{
  TransForm->Show();      
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MessageMemoKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_F1) HelpBtn->OnClick(Sender);    
}
//---------------------------------------------------------------------------

