//------------------------------------------------------------------------------
#include "vector.h"
//------------------------------------------------------------------------------
#include <math.h>
#include <stdlib.h>
//------------------------------------------------------------------------------
vector::vector(void)
    : x(0),
      y(0),
      z(0)
{}
//------------------------------------------------------------------------------
vector::vector(const float &x, const float &y, const float &z)
    : x(x),
      y(y),
      z(z)
{}
//------------------------------------------------------------------------------
vector::~vector()
{}
//------------------------------------------------------------------------------
const vector &vector::operator=(const vector &v)
{
    if (this != &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    return *this;
}
//------------------------------------------------------------------------------
float &vector::operator[](const unsigned index)
{
    return *(&x + index);
}
//------------------------------------------------------------------------------
const float &vector::operator[](const unsigned index) const
{
    return *(&x + index);
}
//------------------------------------------------------------------------------
bool vector::operator==(const vector &v) const
{
    return x == v.x && y == v.y && z == v.z;
}
//------------------------------------------------------------------------------
bool vector::operator!=(const vector &v) const
{
    return x != v.x || y != v.y || z != v.z;
}
//------------------------------------------------------------------------------
vector vector::operator-(void) const
{
    return vector(-x, -y, -z);
}
//------------------------------------------------------------------------------
vector vector::operator+(const vector &v) const
{
    return vector(x + v.x, y + v.y, z + v.z);
}
//------------------------------------------------------------------------------
vector vector::operator-(const vector &v) const
{
    return vector(x - v.x, y - v.y, z - v.z);
}
//------------------------------------------------------------------------------
vector vector::operator*(const float &c) const
{
    return vector(x * c, y * c, z * c);
}
//------------------------------------------------------------------------------
float vector::operator*(const vector &v) const
{
    return x * v.x + y * v.y + z * v.z;
}
//------------------------------------------------------------------------------
vector vector::operator^(const vector &v) const
{
    return vector
    (
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}
//------------------------------------------------------------------------------
vector vector::operator&(const vector &v) const
{
    return vector(x * v.x, y * v.y, z * v.z);
}
//------------------------------------------------------------------------------
vector vector::operator/(const float &c) const
{
    return vector(x / c, y / c, z / c);
}
//------------------------------------------------------------------------------
const vector &vector::operator+=(const vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}
//------------------------------------------------------------------------------
const vector &vector::operator-=(const vector &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}
//------------------------------------------------------------------------------
const vector &vector::operator*=(const float &c)
{
    x *= c;
    y *= c;
    z *= c;

    return *this;
}
//------------------------------------------------------------------------------
const vector &vector::operator^=(const vector &v)
{
    return *this = vector
    (
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}
//------------------------------------------------------------------------------
const vector &vector::operator&=(const vector &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;

    return *this;
}
//------------------------------------------------------------------------------
const vector &vector::operator/=(const float &c)
{
    x /= c;
    y /= c;
    z /= c;

    return *this;
}
//------------------------------------------------------------------------------
float vector::module() const
{
    return sqrt(fabs(x * x + y * y + z * z));
}
//------------------------------------------------------------------------------
const vector &vector::normalize(const float &c)
{
    return *this /= module() / c;
}
//------------------------------------------------------------------------------
vector operator*(const float &c, const vector &v)
{
    return v * c;
}
