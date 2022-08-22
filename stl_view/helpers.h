//------------------------------------------------------------------------------
#ifndef helpers_h
#define helpers_h
//------------------------------------------------------------------------------
#include <Graphics.hpp>
//------------------------------------------------------------------------------
void TColor_to_gl_color(const TColor c, float * const r, float * const g, float * const b);
TColor gl_color_to_TColor(const float &r, const float &g, const float &b);
//------------------------------------------------------------------------------
void TColor_to_rgb(const TColor c, int * const r, int * const g, int * const b);
TColor rgb_to_TColor(const int r, const int g, const int b);
//------------------------------------------------------------------------------
#define GET_TCOLOR(name)\
name##_color->Color = gl_color_to_TColor(main_form->name##_r, main_form->name##_g, main_form->name##_b);

#define SET_TCOLOR(name)\
TColor_to_gl_color(name##_color->Color, &main_form->name##_r, &main_form->name##_g, &main_form->name##_b);

#define GET_XYZ(name)\
name##_x->Text = FloatToStrF(main_form->name##_x, ffFixed, 15, main_form->digits);\
name##_y->Text = FloatToStrF(main_form->name##_y, ffFixed, 15, main_form->digits);\
name##_z->Text = FloatToStrF(main_form->name##_z, ffFixed, 15, main_form->digits);

#define SET_XYZ(name)\
if\
(\
    name##_x->Font->Color == clRed ||\
    name##_y->Font->Color == clRed ||\
    name##_z->Font->Color == clRed\
)\
{\
    bad_value_exists = true;\
}\
else\
{\
    main_form->name##_x = StrToFloat(name##_x->Text);\
    main_form->name##_y = StrToFloat(name##_y->Text);\
    main_form->name##_z = StrToFloat(name##_z->Text);\
}
//------------------------------------------------------------------------------
#endif //helpers_h
