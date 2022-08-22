//---------------------------------------------------------------------------

#ifndef main_form_unitH
#define main_form_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <winsock2>
#include <string>
#include "stl_utils.h"
#include "obj_utils.h"
//---------------------------------------------------------------------------
class TPanelEx : public TPanel
{
public:
     __fastcall virtual TPanelEx(TComponent* AOwner): TPanel(AOwner), OnPaint(0) {}

    void __fastcall (__closure *OnPaint)(TObject* Sender);

    void __fastcall WMPaint(TWMPaint& Message)
    {
        if (OnPaint) OnPaint(this);
    }

    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint)
    END_MESSAGE_MAP(TPanel)
};
//---------------------------------------------------------------------------
class Tmain_form : public TForm
{
__published:	// IDE-managed Components
        TShape *Shape;
        TMainMenu *MainMenu1;
        TMenuItem *file_itm;
        TMenuItem *view_itm;
        TMenuItem *ext_view_itm;
        TMenuItem *open_itm;
        TOpenDialog *OpenDialog;
        TMenuItem *basis_itm;
        TMenuItem *options_itm;
        TColorDialog *ColorDialog;
        TMenuItem *help_itm;
        TMenuItem *about_itm;
        TMenuItem *show_help_itm;
        TMenuItem *go_to_default_pos_itm;
        TMenuItem *wire_itm;
        TMenuItem *N2;
        void __fastcall gl_panelMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall gl_panelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall gl_panelMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall gl_panelResize(TObject *Sender);
        void __fastcall gl_panelPaint(TObject *Sender);
        void __fastcall closeClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall x_view_itmClick(TObject *Sender);
        void __fastcall open_itmClick(TObject *Sender);
        void __fastcall c_itmClick(TObject *Sender);
        void __fastcall options_itmClick(TObject *Sender);
        void __fastcall about_itmClick(TObject *Sender);
        void __fastcall show_help_itmClick(TObject *Sender);
        void __fastcall go_to_default_pos_itmClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    std::string src;

    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;

    GLclampf bg_r, bg_g, bg_b; //фон

    GLfloat LightAmbient_r, LightAmbient_g, LightAmbient_b;
    GLfloat LightDiffuse_r, LightDiffuse_g, LightDiffuse_b;
    GLfloat LightPosition_x, LightPosition_y, LightPosition_z;

    int ww, hw; //размеры окна
    float w[4], h[4]; //размеры модели

    float l[4], b[4], r[4], t[4]; //границы модели

    int xw, yw; //координаты курсора в пр-ве окна
    float x[4], y[4]; //координаты курсора в пр-ве модели

    int xwp, ywp; //координаты курсора в пр-ве окна при активации ф-ии панорамирования
    float lp, bp; //левый нижний угол модели при активации ф-ии панорамирования

    float s[4]; //к-т масштабирования
    float ss; //ступень масштабирования
    float m;

    bool pan;
    DWORD pan_t;

    bool rotate;

    float ax;
    float ay;

    float axp;
    float ayp;

    vector ex;
    vector ey;

    vector exp;
    vector eyp;

    TPanelEx *gl_panel;

    int digits;

    HFONT font_h;
    GLuint font_list;
    int real_font_height;

    HFONT font_big_h;
    GLuint font_big_list;

    enum pm_t
    {
        xz_pm_t = 0,
        yz_pm_t,
        xy_pm_t,
        xyz_pm_t,
        norm_pm_t
    };

    facet_obj *f;

    std::string cfg_file_name;
    bool cfg_load(std::istream &is);
    bool cfg_save(std::ostream &os);
    bool cfg_load(void);
    bool cfg_save(void);

    void create_fonts(void);
    void destroy_fonts(void);

    void create_gl_fonts(void);
    void destroy_gl_fonts(void);

    void print(const GLuint lst, const float &x, const float &y, const AnsiString &s);

    void set_dc_pixel_format(void);
    void set_gl_params(void);

    void set_projection_matrix(const pm_t type);

    void render(void);

    void render_basis
    (
        const GLclampf ex_r = 0.7, const GLclampf ex_g = 0, const GLclampf ex_b = 0,
        const GLclampf ey_r = 0, const GLclampf ey_g = 0.7, const GLclampf ey_b = 0,
        const GLclampf ez_r = 0.3, const GLclampf ez_g = 0.3, const GLclampf ez_b = 1,
        const bool invert_ey = false,
        const float m = 1
    );
    void render_basis_info
    (
        const GLclampf ex_r = 0.7, const GLclampf ex_g = 0, const GLclampf ex_b = 0,
        const GLclampf ey_r = 0, const GLclampf ey_g = 0.7, const GLclampf ey_b = 0,
        const GLclampf ez_r = 0.3, const GLclampf ez_g = 0.3, const GLclampf ez_b = 1,
        const bool invert_ey = false,
        const float m = 1
    );

    void render_frame(void);

    void go_to_default_pos(void);
    
        __fastcall Tmain_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain_form *main_form;
//---------------------------------------------------------------------------
#endif
