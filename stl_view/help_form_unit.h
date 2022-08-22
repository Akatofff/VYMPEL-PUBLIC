//---------------------------------------------------------------------------

#ifndef help_form_unitH
#define help_form_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Thelp_form : public TForm
{
__published:	// IDE-managed Components
        TButton *ok;
        TMemo *Memo;
        void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
        void __fastcall okClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Thelp_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Thelp_form *help_form;
//---------------------------------------------------------------------------
#endif
