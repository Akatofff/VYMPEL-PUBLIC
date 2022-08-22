//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "options_form_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Toptions_form *options_form;
//---------------------------------------------------------------------------
#include "main_form_unit.h"
#include "helpers.h"
#include "vector.h"
//---------------------------------------------------------------------------
__fastcall Toptions_form::Toptions_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Toptions_form::FormShortCut(TWMKey &Msg, bool &Handled)
{
    if (Msg.CharCode == VK_ESCAPE)
    {
        Close();
        Handled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall Toptions_form::bg_colorClick(TObject *Sender)
{
    main_form->ColorDialog->Color = ((TPanel *)Sender)->Color;
    if (!main_form->ColorDialog->Execute()) return;
    ((TPanel *)Sender)->Color = main_form->ColorDialog->Color;
}
//---------------------------------------------------------------------------
void __fastcall Toptions_form::FormShow(TObject *Sender)
{
    GET_TCOLOR(bg)        
    GET_TCOLOR(LightAmbient)
    GET_TCOLOR(LightDiffuse)
    GET_XYZ(LightPosition)
}
//---------------------------------------------------------------------------
void __fastcall Toptions_form::okClick(TObject *Sender)
{
    bool bad_value_exists = false;

    SET_TCOLOR(bg)
    SET_TCOLOR(LightAmbient)
    SET_TCOLOR(LightDiffuse)
    SET_XYZ(LightPosition)

    vector d;
    try
    {
        d.x = StrToFloat(d_x->Text);
        d.y = StrToFloat(d_y->Text);
        d.z = StrToFloat(d_z->Text);
    }
    catch (...)
    {}

    main_form->f->move(d);

    if (!main_form->cfg_save())
    {}

    main_form->gl_panel->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall Toptions_form::LightPosition_xChange(TObject *Sender)
{
    TEdit *p = (TEdit *)Sender;
    try
    {
        int x = StrToFloat(p->Text);
        p->Font->Color = clWindowText;
    }
    catch (...)
    {
        p->Font->Color = clRed;
    }
}
//---------------------------------------------------------------------------

void __fastcall Toptions_form::cancelClick(TObject *Sender)
{
    Close();        
}
//---------------------------------------------------------------------------

