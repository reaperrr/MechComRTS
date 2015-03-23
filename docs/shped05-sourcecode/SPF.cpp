//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "SPF.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSPFix *SPFix;

// User variables
int far_right;
int far_bottom;

//---------------------------------------------------------------------------
__fastcall TSPFix::TSPFix(TComponent* Owner)
	: TForm(Owner)
{
}
//----------------------------------------------------------
void __fastcall  TSPFix :: ShowMagImage()
{
   int l_max,w_max;
   int y,x;          // in virtual image
   int sx,sy;        // in display window
   int r,g,b;
   int yi,xi;

   l_max=header.lines+1;
   w_max=header.width+1;
   //ShpForm->ShpImage->Width=w_max;
   //ShpForm->ShpImage->Height=l_max;
   //ShpForm->ShpImage->Update();
   for ( y=0; y<l_max; ++y)
   {
     sy=3*y+1;
     for (x=0; x<w_max; ++x)
     {
       if (image[x][y]==BACK_COLOR)
       {
          sx=3*x+1;
          for (xi=sx-1; xi<sx+2; ++xi)
            for (yi=sy-1; yi<sy+2; ++yi)
             MagImage->Canvas->Pixels[xi][yi]=
              (TColor)RGB(bkcolor.R,bkcolor.G,bkcolor.B);
       }
       else
       {
         r=pal[image[x][y]].R;
         g=pal[image[x][y]].G;
         b=pal[image[x][y]].B;
         sx=3*x+1;
          for (xi=sx-1; xi<sx+2; ++xi)
            for (yi=sy-1; yi<sy+2; ++yi)
             MagImage->Canvas->Pixels[xi][yi]=
              (TColor)RGB(r,g,b);
       }

     }
     if (y%10==0) MagImage->Update();
     if (y%50==0) Application->ProcessMessages();
   }
}


//---------------------------------------------------------------------------
// read the shp data (for icon n) into the pseudo image
// this does not use the header info for lines, but reads
// until it finds KEY BYTE 88 Next byte 0.
void __fastcall read_SPicon_shp(FILE *inf, int n)
{
   int ch,b,r,i,l=0;
   long fpos;

   fseek(inf,icon_add[n]+HEADER_SIZE,0);
   pix_pos=0;
   far_right=0;
   far_bottom=0;
   do
   {
     // read data  and decode
     ch=fgetc(inf);

     //==== this section checks for end =====
     if (ch==-1) break;// for last image this is end of shp
     fgetpos(inf,&fpos);
     if ((n<(icons-1)) && fpos>icon_add[n+1]) break;
     // ==== end of end check ===========
     r=ch%2;
     b=ch/2;
     if (b==0 && r==1) // a skip over
     {
        ch=fgetc(inf);
        for (i=0; i<ch; ++i)
          put_pix(l,BACK_COLOR);
        if (pix_pos>far_right) far_right=pix_pos;
     }
     else if (b==0)   // end of line
     {
       ++l;
       pix_pos=0;
     }
     else if (r==0) // a run of bytes
     {
       ch=fgetc(inf); // the color #
       for (i=0; i<b; ++i)
        put_pix(l,ch);
       if (pix_pos>far_right) far_right=pix_pos;
     }
     else // b!0 and r==1 ... read the next b bytes as color #'s
     {
       for (i=0; i<b; ++i)
       {
         ch=fgetc(inf);
         put_pix(l,ch);
       }
       if (pix_pos>far_right) far_right=pix_pos;
     }
   } while (true); //exit this loop with break
   far_bottom=l;
}
//--------------------------------------------------------------------
// draw a line through image along passed y
void __fastcall TSPFix::Yline(int y)
{
  int xf,sy;

  //remember we are 3x scale and write in middle
  sy=3*y+1;
  xf=MagImage->Width;
  MagImage->Canvas->Pen->Width=1;
  MagImage->Canvas->Pen->Color=clAqua;
  MagImage->Canvas->MoveTo(0,sy);
  MagImage->Canvas->LineTo(xf,sy);
}
//---------------------------------------------
// remove the line by reading pixels above line pixels
void __fastcall TSPFix::UnYline(int y)
{
  int src_y, des_y,x,xf;
  TColor clr;

  des_y=3*y+1;
  src_y=des_y-1;
  xf=MagImage->Width;

  for (x=0; x<xf; ++x)
  {
    clr=MagImage->Canvas->Pixels[x][src_y];
   // if (clr==clAqua && x>0)
   // clr=MagImage->Canvas->Pixels[x-1][src_y];
    MagImage->Canvas->Pixels[x][des_y]=clr;
  }

}
//-----------------------------------------------------------------
// remove vertical line by reading pixels feft of line pixels
void __fastcall TSPFix::UnXline(int x)
{
  int src_x, des_x,y,yf;
  TColor clr;

  des_x=3*x+1;
  src_x=des_x-1;
  yf=MagImage->Height;

  for (y=0; y<yf; ++y)
  {
    clr=MagImage->Canvas->Pixels[src_x][y];
   // if (clr==clAqua && y>0)
   // clr=MagImage->Canvas->Pixels[src_x][y-1];
    MagImage->Canvas->Pixels[des_x][y]=clr;
  }

}
//-----------------------------------------------------------------

void __fastcall TSPFix::Xline(int x)
{
  int yf,sx;

  //remember we are 3x scale and write in middle
  sx=3*x+1;
  yf=MagImage->Height;
  MagImage->Canvas->Pen->Width=1;
  MagImage->Canvas->Pen->Color=clAqua;
  MagImage->Canvas->MoveTo(sx,0);
  MagImage->Canvas->LineTo(sx,yf);
}
//-----------------------------------------------------------------


void __fastcall TSPFix::MagShowBtnClick(TObject *Sender)
{
  int image_number,i;
  int tx,ty;
  FILE *inf;
  char str[256];

  max_pix_x=0; max_pix_y=0;
  image_number=MainForm->ImageUpDown->Position-1;
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
    MainForm->MessageMemo->Lines->Add("No image #"+IntToStr(image_number+1));
    fclose(inf);
    return;
  }
  if (header.xstart<0||header.ystart<0)
    MainForm->MessageMemo->Lines->Add("#"+IntToStr(image_number+1)+" SP Icon");

  if (icon_pal_add[image_number]>0 && !MainForm->FullPalCB->Checked)
      read_palette(inf,image_number);
  else
  for (i=0; i<MAX_COLORS; ++i) // there was no palette use std?
  {
    pal[i].R=pinfo[i].R;
    pal[i].G=pinfo[i].G;
    pal[i].B=pinfo[i].B;
  }
  read_SPicon_shp(inf,image_number);
  fclose(inf);
  //ClearShpImage();
  //ShowImage();
  MainForm->MessageMemo->Lines->Add("cols "+IntToStr(max_pix_x)+", lines "+
    IntToStr(max_pix_y) );


   // set the values for the header display
   OldXSizeEdit->Text=IntToStr(header.lines);
   OldYSizeEdit->Text=IntToStr(header.width);
   OldXOffsEdit->Text=IntToStr(header.var1&0xFFFF);
   OldYOffsEdit->Text=IntToStr(header.var1>>16);
   OldLeftEdit->Text=IntToStr(header.xstart);
   OldTopEdit->Text=IntToStr(header.ystart);
   OldRightEdit->Text=IntToStr(header.xend);
   OldBottomEdit->Text=IntToStr(header.yend);

   NewRightEdit->Text=IntToStr(header.xend);
   NewBottomEdit->Text=IntToStr(header.yend);
   NewXSizeEdit->Text=IntToStr(header.lines);
   NewYSizeEdit->Text=IntToStr(header.width);
   NewXOffsEdit->Text=IntToStr(header.var1&0xFFFF);
   NewYOffsEdit->Text=IntToStr(header.var1>>16);
   NewLeftEdit->Text=IntToStr(header.xstart);
   NewTopEdit->Text=IntToStr(header.ystart);

   YUpDown->Position=header.ystart;
   XUpDown->Position=header.xstart;
   
   tx=far_right-abs(header.xstart)-1;
   NewRightEdit->Text=IntToStr(tx);
   ty=far_bottom-abs(header.ystart)-1;
   NewBottomEdit->Text=IntToStr(ty);

   HeightEdit->Text=IntToStr(far_bottom);
   WidthEdit->Text=IntToStr(far_right);

   ShowMagImage();

   tx=abs(StrToInt(NewLeftEdit->Text));//+2;
   Xline(tx);
   ty=abs(StrToInt(NewTopEdit->Text));//+2;
   Yline(ty);

}
//---------------------------------------------------------------------------
void __fastcall TSPFix::XUpDownClick(TObject *Sender, TUDBtnType Button)
{
   int left,right,tx;

   left=StrToInt(NewLeftEdit->Text);
   right=StrToInt(NewRightEdit->Text);

   // undraw the line
   tx=abs(StrToInt(NewLeftEdit->Text));//+2;
   UnXline(tx);

   if (Button==btNext) // ie right
   {
     if (right>0)
     {
       --right;
       --left;
     }
   }
   else
   {
     if (left<0)
     {
      ++right;
      ++left;
     }
   }
   NewLeftEdit->Text=IntToStr(left);
   NewRightEdit->Text=IntToStr(right);
   tx=abs(StrToInt(NewLeftEdit->Text));//+2;
   Xline(tx);

}
//---------------------------------------------------------------------------
void __fastcall TSPFix::YUpDownClick(TObject *Sender, TUDBtnType Button)
{

   int top,bottom,ty;

   top=StrToInt(NewTopEdit->Text);
   bottom=StrToInt(NewBottomEdit->Text);

   // undraw the line
   ty=abs(StrToInt(NewTopEdit->Text));//+2;
   UnYline(ty);

   if (Button==btNext) // ie up
   {
     ++top;
     ++bottom;
   }
   else
   {
     --top;
     --bottom;
   }
   NewTopEdit->Text=IntToStr(top);
   NewBottomEdit->Text=IntToStr(bottom);
   ty=abs(StrToInt(NewTopEdit->Text));//+2;
   Yline(ty);

}
//---------------------------------------------------------------------------
void __fastcall TSPFix::FormActivate(TObject *Sender)
{
  NameLbl->Caption=MainForm->EditLbl->Caption;
  NumberLbl->Caption="#"+MainForm->ImageEdit->Text;
  
}
//---------------------------------------------------------------------------
void __fastcall TSPFix::WriteBtnClick(TObject *Sender)
{
  FILE *outf;
  short width,height,xoffs,yoffs;
  long left,top,right,bottom;
  int number;
  char str[128];

  number=StrToInt(MainForm->ImageEdit->Text);
  outf=fopen(shp_fname.c_str(),"r+b");
  if (!outf)
  {
    sprintf(str,"Could not open file %s",shp_fname.c_str());
    Error_Message(str);
    return;
  }
  // read each field from edits and write
  width=StrToInt(NewXSizeEdit->Text);
  height=StrToInt(NewYSizeEdit->Text);
  xoffs=StrToInt(NewXOffsEdit->Text);
  yoffs=StrToInt(NewYOffsEdit->Text);
  left=StrToInt(NewLeftEdit->Text);
  top=StrToInt(NewTopEdit->Text);
  right=StrToInt(NewRightEdit->Text);
  bottom=StrToInt(NewBottomEdit->Text);

  // write each
  fseek(outf,icon_add[number-1],0);
  fwrite(&width,2,1,outf);
  fwrite(&height,2,1,outf);
  fwrite(&xoffs,2,1,outf);
  fwrite(&yoffs,2,1,outf);
  fwrite(&left,4,1,outf);
  fwrite(&top,4,1,outf);
  fwrite(&right,4,1,outf);
  fwrite(&bottom,4,1,outf);

  fclose(outf);


}
//---------------------------------------------------------------------------
void __fastcall TSPFix::FormCreate(TObject *Sender)
{
  SPFix->Top=FixWinY;
  SPFix->Left=FixWinX;
}
//---------------------------------------------------------------------------
void __fastcall TSPFix::FormClose(TObject *Sender, TCloseAction &Action)
{
   FixWinY=SPFix->Top;
   FixWinX=SPFix->Left;
}
//---------------------------------------------------------------------------
