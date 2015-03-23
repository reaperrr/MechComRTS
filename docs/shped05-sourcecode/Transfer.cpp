//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <io.h>
#include "Transfer.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTransForm *TransForm;

AnsiString TempName("TransTmp.sdf");
AnsiString CopyString;

struct palette src_pal[256]; //the source palette

//---------------------------------------------------------------------------
__fastcall TTransForm::TTransForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTransForm::FormCreate(TObject *Sender)
{
   TransForm->Top=TransWinY;
   TransForm->Left=TransWinX;

   TransGrid->Width=427;
   TransGrid->ColWidths[0]=120;
   TransGrid->ColWidths[1]=100;
   TransGrid->ColWidths[2]=40;
   TransGrid->ColWidths[3]=100;
   TransGrid->ColWidths[4]=40;

   TransGrid->Cells[0][0]="Description";
   TransGrid->Cells[1][0]="Dest File";
   TransGrid->Cells[2][0]="D. I#";
   TransGrid->Cells[3][0]="Src File";
   TransGrid->Cells[4][0]="Src I#";

}
//---------------------------------------------------------------------------
void __fastcall TTransForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   TransWinY=TransForm->Top;
   TransWinX=TransForm->Left;
}
//---------------------------------------------------------------------------
void __fastcall TTransForm::TransSelection(int select)
{
   FILE *srcf,*tempf,*destf,*bnewf;
   int start_addr,iaddr,old_addr;
   int old_icon_size,replace_icon_number,new_icon_size,delta_size;
   int r,b,ch,l,lf,i;

   AnsiString SrcName;
   AnsiString DestName;
   AnsiString NewName("dest\\new.shp");
   int src_icon_number,src_total_icons,total_dest_icons;
   char cstr[256];
   struct iconheader iheader;

   // we will extract the target icon from srcf and copy
   //it to tempf. Then destf and tempf file will be
   //combined to make the new file bnewf. finally destf
   //will be removed and bnewf renamed to destf

   if (!SetCurrentDirectory(start_path.c_str()))
   {
      sprintf(cstr,"Could not set path %s. Aborting.",start_path.c_str());
      Application->MessageBox(cstr,"File Error",MB_OK);
      return;
   }
   //do line 1...expand later
   SrcName="source\\"+TransGrid->Cells[3][select]+".shp";
   //get the icon number etc from the table
   src_icon_number=StrToInt(TransGrid->Cells[4][select]);
   FromLbl->Caption=SrcName;
   //open the src
   srcf=fopen(SrcName.c_str(),"rb");
   if (!srcf) {
      sprintf(cstr,"Could not open %s. Aborting.",SrcName.c_str());
      Application->MessageBox(cstr,"File Error",MB_OK);
      return;
   }

   //get start address
   fseek(srcf,4,0);
   fread(&src_total_icons,4,1,srcf);
   if (!(src_icon_number<src_total_icons))
   {
     fclose(srcf);
     sprintf(cstr,"Icon %d of %d does not exist. Aborting.",
        src_icon_number,src_total_icons);
      Application->MessageBox(cstr,"Input Error",MB_OK);
      return;
   }
   fseek(srcf,8+8*src_icon_number,0);
   fread(&start_addr,4,1,srcf);

   //read the header
   fseek(srcf,start_addr,0);
   iheader.lines=fgetc(srcf)+256*fgetc(srcf);
   iheader.width=fgetc(srcf)+256*fgetc(srcf);
   fread(&iheader.var1,4,1,srcf);
   fread(&iheader.xstart,4,1,srcf);
   fread(&iheader.ystart,4,1,srcf);
   fread(&iheader.xend,4,1,srcf);
   fread(&iheader.yend,4,1,srcf);

   //open the temp for writing
   tempf=fopen(TempName.c_str(),"wb");
   if (!tempf)
   {
     fclose(srcf);
     sprintf(cstr,"Couldn't open temp file %s. Aborting.",TempName.c_str());
     Application->MessageBox(cstr,"File Error",MB_OK);
     return;

   }
   //copy the header
   fwrite(&iheader.lines,2,1,tempf);
   fwrite(&iheader.width,2,1,tempf);
   fwrite(&iheader.var1,4,1,tempf);
   fwrite(&iheader.xstart,4,1,tempf);
   fwrite(&iheader.ystart,4,1,tempf);
   fwrite(&iheader.xend,4,1,tempf);
   fwrite(&iheader.yend,4,1,tempf);

   //write the rest of the temp file
   fseek(srcf,start_addr+HEADER_SIZE,0);
   if (iheader.ystart<0)
   {
      l=0;
      lf=iheader.yend+abs(iheader.ystart);
   }
   else
   {
     l=iheader.ystart;
     lf=iheader.yend;
   }

   do
   {
     // read data and write and decode
     ch=fgetc(srcf);
     fputc(ch,tempf);
     r=ch%2;
     b=ch/2;
     if (b==0 && r==1) // a skip over
     {
        ch=fgetc(srcf);
        fputc(ch,tempf);
     }
     else if (b==0)   // end of line
     {
       ++l;

     }
     else if (r==0) // a run of bytes
     {
       ch=fgetc(srcf); // the color #
       //do a palette conversion here if needed
       if (PaletteCB->Checked)
         ch=match_color(src_pal[ch].R,src_pal[ch].G,src_pal[ch].B);
       fputc(ch,tempf);
     }
     else // b!0 and r==1 ... read the next b bytes as color #'s
     {
       for (i=0; i<b; ++i)
       {
         ch=fgetc(srcf);
         //do a palette conversion here
         if (PaletteCB->Checked)
          ch=match_color(src_pal[ch].R,src_pal[ch].G,src_pal[ch].B);
         fputc(ch,tempf);
       }
     }
   } while (l<=lf);
   fclose(srcf);
   fclose(tempf);

   //--------------------------------------------------------------

   //now insert the image in the temp file into the dest icon file
   //open all the files
   //we will write the new.shp using the single new icon in
   //TempName and the rest of the icons in DestName

   bnewf=fopen(NewName.c_str(),"w+b");
   if (!bnewf)
   {
      sprintf(cstr,"Could not open bignew.shp. Aborting.");
      Application->MessageBox(cstr,"File Error",MB_OK);
      return;
   }
   replace_icon_number=StrToInt(TransGrid->Cells[2][select]);
   DestName="dest\\"+TransGrid->Cells[1][select]+".shp";
   ToLbl->Caption=DestName;
   destf=fopen(DestName.c_str(),"rb");
   if (!destf)
   {
      fclose(bnewf);
      sprintf(cstr,"Could not open %s. Aborting.",DestName.c_str());
      Application->MessageBox(cstr,"File Error",MB_OK);
      return;
   }
   tempf=fopen(TempName.c_str(),"rb");
   if (!tempf)
   {
      fclose(bnewf);
      fclose(destf);
      sprintf(cstr,"Could not open %s. Aborting.",TempName.c_str());
      Application->MessageBox(cstr,"File Error",MB_OK);
      return;
   }

   //---------------------------------------------------------
   //copy the first part of destf to bignew until getting to
   //the icon to be replaced.
   fseek(destf,4,0);
   fread(&total_dest_icons,4,1,destf);
   if (!(replace_icon_number<total_dest_icons))
   {
     fclose(destf);
     fclose(tempf);
     fclose(bnewf);
     sprintf(cstr,"Icon %d does not exist in %s",
        replace_icon_number,DestName.c_str());
     Application->MessageBox(cstr,"Input Error",MB_OK);
     return;
   }
   fseek(destf,8*replace_icon_number+8,0);
   fread(&iaddr,4,1,destf);

   rewind(destf);
   for (i=0; i<iaddr; ++i)
     fputc(fgetc(destf),bnewf);

   //-----------------------------------------------------
   //now read through the icon that is to be replaced
   //in dest file to get its size and position the file
   //pointer past the data

   //read the header
   iheader.lines=fgetc(destf)+256*fgetc(destf);
   iheader.width=fgetc(destf)+256*fgetc(destf);
   fread(&iheader.var1,4,1,destf);
   fread(&iheader.xstart,4,1,destf);
   fread(&iheader.ystart,4,1,destf);
   fread(&iheader.xend,4,1,destf);
   fread(&iheader.yend,4,1,destf);

   //read through the image data
   old_icon_size=HEADER_SIZE;
   if (iheader.ystart<0)
   {
      l=0;
      lf=iheader.yend+abs(iheader.ystart);
   }
   else
   {
     l=iheader.ystart;
     lf=iheader.yend;
   }

   do
   {
     // read data and write and decode
     ch=fgetc(destf);
     ++old_icon_size;
     r=ch%2;
     b=ch/2;
     if (b==0 && r==1) // a skip over
     {
        ch=fgetc(destf);
        ++old_icon_size;
     }
     else if (b==0)   // end of line
     {
       ++l;

     }
     else if (r==0) // a run of bytes
     {
       ch=fgetc(destf); // the color #
       ++old_icon_size;
     }
     else // b!0 and r==1 ... read the next b bytes as color #'s
     {
       for (i=0; i<b; ++i)
       {
         ch=fgetc(destf);
         ++old_icon_size;
       }
     }
   } while (l<=lf);

   //get the adjustment for addresses
   new_icon_size=filelength(fileno(tempf));
   delta_size=new_icon_size-old_icon_size;

   //now append the new icon to bignew
   for (i=0; i<new_icon_size; ++i)
     fputc(fgetc(tempf),bnewf);

   //copy the rest of destf to the end of bnewf
   ch=0;
   while (ch!=EOF)
   {
     ch=fgetc(destf);
     if (ch!=EOF) fputc(ch,bnewf);
   }

   // fix up the addesses in bignew
   fclose(tempf);
   fclose(destf);
   //do icon addresses and palette
   for (i=0; i<total_dest_icons; ++i)
   {
      //icon address
      fseek(bnewf,i*8+8,0);
      fread(&old_addr,4,1,bnewf);
      if (old_addr>iaddr)
      {
        old_addr+=delta_size;
        fseek(bnewf,i*8+8,0);
        fwrite(&old_addr,4,1,bnewf);
      }
      //palette address
      fseek(bnewf,i*8+12,0);
      fread(&old_addr,4,1,bnewf);
      if (old_addr>iaddr)
      {
        old_addr+=delta_size;
        fseek(bnewf,i*8+12,0);
        fwrite(&old_addr,4,1,bnewf);
      }
   }

   fclose(bnewf);
   //done except for renaming
   remove(DestName.c_str());
   rename(NewName.c_str(),DestName.c_str());
   FromLbl->Caption=SrcName+" Icon "+IntToStr(src_icon_number);
   ToLbl->Caption=DestName+" Icon "+IntToStr(replace_icon_number);
   TransForm->Update();
}
//---------------------------------------------------------------------
void __fastcall TTransForm::TransBtnClick(TObject *Sender)
{
   int row;

   if (AutoCB->Checked) row=1;
   else row=TransGrid->Row;
   do
   {
     if ( TransGrid->Cells[1][row].IsEmpty()    //return if a grid spot is blank
          ||TransGrid->Cells[2][row].IsEmpty()
          ||TransGrid->Cells[3][row].IsEmpty()
          ||TransGrid->Cells[4][row].IsEmpty() ) return;
        TransSelection(row);
        ++row;
    }while (AutoCB->Checked); //if not checked we exit after one
}
//---------------------------------------------------------------------------


void __fastcall TTransForm::TransGridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (!(Shift.Contains(ssCtrl))) return;
   if (Key==67)
     CopyString=TransGrid->Cells[TransGrid->Col][TransGrid->Row];
   if (Key==86)
     TransGrid->Cells[TransGrid->Col][TransGrid->Row]=CopyString;
}
//---------------------------------------------------------------------------
int __fastcall TTransForm::match_color(int r, int g, int b)
{
  int i,dr,dg,db;
  int d,min_d,best;

  // don't match to 255
   for (i=0; i<MAX_COLORS-1; ++i)
  {
    d=abs(pinfo[i].R-r)+abs(pinfo[i].G-g)+abs(pinfo[i].B-b);
    if (i==0 || d<min_d)
    {
       min_d=d;
       best=i;
    }

  }
  return best;
}
//-------------------------------------------------------------------
void __fastcall TTransForm::PaletteBtnClick(TObject *Sender)
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
     src_pal[i].R=r;
     src_pal[i].G=g;
     src_pal[i].B=b;

   }
   fclose(inf);
   Palette2Name=ExtractFileName(Palette1Name);
   PaletteLbl->Caption=Palette2Name;
}
//---------------------------------------------------------------------------

void __fastcall TTransForm::LoadScriptBtnClick(TObject *Sender)
{
   FILE *inf;
   char line[256],cstr[128];
   int pos_src,pos_dest,row=1;

   OpenDialog1->InitialDir=start_path;
   OpenDialog1->Filter=
           "Comma Separated (*.csv)|*.CSV|All files (*.*)|*.*";
   OpenDialog1->FileName="";
   if (!OpenDialog1->Execute()) return;
   inf=fopen(OpenDialog1->FileName.c_str(),"rt");
   if (!inf)
   {
     sprintf(cstr,"Could not open %s. Aborting.",
             OpenDialog1->FileName.c_str());
     Application->MessageBox(cstr,"File Error",MB_OK);
     return;
   }
   do
   {
     line[0]=0;
     fgets(line,127,inf);
     if (line[0])
     {
       pos_src=0;

       //description
       cstr[0]=0; pos_dest=0;
       while(line[pos_src]!=',' && pos_dest<127)
       {
         cstr[pos_dest]=line[pos_src];
         ++pos_dest; ++pos_src;
         cstr[pos_dest]=0;
       }
       AnsiString Astr1(cstr);
       TransGrid->Cells[0][row]=Astr1;
       ++pos_src;

       //dest file name
       cstr[0]=0; pos_dest=0;
       while(line[pos_src]!=',' && pos_dest<127)
       {
         cstr[pos_dest]=line[pos_src];
         ++pos_dest; ++pos_src;
         cstr[pos_dest]=0;
       }
       AnsiString Astr2(cstr);
       TransGrid->Cells[1][row]=Astr2;
       ++pos_src;

       //dest icon numebr
       cstr[0]=0; pos_dest=0;
       while(line[pos_src]!=',' && pos_dest<127)
       {
         cstr[pos_dest]=line[pos_src];
         ++pos_dest; ++pos_src;
         cstr[pos_dest]=0;
       }
       AnsiString Astr3(cstr);
       TransGrid->Cells[2][row]=Astr3;
       ++pos_src;

       //source file
       cstr[0]=0;  pos_dest=0;
       while(line[pos_src]!=',' && pos_dest<127)
       {
         cstr[pos_dest]=line[pos_src];
         ++pos_dest; ++pos_src;
         cstr[pos_dest]=0;
       }
       AnsiString Astr4(cstr);
       TransGrid->Cells[3][row]=Astr4;
       ++pos_src;

       //source icon
       cstr[0]=0; pos_dest=0;
       while(line[pos_src]>',' && pos_dest<127)
       {
         cstr[pos_dest]=line[pos_src];
         ++pos_dest; ++pos_src;
         cstr[pos_dest]=0;
       }
       AnsiString Astr5(cstr);
       TransGrid->Cells[4][row]=Astr5;
       ++pos_src;

       ++row;
     }
   } while (line[0] && row<TransGrid->RowCount);
   fclose(inf);
   //terminate data
   while(!TransGrid->Cells[1][row].IsEmpty()&&row<TransGrid->RowCount)
   {
    for (int i=0; i<TransGrid->ColCount; ++i)
     TransGrid->Cells[i][row]="";
    ++row;
   }
}
//---------------------------------------------------------------------------

void __fastcall TTransForm::SaveScriptBtnClick(TObject *Sender)
{
   int row=1;
   boolean done=false;
   FILE *outf;
   char cstr[256];

    SaveDialog1->Filter="Standard (*.csv)| *.CSV| All files (*.*)|*.*";
    SaveDialog1->Title="Save Script";
    SaveDialog1->DefaultExt="csv";
    if (!SaveDialog1->Execute())return ;
    outf=fopen(SaveDialog1->FileName.c_str(),"wt");
    if (!outf)
    {
      sprintf(cstr,"Could not open %s. Aborting.",
              SaveDialog1->FileName.c_str());
      Application->MessageBox(cstr,"File Error",MB_OK);
      return;
    }

    do
    {
      if ( TransGrid->Cells[1][row].IsEmpty()    //return if a grid spot is blank
           ||TransGrid->Cells[2][row].IsEmpty()
           ||TransGrid->Cells[3][row].IsEmpty()
           ||TransGrid->Cells[4][row].IsEmpty() ) done=true;
      if (!done)
      {
        sprintf(cstr,"%s,%s,%s,%s,%s\n",
           TransGrid->Cells[0][row].c_str(),
           TransGrid->Cells[1][row].c_str(),
           TransGrid->Cells[2][row].c_str(),
           TransGrid->Cells[3][row].c_str(),
           TransGrid->Cells[4][row].c_str() );
        fputs(cstr,outf);
      }
      ++row;
    }while (!done && row<TransGrid->RowCount);
    fclose(outf);

}
//---------------------------------------------------------------------------

