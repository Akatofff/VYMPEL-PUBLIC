//------------------------------------------------------------------------------
#ifndef matrix_h
#define matrix_h
//------------------------------------------------------------------------------
#include "vector.h"
//------------------------------------------------------------------------------
class matrix
{
public:
    float a[4][4];

    matrix(void);
    matrix(const float &c);
    virtual ~matrix();

    const matrix &operator=(const matrix &m);

    float *operator[](const unsigned index);
    const float *operator[](const unsigned index) const;

    bool operator==(const matrix &m) const;
    bool operator!=(const matrix &m) const;

    matrix operator-(void) const;

    matrix operator+(const matrix &m) const;
    matrix operator-(const matrix &m) const;
    matrix operator*(const float &c) const;
    matrix operator*(const matrix &m) const;
    vector operator*(const vector &v) const;
    matrix operator/(const float &c) const;

    const matrix &operator+=(const matrix &m);
    const matrix &operator-=(const matrix &m);
    const matrix &operator*=(const float &c);
    const matrix &operator*=(const matrix &m);
    const matrix &operator/=(const float &c);

    const matrix &transpose();

    static matrix transpose(const matrix &m);

    static matrix transport(const vector &t);
    static matrix scale(const vector &s);

    static matrix rotate_x(const float &angle);
    static matrix rotate_y(const float &angle);
    static matrix rotate_z(const float &angle);
    static matrix rotate(const vector &point, const vector &axis, const float &angle);

    static matrix mirror_x(void);
    static matrix mirror_y(void);
    static matrix mirror_z(void);
};
//------------------------------------------------------------------------------
matrix operator*(const float &c, const matrix &m);
//------------------------------------------------------------------------------
#endif //matrix_h
