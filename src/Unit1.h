//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <math.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
// Tabla meretek
const int BIGX = 30;
const int BIGY = 20;
const int SMALLX = 15;
const int SMALLY = 10;

const int MAXSIZE = 100;

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
		TMenuItem *mnuGame;
		TMenuItem *mnuNewBoard;
		TMenuItem *mnuUndo;
		TMenuItem *N1;
		TMenuItem *mnuNormal;
		TMenuItem *mnuAdvanced;
		TMenuItem *mnuExtra;
		TMenuItem *N2;
		TMenuItem *mnuAbout;
		TMenuItem *mnuExit;
		TStatusBar *StatusBar1;
		TImage *Image1;
		TImage *black;
		TImage *blue;
		TImage *cyan;
		TImage *green;
		TImage *purple;
		TImage *red;
		TImage *yellow;
		TTimer *Timer1;
		TMenuItem *mnuLang;
		TMenuItem *mnuMagyarul;
		TMenuItem *mnuEnglish;
		void __fastcall mnuExitClick(TObject *Sender);
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall mnuNormalClick(TObject *Sender);
        void __fastcall mnuAdvancedClick(TObject *Sender);
        void __fastcall mnuNewBoardClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall mnuUndoClick(TObject *Sender);
        void __fastcall mnuAboutClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mnuExtraClick(TObject *Sender);
		void __fastcall mnuMagyarulClick(TObject *Sender);
		void __fastcall mnuEnglishClick(TObject *Sender);
private:	// User declarations
        int **Tabla;
        int **Masolat;
        int meretx,merety,Lepes,Pontok,UtolsoPontok;
        bool vanMasolat;
        bool Jatek,Vege;
        int Szamlalo,Terulet;
		TImage **Kepek;
        UnicodeString txtAttention,txtPoints,txtWarnUndo,txtWarnNew,txtEnd,txtWin,txtNoMore;
        void __fastcall Lemasol(void);
        void __fastcall Visszavon(void);
        void __fastcall Feltolt(bool resize);
        void __fastcall Megmutat(void);
        int  __fastcall CellaSzin(int x,int y);
        int  __fastcall Szomszedok(int x,int y);
        void __fastcall Torles(int x,int y);
        void __fastcall Korrekcio(void);
		void __fastcall Ellenor(void);
		void __fastcall Pontszam(void);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
