//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main_form_unit.cpp", main_form);
USEFORM("options_form_unit.cpp", options_form);
USEFORM("about_form_unit.cpp", about_form);
USEFORM("help_form_unit.cpp", help_form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(Tmain_form), &main_form);
                 Application->CreateForm(__classid(Toptions_form), &options_form);
                 Application->CreateForm(__classid(Tabout_form), &about_form);
                 Application->CreateForm(__classid(Thelp_form), &help_form);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
