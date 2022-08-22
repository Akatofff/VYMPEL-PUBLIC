//---------------------------------------------------------------------------

#ifndef about_form_unitH
#define about_form_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tabout_form : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TButton *ok;
        TLabel *Label3;
        TLabel *Label4;
        void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
        void __fastcall okClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tabout_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tabout_form *about_form;
//---------------------------------------------------------------------------
#endif
