//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "help_form_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Thelp_form *help_form;
//---------------------------------------------------------------------------
__fastcall Thelp_form::Thelp_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Thelp_form::FormShortCut(TWMKey &Msg, bool &Handled)
{
    if (Msg.CharCode == VK_ESCAPE)
    {
        Close();
        Handled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall Thelp_form::okClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

