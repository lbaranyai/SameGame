//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuExitClick(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 int i,j;
 // Nem indul automatikusan a szamlalo
 Jatek = false;
 Vege = false;
 Szamlalo = 0;
 // meret beallitas
 meretx = SMALLX;
 merety = SMALLY;
 ClientWidth = meretx*20;
 ClientHeight = merety*20 + StatusBar1->Height;
 Image1->Picture->Bitmap = new Graphics::TBitmap();
 // memoria foglalas
 Tabla = new int*[MAXSIZE];
 Masolat = new int*[MAXSIZE];
 for (i=0;i<MAXSIZE;i++) {
  Tabla[i] = new int[MAXSIZE];
  Masolat[i] = new int[MAXSIZE];
  for (j=0;j<MAXSIZE;j++) {
   Tabla[i][j] = 0;
   Masolat[i][j] = 0;
  }
 }
 // Kepek beallitasa
 Kepek = new TImage*[7];
 Kepek[0] = black;
 Kepek[1] = blue;
 Kepek[2] = green;
 Kepek[3] = red;
 Kepek[4] = cyan;
 Kepek[5] = purple;
 Kepek[6] = yellow;
 // kezdo ertekek
 Lepes  = Pontok = 0;
 vanMasolat = false;
 randomize();
 Feltolt(false);
 mnuMagyarulClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Lemasol(void)
{
 int i,j;

 for (i=0;i<merety;i++) {
  for (j=0;j<meretx;j++) Masolat[i][j] = Tabla[i][j];
 }
 UtolsoPontok = Pontok;
 mnuUndo->Enabled = true;
 vanMasolat = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Pontszam(void)
{
 UnicodeString AS;
 AS.printf(txtPoints.c_str(),Lepes,Pontok);
 StatusBar1->Panels->Items[2]->Text = AS;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Visszavon(void)
{
 int i,j;

 if (Lepes<1 || Vege) return;
 if (!vanMasolat) {
  i = Application->MessageBox(txtWarnUndo.c_str(),txtAttention.c_str(),MB_OK);
  return;
 }
 for (i=0;i<merety;i++) {
  for (j=0;j<meretx;j++) Tabla[i][j] = Masolat[i][j];
 }
 Pontok = UtolsoPontok;
 Pontszam();
 Megmutat();
 vanMasolat = false;
 mnuUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Feltolt(bool resize)
{
 int i,j,k,n;
 AnsiString AS;

 if (Lepes>0) {
  i = Application->MessageBox(txtWarnNew.c_str(),txtAttention.c_str(),MB_YESNO);
  if (i == IDNO) return;
 }
 Jatek = false; Vege = false;
 StatusBar1->Panels->Items[0]->Text = "00:00";
 AS.printf("%d x %d",meretx,merety);
 StatusBar1->Panels->Items[1]->Text = AS;
 Lepes = Pontok = 0;
 Pontszam();
 Szamlalo = 0;
 Image1->Picture->Bitmap->Width = meretx*20;
 Image1->Picture->Bitmap->Height = merety*20;
 if (resize) {
  ClientWidth = meretx*20;
  ClientHeight = merety*20 + StatusBar1->Height;
  // To center
  Top = Screen->DesktopTop + (Screen->DesktopHeight - Height)/2;
  Left = Screen->DesktopLeft + (Screen->DesktopWidth - Width)/2;
 }
 for (i=0;i<merety;i++) {
  j = 0;
  do {
   k = 1 + random(6);
   n = 1 + random(5);
   while (n>0 && j<meretx) {
    Tabla[i][j] = k;
    Masolat[i][j] = k;
    Image1->Picture->Bitmap->Canvas->Draw(j*20,i*20,(Kepek[k])->Picture->Bitmap);
    j++; n--;
   }
  } while(j<meretx);
 }
 vanMasolat = true;
 Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Megmutat(void)
{
 int i,j,k;
 for (i=0;i<merety;i++) {
  for (j=0;j<meretx;j++) {
   k = Tabla[i][j];
   Image1->Picture->Bitmap->Canvas->Draw(j*20,i*20,(Kepek[k])->Picture->Bitmap);
  }
 }
 Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnuNormalClick(TObject *Sender)
{
 mnuNormal->Checked = true;
 mnuAdvanced->Checked = false;
 mnuExtra->Checked = false;
 meretx = SMALLX;
 merety = SMALLY;
 Feltolt(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuAdvancedClick(TObject *Sender)
{
 mnuNormal->Checked = false;
 mnuAdvanced->Checked = true;
 mnuExtra->Checked = false;
 meretx = BIGX;
 merety = BIGY;
 Feltolt(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuNewBoardClick(TObject *Sender)
{
 Feltolt(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
 AnsiString AS;
 int ts,tm;

 if (!Jatek || Vege) return;
 Szamlalo++;
 ts = Szamlalo%60;
 tm = (Szamlalo-ts)/60;
 AS.printf("%02d:%02d",tm,ts);
 StatusBar1->Panels->Items[0]->Text = AS;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y)
{
 int xx,yy;
 double d;

 if (Vege) return;
 if (!Jatek) Jatek = true;
 d = ClientWidth; d /= meretx; xx = floor(X/d);
 d = ClientHeight - StatusBar1->Height; d /= merety; yy = floor(Y/d);
 Terulet = 0;
 if (Szomszedok(xx,yy)==0) {
  Pontszam();
  Beep(); return;
 }
 Lemasol();
 Torles(xx,yy);
 Korrekcio();
 Lepes++;
 Pontok += Terulet*Terulet;
 Pontszam();
 Ellenor();
}
//---------------------------------------------------------------------------
int  __fastcall TForm1::CellaSzin(int x,int y)
{
 if (x<0 || y<0 || x>=meretx || y>=merety) return -1;
 return Tabla[y][x];
}
//---------------------------------------------------------------------------
int  __fastcall TForm1::Szomszedok(int x,int y)
{
 int n,t;

 n = 0;
 t = CellaSzin(x, y);
 if (t<1) return 0;
 if (CellaSzin(x-1, y) == t) n++;
 if (CellaSzin(x+1, y) == t) n++;
 if (CellaSzin(x, y-1) == t) n++;
 if (CellaSzin(x, y+1) == t) n++;
 return n;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Torles(int x,int y)
{
 int t;

 if (x<0 || x>=meretx || y<0 || y>=merety) return;
 t = CellaSzin(x,y);
 if (t<1) return;
 Tabla[y][x] = 99;
 Terulet++;
 if (CellaSzin(x-1,y) == t) Torles(x-1,y);
 if (CellaSzin(x+1,y) == t) Torles(x+1,y);
 if (CellaSzin(x,y-1) == t) Torles(x,y-1);
 if (CellaSzin(x,y+1) == t) Torles(x,y+1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Korrekcio(void)
{
 int x,y,k,n,chg;

 /* lehullas */
 for (y=merety-1;y>0;y--) {
  for (x=0;x<meretx;x++) {
   chg = 0;
   while (Tabla[y][x]==99) {
    chg = 1;
    for (k=y;k>0;k--) { Tabla[k][x]=Tabla[k-1][x]; }
    Tabla[0][x]=0;
   }
  }
 }
 /* elso sor kiegeszites */
 for (x=0;x<meretx;x++) {
  if (Tabla[0][x]==99) Tabla[0][x]=0;
 }
 /* ures sorok torlese */
 x=0;
 while (x<meretx-1) {
  chg = 0;
  for (y=0;y<merety;y++) if (Tabla[y][x]==0) chg++;
  if (chg == merety) {
   n = 0;
   for (y=0;y<merety;y++) {
    for (k=x;k<meretx-1;k++) {
     Tabla[y][k] = Tabla[y][k+1];
     if (Tabla[y][k]>0) n++;
    }
    Tabla[y][meretx-1] = 0;
   }
   if (n==0) x=meretx; /* nem volt ures oszlop */
  } else {
   x++;
  }
 }
 Megmutat();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Ellenor(void)
{
 int nt,np,x,y;
 UnicodeString AS;

 nt=0; np=0;
 for (x=0;x<meretx;x++) {
  for (y=0;y<merety;y++) {
   if (Tabla[y][x]>0) {
    nt++;
    if (Szomszedok(x,y)>0) np++;
   }
  }
 }
 if (nt == 0) {
  Vege = true;
  Pontok *= 2;
  Pontszam();
  AS.printf(txtWin.c_str(),Lepes,Pontok);
  x = Application->MessageBox(AS.c_str(),txtEnd.c_str(),MB_OK);
  Lepes = Pontok = 0;
  mnuUndo->Enabled = false;
 } else {
  if (np == 0) {
   Vege = true;
   x = Application->MessageBox(txtNoMore.c_str(),txtEnd.c_str(),MB_OK);
   Lepes = Pontok = 0;
   mnuUndo->Enabled = false;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuUndoClick(TObject *Sender)
{
 Visszavon();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::mnuAboutClick(TObject *Sender)
{
 AnsiString AS;
 AS = "http://www.baranyailaszlo.hu/";
 ShellExecute(NULL,"open",AS.c_str(),"","",SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 int i;
 for (i=0;i<MAXSIZE;i++) {
  delete[] Tabla[i];
  delete[] Masolat[i];
 }
 delete[] Tabla;
 delete[] Masolat;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuExtraClick(TObject *Sender)
{
 mnuNormal->Checked = false;
 mnuAdvanced->Checked = false;
 mnuExtra->Checked = true;
 // almost fullscreen
 meretx = (Screen->DesktopWidth - 30)/20; if (meretx>MAXSIZE) meretx = MAXSIZE;
 merety = (Screen->DesktopHeight - 90)/20; if (merety>MAXSIZE) merety = MAXSIZE;
 Feltolt(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuMagyarulClick(TObject *Sender)
{
 mnuMagyarul->Checked = true;
 mnuEnglish->Checked = false;
 mnuGame->Caption = "Játék";
 mnuNewBoard->Caption = "Új tábla";
 mnuUndo->Caption = "Visszavonás";
 mnuNormal->Caption = "Normál";
 mnuAdvanced->Caption = "Haladó";
 mnuAbout->Caption = "A játékról...";
 mnuExit->Caption = "Kilépés";
 txtAttention = "Figyelem!";
 txtPoints = "%d lépés, %d pont";
 txtWarnUndo = "Sajnos csak az utolsó lépés vonható vissza.";
 txtWarnNew = "Biztosan új táblát szeretne?";
 txtEnd = "Vége";
 txtNoMore = "Nincs több lépés!";
 txtWin = "Gratulálunk!\n\nÖn nyert! %d lépésben %d pontot gyûjtött.";
 Pontszam();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnuEnglishClick(TObject *Sender)
{
 mnuEnglish->Checked = true;
 mnuMagyarul->Checked = false;
 mnuGame->Caption = "Game";
 mnuNewBoard->Caption = "New board";
 mnuUndo->Caption = "Undo";
 mnuNormal->Caption = "Normal";
 mnuAdvanced->Caption = "Advanced";
 mnuAbout->Caption = "About...";
 mnuExit->Caption = "Quit";
 txtAttention = "Attention!";
 txtPoints = "%d steps, %d points";
 txtWarnUndo = "Unfortunately you can withdraw only the last step.";
 txtWarnNew = "Are you sure to get new board?";
 txtEnd = "Finished";
 txtNoMore = "No more steps!";
 txtWin = "Congratulations!\n\nYou won! In %d steps %d points were collected.";
 Pontszam();
}
//---------------------------------------------------------------------------

