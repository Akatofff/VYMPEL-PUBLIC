//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tmain_form *main_form;
//---------------------------------------------------------------------------
#include <fstream>
#include <GL\glu.h>
#include "matrix.h"
#include "options_form_unit.h"
#include "about_form_unit.h"
#include "help_form_unit.h"
#include "rw_macros.h"
#include "skeleton.h"
//---------------------------------------------------------------------------
//#define SKELETON_DEMO
//#define TEX_DEMO
//---------------------------------------------------------------------------
__fastcall Tmain_form::Tmain_form(TComponent* Owner)
        : TForm(Owner),
          bg_r(0),
          bg_g(0),
          bg_b(0.2),
          LightAmbient_r(0.2),
          LightAmbient_g(0.2),
          LightAmbient_b(0.2),
          LightDiffuse_r(1),
          LightDiffuse_g(1),
          LightDiffuse_b(1),
          LightPosition_x(0.5),
          LightPosition_y(1),
          LightPosition_z(0.75),
          ss(1.5),
          m(0.00001),
          pan(false),
          rotate(false),
          ax(0),
          ay(0),
          ex(1, 0, 0),
          ey(0, 1, 0),
          digits(4),
          f(0),
          cfg_file_name(ChangeFileExt(Application->ExeName, ".cfg").c_str())
{
    if (!cfg_load())
    {}

    for (int idx = 0; idx < 4; idx++)
        s[idx] = 100;

    gl_panel = new TPanelEx(this);
    gl_panel->Parent = this;

    gl_panel->Left = Shape->Left + 1;
    gl_panel->Top = Shape->Top + 1;
    gl_panel->Width = Shape->Width - 2;
    gl_panel->Height = Shape->Height - 2;

    ww = gl_panel->Width;
    hw = gl_panel->Height;

    if (ext_view_itm->Checked)
    {
        ww /= 2;
        hw /= 2;
    }

    for (int idx = 0; idx < 4; idx++)
    {
        w[idx] = ww / s[idx];
        h[idx] = hw / s[idx];
        l[idx] = -w[idx] / 2;
        b[idx] = -h[idx] / 2;
        r[idx] = w[idx] / 2;
        t[idx] = h[idx] / 2;
    }

    gl_panel->OnMouseMove = gl_panelMouseMove;
    gl_panel->OnMouseDown = gl_panelMouseDown;
    gl_panel->OnMouseUp = gl_panelMouseUp;
    gl_panel->OnResize = gl_panelResize;
    gl_panel->OnPaint = gl_panelPaint;

    gl_panel->Anchors = Shape->Anchors;

    gl_panel->BorderStyle = bsNone;

    DoubleBuffered = true;
    gl_panel->DoubleBuffered = true;
    gl_panel->FullRepaint = false;

    hwnd = gl_panel->Handle;
    hdc = GetDC(hwnd);
    set_dc_pixel_format();
    hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);
    set_gl_params();

    create_fonts();
    create_gl_fonts();

    f = new facet_obj;

    render();
}
//---------------------------------------------------------------------------
bool Tmain_form::cfg_load(std::istream &is)
{
    READ_NAME_RGB(bg)
    READ_NAME_RGB(LightAmbient)
    READ_NAME_RGB(LightDiffuse)
    READ_NAME_XYZ(LightPosition)

    //загрузка закончена

    ASSIGN_NAME_RGB_TO_THIS(bg)
    ASSIGN_NAME_RGB_TO_THIS(LightAmbient)
    ASSIGN_NAME_RGB_TO_THIS(LightDiffuse)
    ASSIGN_NAME_XYZ_TO_THIS(LightPosition)

    return true;
}
//---------------------------------------------------------------------------
bool Tmain_form::cfg_save(std::ostream &os)
{
    WRITE_NAME_RGB(bg)
    WRITE_NAME_RGB(LightAmbient)
    WRITE_NAME_RGB(LightDiffuse)
    WRITE_NAME_XYZ(LightPosition)

    return true;
}
//---------------------------------------------------------------------------
bool Tmain_form::cfg_load(void)
{
    std::ifstream is(cfg_file_name.c_str());
    if (!cfg_load(is))
    {
        is.close();
        return false;
    }
    is.close();
    return !is.fail();
}
//---------------------------------------------------------------------------
bool Tmain_form::cfg_save(void)
{
    std::ofstream os(cfg_file_name.c_str());
    cfg_save(os);
    os.close();
    return !os.fail();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::gl_panelMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    xw = X;
    yw = Y;

    int idx;
    if (!ext_view_itm->Checked)
    {
        idx = 3;
    }
    else
    {
        if (xw > ww)
            if (yw > hw) idx = 3;
            else idx = 1;
        else
            if (yw > hw) idx = 2;
            else idx = 0;
    }

    int xww = xw;
    int yww = yw;
    if (xww > ww) xww -= ww;
    if (yww > hw) yww -= hw;

    x[idx] = l[idx] + xww / s[idx];
    y[idx] = t[idx] - yww / s[idx];

    if (pan)
    {
        l[idx] = lp + (xwp - xw) / s[idx];
        b[idx] = bp - (ywp - yw) / s[idx];
        r[idx] = l[idx] + w[idx];
        t[idx] = b[idx] + h[idx];
    }
    else if (rotate)
    {
        ax = float(yw - ywp) / hw * 90;
        ay = float(xw - xwp) / ww * 90;

        ex = matrix::rotate(vector(0, 0, 0), ey, ay * RAD_IN_DEG) * exp;
        ex = ey ^ ex ^ ey;
        ex.normalize();

        ey = matrix::rotate(vector(0, 0, 0), ex, ax * RAD_IN_DEG) * eyp;
        ey = ex ^ ey ^ ex;
        ey.normalize();
    }

    render();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::gl_panelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int idx;
    if (!ext_view_itm->Checked)
    {
        idx = 3;
    }
    else
    {
        if (xw > ww)
            if (yw > hw) idx = 3;
            else idx = 1;
        else
            if (yw > hw) idx = 2;
            else idx = 0;
    }

    if (Button == mbMiddle || (Button == mbRight && Shift.Contains(ssShift)))
    {
        if (GetTickCount() - pan_t <= GetDoubleClickTime())
        {
            go_to_default_pos();
        }
        else
        {
            lp = l[idx];
            bp = b[idx];
            xwp = xw;
            ywp = yw;

            SetCapture(hwnd);

            pan = true;
            pan_t = GetTickCount();
        }
    }
    else if (Button == mbLeft)
    {
        lp = l[idx];
        bp = b[idx];
        xwp = xw;
        ywp = yw;

        exp = ex;
        eyp = ey;

        SetCapture(hwnd);

        rotate = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::gl_panelMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    if (Button == mbMiddle && pan)
    {
        ReleaseCapture();

        pan = false;
    }
    else if (Button == mbLeft && rotate)
    {
        ReleaseCapture();

        rotate = false;
    }

    render();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
    Handled = true;

    int idx;
    if (!ext_view_itm->Checked)
    {
        idx = 3;
    }
    else
    {
        if (xw > ww)
            if (yw > hw) idx = 3;
            else idx = 1;
        else
            if (yw > hw) idx = 2;
            else idx = 0;
    }

    int xww = xw;
    int yww = yw;
    if (xww > ww) xww -= ww;
    if (yww > hw) yww -= hw;

    s[idx] /= ss;

    //восстанавливаем положение т-ки зумирования

    l[idx] = x[idx] - xww / s[idx];
    t[idx] = y[idx] + yww / s[idx];

    w[idx] = ww / s[idx];
    h[idx] = hw / s[idx];

    r[idx] = l[idx] + w[idx];
    b[idx] = t[idx] - h[idx];

    render();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
    Handled = true;

    int idx;
    if (!ext_view_itm->Checked)
    {
        idx = 3;
    }
    else
    {
        if (xw > ww)
            if (yw > hw) idx = 3;
            else idx = 1;
        else
            if (yw > hw) idx = 2;
            else idx = 0;
    }

    int xww = xw;
    int yww = yw;
    if (xww > ww) xww -= ww;
    if (yww > hw) yww -= hw;

    s[idx] *= ss;

    //восстанавливаем положение т-ки зумирования

    l[idx] = x[idx] - xww / s[idx];
    t[idx] = y[idx] + yww / s[idx];

    w[idx] = ww / s[idx];
    h[idx] = hw / s[idx];

    r[idx] = l[idx] + w[idx];
    b[idx] = t[idx] - h[idx];

    render();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::gl_panelResize(TObject *Sender)
{
    ww = gl_panel->Width;
    hw = gl_panel->Height;

    if (ext_view_itm->Checked)
    {
        ww /= 2;
        hw /= 2;
    }

    for (int idx = 0; idx < 4; idx++)
    {
        w[idx] = ww / s[idx];
        h[idx] = hw / s[idx];

        //левый верхний угол неподвижен

        /*r = l + w;
        b = t - h;*/

        //центр неподвижен

        float cx = (l[idx] + r[idx]) / 2;
        float cy = (b[idx] + t[idx]) / 2;

        l[idx] = cx - w[idx] / 2;
        r[idx] = cx + w[idx] /2;
        b[idx] = cy - h[idx] / 2;
        t[idx] = cy + h[idx] / 2;
    }

    render();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::gl_panelPaint(TObject *Sender)
{
    PAINTSTRUCT ps;
    memset(&ps, 0, sizeof(ps));
    ps.hdc = hdc;
    ps.fErase = FALSE;
    ps.rcPaint = TRect(0, 0, ww, hw);

    BeginPaint(hwnd, &ps);

    glClearColor(bg_r, bg_g, bg_b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

////////////////////////////////////////////////////////////////////////////////
    for (int idx = ext_view_itm->Checked? 0 : 3; idx < 4; idx++)
    {
        set_projection_matrix(idx);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if (idx == xyz_pm_t)
        {
            glRotatef(-54.74, 1, 0, 0);
            glRotatef(-135, 0, 0, 1);
        }

        if (!wire_itm->Checked)
        {
            GLfloat LightAmbient[4] = {LightAmbient_r, LightAmbient_g, LightAmbient_b, 1};
            GLfloat LightDiffuse[4] = {LightDiffuse_r, LightDiffuse_g, LightDiffuse_b, 1};
            GLfloat LightPosition[4] = {LightPosition_x, LightPosition_y, LightPosition_z, 0};
            glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
            glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
            glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glPushMatrix();
        glScalef(m, m, m);

        if (!wire_itm->Checked)
        {
            glEnable(GL_LIGHTING);
        }

        glColor3f(1, 1, 1);

        #ifndef SKELETON_DEMO

        f->render();

        #else
////////////////////////////////////////////////////////////////////////////////
        //демонстрация библиотеки графических примитивов
////////////////////////////////////////////////////////////////////////////////
        bool render_lines = false;
        bool render_facets = true;

        glPushMatrix();
        
        glTranslatef(350000, -350000, 0);
        skeleton s1;
        s1.render_lines = render_lines;
        s1.render_facets = render_facets;
        create_ellipsoid(&s1, 100000, 20, 20, 90, 180, 90, 360);
        s1.render();

        glTranslatef(-350000, 0, 0);
        skeleton c1;
        c1.render_lines = render_lines;
        c1.render_facets = render_facets;
        create_elliptical_cylinder(&c1, 100000, 100000, 20, 20, 0, 100000, 90, 360);
        c1.render();

        glTranslatef(-350000, 0, 0);
        skeleton t1;
        t1.render_lines = render_lines;
        t1.render_facets = render_facets;
        create_elliptical_torus(&t1, 100000, 25000, 25000, 20, 20, 90, 360, 180, 315);
        t1.render();
        
        glTranslatef(-350000, 0, 0);
        skeleton b1;
        b1.render_lines = render_lines;
        b1.render_facets = render_facets;
        create_box(&b1, 100000, 50000, 25000);
        b1.render();
        
        glPopMatrix();

        glPushMatrix();
        
        glTranslatef(350000, 0, 0);
        skeleton s2;
        s2.render_lines = render_lines;
        s2.render_facets = render_facets;
        create_ellipsoid(&s2, 100000, 20, 20, 0, 180, 0, 360, 1, 0.5);
        s2.render();

        glTranslatef(-350000, 0, 0);
        skeleton c2;
        c2.render_lines = render_lines;
        c2.render_facets = render_facets;
        create_elliptical_cylinder(&c2, 100000, 100000, 20, 20, 0, 100000, 0, 360, 0.5, 1);
        c2.render();

        glTranslatef(-350000, 0, 0);
        skeleton t2;
        t2.render_lines = render_lines;
        t2.render_facets = render_facets;
        create_elliptical_torus(&t2, 100000, 12500, 25000, 20, 20, 0, 360, 0, 360, 0.5, 2);
        t2.render();

        glPopMatrix();
////////////////////////////////////////////////////////////////////////////////
        #endif
        
        if (!wire_itm->Checked)
        {
            glDisable(GL_LIGHTING);
        }

        glPopMatrix();

        glPushAttrib(GL_TEXTURE_BIT);
        glDisable(GL_TEXTURE_2D);

        if (basis_itm->Checked)
        {
            render_basis();
            render_basis_info();
        }

        glPopAttrib();
    }

    if (ext_view_itm->Checked)
    {
        set_projection_matrix(norm_pm_t);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        render_frame();
    }
////////////////////////////////////////////////////////////////////////////////

    SwapBuffers(hdc);

    EndPaint(hwnd, &ps);
}
//---------------------------------------------------------------------------
void Tmain_form::create_fonts(void)
{
    LOGFONT logfont;

    logfont.lfHeight = -8;
    logfont.lfWidth = 0;
    logfont.lfEscapement = 0;
    logfont.lfOrientation = 0;
    logfont.lfWeight = FW_NORMAL;
    logfont.lfItalic = FALSE;
    logfont.lfUnderline = FALSE;
    logfont.lfStrikeOut = FALSE;
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    logfont.lfQuality = DEFAULT_QUALITY;
    logfont.lfPitchAndFamily = DEFAULT_PITCH;
    strcpy(logfont.lfFaceName, "Fixedsys");

    font_h = CreateFontIndirect(&logfont);

    real_font_height = -8;

    logfont.lfHeight = -18;
    strcpy(logfont.lfFaceName, "Arial");

    font_big_h = CreateFontIndirect(&logfont);
}
//---------------------------------------------------------------------------
void Tmain_form::destroy_fonts(void)
{
    DeleteObject(font_h);
    DeleteObject(font_big_h);
}
//---------------------------------------------------------------------------
void Tmain_form::create_gl_fonts(void)
{
    SelectObject(hdc, font_h);
    font_list = glGenLists(256);
    wglUseFontBitmaps(hdc, 0, 256, font_list);

    SelectObject(hdc, font_big_h);
    font_big_list = glGenLists(256);
    wglUseFontBitmaps(hdc, 0, 256, font_big_list);
}
//---------------------------------------------------------------------------
void Tmain_form::destroy_gl_fonts(void)
{
    glDeleteLists(font_list, 1);
    glDeleteLists(font_big_list, 1);
}
//---------------------------------------------------------------------------
void Tmain_form::print(const GLuint lst, const float &x, const float &y, const AnsiString &s)
{
    glRasterPos2f(x, y);
    glListBase(lst);
    glCallLists(s.Length(), GL_UNSIGNED_BYTE, s.c_str());
}
//---------------------------------------------------------------------------
void Tmain_form::set_dc_pixel_format(void)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER |
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0, 0,
        0, 0, 0, 0, 0,
        32,
        0,
        0,
        0,
        0,
        0, 0, 0
    };
    int pixel_format = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixel_format, &pfd);
}
//---------------------------------------------------------------------------
void Tmain_form::set_gl_params(void)
{
    glEnable(GL_DEPTH_TEST);

    glClearDepth(1000);

    glPointSize(10);
    glLineWidth(1);

    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_NORMALIZE);

    /*glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);*/
    
    #ifdef TEX_DEMO
    //демонстрация наложения текстуры

    GLuint tex;
    glGenTextures(1, &tex);

    HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(0), "BMP01", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)
    {
        BITMAP BMP;
        GetObject(hBMP, sizeof(BMP), &BMP);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
        DeleteObject(hBMP);
    }

    glEnable(GL_TEXTURE_2D);
    #endif
}
//---------------------------------------------------------------------------
void Tmain_form::set_projection_matrix(const pm_t type)
{
    if (!ext_view_itm->Checked)
    {
        glViewport(0, 0, gl_panel->Width, gl_panel->Height);
    }
    else
    {
        int row = type / 2;
        int column = type % 2;

        if (type == norm_pm_t)
        {
            glViewport(0, 0, gl_panel->Width, gl_panel->Height);
        }
        else
        {
            glViewport(column * ww, hw - row * hw, ww, hw);
        }
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (type == norm_pm_t)
    {
        glOrtho(0, gl_panel->Width, 0, gl_panel->Height, -1000, 1000);
    }
    else
    {
        glOrtho(l[type], r[type], b[type], t[type], -1000, 1000);
    }
    if (type == xz_pm_t)
    {
        gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, 1);
    }
    else if (type == xy_pm_t)
    {
        gluLookAt(0, 0, 1, 0, 0, 0, 0, -1, 0);
    }
    else if (type == yz_pm_t)
    {
        gluLookAt(1, 0, 0, 0, 0, 0, 0, 0, 1);
    }
    else if (type == xyz_pm_t)
    {
        vector eye = ex ^ ey;
        gluLookAt(eye.x, eye.y, eye.z, 0, 0, 0, ey.x, ey.y, ey.z);
    }
}
//---------------------------------------------------------------------------
void Tmain_form::render(void)
{
    gl_panel->Repaint();
}
//---------------------------------------------------------------------------
void Tmain_form::render_basis
(
    const GLclampf ex_r, const GLclampf ex_g, const GLclampf ex_b,
    const GLclampf ey_r, const GLclampf ey_g, const GLclampf ey_b,
    const GLclampf ez_r, const GLclampf ez_g, const GLclampf ez_b,
    const bool invert_ey,
    const float m
)
{
////
    glColor3f(ex_r, ex_g, ex_b);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0, 0, 0);
        glVertex3f(m, 0, 0);
    glEnd();

    glColor3f(ey_r, ey_g, ey_b);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0, 0, 0);
        glVertex3f(0, invert_ey? -m : m, 0);
    glEnd();

    glColor3f(ez_r, ez_g, ez_b);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, m);
    glEnd();
/*
////
    glEnable(GL_LIGHTING);
//
    glPushMatrix();

    glTranslatef(m, 0, 0);
    glRotatef(90, 0, 1, 0);

    glColor3f(ex_r, ex_g, ex_b);

    GLUquadricObj *q_obj = gluNewQuadric();
    gluQuadricDrawStyle(q_obj, GLU_FILL);
    gluCylinder(q_obj, 0.1, 0, 0.3, 10, 10);
    gluDeleteQuadric(q_obj);

    glRotatef(180, 1, 0, 0);

    q_obj = gluNewQuadric();
    gluQuadricDrawStyle(q_obj, GLU_FILL);
    gluDisk(q_obj, 0, 0.1, 10, 10);
    gluDeleteQuadric(q_obj);

    glPopMatrix();
//
    glPushMatrix();

    glTranslatef(0, invert_ey? -m : m, 0);
    glRotatef(invert_ey? 90 : -90, 1, 0, 0);

    glColor3f(ey_r, ey_g, ey_b);

    q_obj = gluNewQuadric();
    gluQuadricDrawStyle(q_obj, GLU_FILL);
    gluCylinder(q_obj, 0.1, 0, 0.3, 10, 10);
    gluDeleteQuadric(q_obj);

    glRotatef(180, 1, 0, 0);

    q_obj = gluNewQuadric();
    gluQuadricDrawStyle(q_obj, GLU_FILL);
    gluDisk(q_obj, 0, 0.1, 10, 10);
    gluDeleteQuadric(q_obj);

    glPopMatrix();
//
    glPushMatrix();

    glTranslatef(0, 0, m);

    glColor3f(ez_r, ez_g, ez_b);

    q_obj = gluNewQuadric();
    gluQuadricDrawStyle(q_obj, GLU_FILL);
    gluCylinder(q_obj, 0.1, 0, 0.3, 10, 10);
    gluDeleteQuadric(q_obj);

    glRotatef(180, 1, 0, 0);

    q_obj = gluNewQuadric();
    gluQuadricDrawStyle(q_obj, GLU_FILL);
    gluDisk(q_obj, 0, 0.1, 10, 10);
    gluDeleteQuadric(q_obj);

    glPopMatrix();
//
    glDisable(GL_LIGHTING);
////
*/
}
//---------------------------------------------------------------------------
void Tmain_form::render_basis_info
(
    const GLclampf ex_r, const GLclampf ex_g, const GLclampf ex_b,
    const GLclampf ey_r, const GLclampf ey_g, const GLclampf ey_b,
    const GLclampf ez_r, const GLclampf ez_g, const GLclampf ez_b,
    const bool invert_ey,
    const float m
)
{
    glPushMatrix();

    glDisable(GL_DEPTH_TEST);

    glColor3f(ex_r, ex_g, ex_b);
    print(font_big_list, 1.2 * m, 0, "X");

    glColor3f(ey_r, ey_g, ey_b);
    print(font_big_list, 0, 1.2 * (invert_ey? -m : m), "Y");

    glTranslatef(0, 0, 1.2 * m);
    glColor3f(ez_r, ez_g, ez_b);
    print(font_big_list, 0, 0, "Z");

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
}
//---------------------------------------------------------------------------
void Tmain_form::render_frame(void)
{
    glDisable(GL_DEPTH_TEST);

    float cx = gl_panel->Width / 2;
    float cy = gl_panel->Height / 2;

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
        glVertex3f(0, cy, 0);
        glVertex3f(gl_panel->Width, cy, 0);
        glVertex3f(cx, 0, 0);
        glVertex3f(cx, gl_panel->Height, 0);
    glEnd();

    float _x = gl_panel->Width / 4 - -real_font_height;
    float _y = gl_panel->Height - 2 * -real_font_height;

    print(font_list, _x, _y, "XZ"); _x += gl_panel->Width / 2;
    print(font_list, _x, _y, "YZ"); _x -= gl_panel->Width / 2; _y -= gl_panel->Height / 2; 
    print(font_list, _x, _y, "XY"); _x += gl_panel->Width / 2;
    print(font_list, _x, _y, "XYZ");

    glEnable(GL_DEPTH_TEST);
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::closeClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if (!cfg_save())
    {}

    destroy_gl_fonts();
    destroy_fonts();

    wglMakeCurrent(0, 0);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::x_view_itmClick(TObject *Sender)
{
    TMenuItem *itm = (TMenuItem *)Sender;
    itm->Checked = !itm->Checked;
    gl_panelResize(this);
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::open_itmClick(TObject *Sender)
{
    if (!OpenDialog->Execute()) return;

    TCursor c = Screen->Cursor;
    Screen->Cursor = crHourGlass;

    if (ExtractFileExt(OpenDialog->FileName) == ".obj") read_triangles_from_obj(OpenDialog->FileName.c_str(), &f->facets);
    else if (ExtractFileExt(OpenDialog->FileName) == ".stl")
    {
        if (OpenDialog->FilterIndex == 1) read_facets_stl_txt(OpenDialog->FileName.c_str(), &f->facets);
        else read_facets_stl_bin(OpenDialog->FileName.c_str(), &f->facets);
    }

    f->compile();

    m = 1.75 / f->get_size();

    if (m < 0) m = 0.00001;
    go_to_default_pos();

    Screen->Cursor = c;
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::c_itmClick(TObject *Sender)
{
    TMenuItem *itm = (TMenuItem *)Sender;
    itm->Checked = !itm->Checked;
    render();       
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::options_itmClick(TObject *Sender)
{
    options_form->Show();
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::about_itmClick(TObject *Sender)
{
    about_form->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::show_help_itmClick(TObject *Sender)
{
    help_form->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::go_to_default_pos_itmClick(TObject *Sender)
{
    go_to_default_pos();
}
//---------------------------------------------------------------------------
void Tmain_form::go_to_default_pos(void)
{
    for (int idx = 0; idx < 4; idx++)
    {
        s[idx] = 100;

        w[idx] = ww / s[idx];
        h[idx] = hw / s[idx];
        l[idx] = -w[idx] / 2;
        b[idx] = -h[idx] / 2;
        r[idx] = w[idx] / 2;
        t[idx] = h[idx] / 2;
    }

    ax = 0;
    ay = 0;

    ex.x = 1;
    ex.y = 0;
    ex.z = 0;

    ey.x = 0;
    ey.y = 1;
    ey.z = 0;

    render();
}


