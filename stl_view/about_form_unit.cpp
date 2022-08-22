//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "about_form_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tabout_form *about_form;
//---------------------------------------------------------------------------
__fastcall Tabout_form::Tabout_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tabout_form::FormShortCut(TWMKey &Msg, bool &Handled)
{
    if (Msg.CharCode == VK_ESCAPE)
    {
        Close();
        Handled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall Tabout_form::okClick(TObject *Sender)
{
    Close();        
}
//---------------------------------------------------------------------------

