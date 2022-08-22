//------------------------------------------------------------------------------
#include "matrix.h"
//------------------------------------------------------------------------------
#include <math.h>
#include <mem.h>
//------------------------------------------------------------------------------
matrix::matrix(void)
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            a[i][j] = 0;
}
//------------------------------------------------------------------------------
matrix::matrix(const float &c)
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = i + 1; j < 4; j++)
            a[i][j] = 0;

    for (unsigned i = 1; i < 4; i++)
        for (unsigned j = 0; j < i; j++)
            a[i][j] = 0;

    for (unsigned i = 0; i < 3; i++)
            a[i][i] = c;

    a[3][3] = 1;
}
//------------------------------------------------------------------------------
matrix::~matrix()
{}
//------------------------------------------------------------------------------
const matrix &matrix::operator=(const matrix &m)
{
    if (this != &m)
        memcpy(this->a, m.a, sizeof(a));

    return *this;
}
//------------------------------------------------------------------------------
float *matrix::operator[](const unsigned index)
{
    return *(a + index);
}
//------------------------------------------------------------------------------
const float *matrix::operator[](const unsigned index) const
{
    return *(a + index);
}
//------------------------------------------------------------------------------
bool matrix::operator==(const matrix &m) const
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            if (a[i][j] != m.a[i][j]) return false;

    return true;
}
//------------------------------------------------------------------------------
bool matrix::operator!=(const matrix &m) const
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            if (a[i][j] != m.a[i][j]) return false;

    return true;
}
//------------------------------------------------------------------------------
matrix matrix::operator*(const float &c) const
{
    matrix res;

    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            res.a[i][j] = a[i][j] * c;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::operator*(const matrix &m) const
{
    matrix res;

    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
        {
            float s = 0;

            for (unsigned k = 0; k < 4; k++)
                s += a[i][k] * m.a[k][j];

            res.a[i][j] = s;
        }

    return res;
}
//------------------------------------------------------------------------------
vector matrix::operator*(const vector &v) const
{
    vector res;

    res.x = a[0][0] * v.x + a[0][1] * v.y + a[0][2] * v.z + a[0][3];
    res.y = a[1][0] * v.x + a[1][1] * v.y + a[1][2] * v.z + a[1][3];
    res.z = a[2][0] * v.x + a[2][1] * v.y + a[2][2] * v.z + a[2][3];

    res /= a[3][0] * v.x + a[3][1] * v.y + a[3][2] * v.z + a[3][3];

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::operator/(const float &c) const
{
    matrix res;

    for (unsigned i = 0; i < 4; i++)
       for (unsigned j = 0; j < 4; j++)
           res.a[i][j] = a[i][j] / c;

    return res;
}
//------------------------------------------------------------------------------
const matrix &matrix::operator+=(const matrix &m)
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            a[i][j] += m.a[i][j];

    return *this;
}
//------------------------------------------------------------------------------
const matrix &matrix::operator-=(const matrix &m)
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            a[i][j] -= m.a[i][j];

    return *this;
}
//------------------------------------------------------------------------------
const matrix &matrix::operator*=(const float &c)
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            a[i][j] *= c;

    return *this;
}
//------------------------------------------------------------------------------
const matrix &matrix::operator*=(const matrix &m)
{
    matrix tmp = *this;

    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
        {
            float s = 0;

            for (unsigned k = 0; k < 4; k++)
                s += tmp.a[i][k] * m.a[k][j];

            a[i][j] = s;
        }

    return *this;
}
//------------------------------------------------------------------------------
const matrix &matrix::operator/=(const float &c)
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            a[i][j] /= c;

    return *this;
}
//------------------------------------------------------------------------------
const matrix &matrix::transpose()
{
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            a[i][j] = a[j][i];

    return *this;
}
//------------------------------------------------------------------------------
matrix matrix::transpose(const matrix &m)
{
    return matrix(m).transpose();
}
//------------------------------------------------------------------------------
matrix matrix::transport(const vector &t)
{
    matrix res(1);

    res.a[0][3] = t.x;
    res.a[1][3] = t.y;
    res.a[2][3] = t.z;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::scale(const vector &s)
{
    matrix res(1);

    res.a[0][0] = s.x;
    res.a[1][1] = s.y;
    res.a[2][2] = s.z;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::rotate_x(const float &angle)
{
    matrix res(1);

    float sine   = sin(angle);
    float cosine = cos(angle);

    res.a[1][1] = cosine;
    res.a[1][2] = -sine;
    res.a[2][1] = sine;
    res.a[2][2] = cosine;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::rotate_y(const float &angle)
{
    matrix res(1);

    float sine   = sin(angle);
    float cosine = cos(angle);

    res.a[0][0] = cosine;
    res.a[0][2] = sine;
    res.a[2][0] = -sine;
    res.a[2][2] = cosine;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::rotate_z(const float &angle)
{
    matrix res(1);

    float sine   = sin(angle);
    float cosine = cos(angle);

    res.a[0][0] = cosine;
    res.a[0][1] = -sine;
    res.a[1][0] = sine;
    res.a[1][1] = cosine;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::rotate(const vector &point, const vector &axis, const float &angle)
{
    matrix res(1);

    float sine   = sin(angle);
    float cosine = cos(angle);

    float axis_x_2 = axis.x * axis.x;
    float axis_y_2 = axis.y * axis.y;
    float axis_z_2 = axis.z * axis.z;

    float one_minus_cosine = 1 - cosine;

    res.a[0][0] = axis_x_2 + cosine * (1 - axis_x_2);
    res.a[0][1] = axis.x * one_minus_cosine * axis.y + axis.z * sine;
    res.a[0][2] = axis.x * one_minus_cosine * axis.z - axis.y * sine;

    res.a[1][0] = axis.x * one_minus_cosine * axis.y - axis.z * sine;
    res.a[1][1] = axis_y_2 + cosine * (1 - axis_y_2);
    res.a[1][2] = axis.y * one_minus_cosine * axis.z + axis.x * sine;

    res.a[2][0] = axis.x * one_minus_cosine * axis.z + axis.y * sine;
    res.a[2][1] = axis.y * one_minus_cosine * axis.z - axis.x * sine;
    res.a[2][2] = axis_z_2 + cosine * (1 - axis_z_2);

    return transport(-point) * res * transport(point);
}
//------------------------------------------------------------------------------
matrix matrix::mirror_x(void)
{
    matrix res(1);

    res.a[0][0] = -1;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::mirror_y(void)
{
    matrix res(1);

    res.a[1][1] = -1;

    return res;
}
//------------------------------------------------------------------------------
matrix matrix::mirror_z(void)
{
    matrix res(1);

    res.a[2][2] = -1;

    return res;
}
//------------------------------------------------------------------------------
matrix operator*(const float &c, const matrix &m)
{
    return m * c;
}