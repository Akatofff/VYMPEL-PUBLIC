//------------------------------------------------------------------------------
#include "helpers.h"
//------------------------------------------------------------------------------
void TColor_to_gl_color(const TColor c, float * const r, float * const g, float * const b)
{
    *r = float(c & 0xFF) / 255;
    *g = float((c & 0xFF00) >> 8) / 255;
    *b = float((c & 0xFF0000) >> 16) / 255;
}
//------------------------------------------------------------------------------
TColor gl_color_to_TColor(const float &r, const float &g, const float &b)
{
    return int(r * 255) | int(g * 255) << 8 | int(b * 255) << 16;
}
//------------------------------------------------------------------------------
void TColor_to_rgb(const TColor c, int * const r, int * const g, int * const b)
{
    *r = c & 0xFF;
    *g = (c & 0xFF00) >> 8;
    *b = (c & 0xFF0000) >> 16;
}
//------------------------------------------------------------------------------
TColor rgb_to_TColor(const int r, const int g, const int b)
{
    return r | g << 8 | b << 16;
}

