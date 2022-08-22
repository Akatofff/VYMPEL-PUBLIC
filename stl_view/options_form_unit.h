//---------------------------------------------------------------------------

#ifndef options_form_unitH
#define options_form_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Toptions_form : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TPanel *bg_color;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *LightPosition_x;
        TLabel *Label4;
        TEdit *LightPosition_y;
        TLabel *Label5;
        TEdit *LightPosition_z;
        TButton *ok;
        TButton *cancel;
        TPanel *LightAmbient_color;
        TPanel *LightDiffuse_color;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *d_x;
        TEdit *d_y;
        TEdit *d_z;
        void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
        void __fastcall bg_colorClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall okClick(TObject *Sender);
        void __fastcall LightPosition_xChange(TObject *Sender);
        void __fastcall cancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Toptions_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Toptions_form *options_form;
//---------------------------------------------------------------------------
#endif
