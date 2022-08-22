//------------------------------------------------------------------------------
#ifndef vector_h
#define vector_h
//------------------------------------------------------------------------------
class vector
{
public:
    float x;
    float y;
    float z;

    vector(void);
    vector(const float &x, const float &y, const float &z);
    virtual ~vector();

    const vector &operator=(const vector &v);

    float &operator[](const unsigned index);
    const float &operator[](const unsigned index) const;

    bool operator==(const vector &v) const;
    bool operator!=(const vector &v) const;

    vector operator-(void) const;

    vector operator+(const vector &v) const;
    vector operator-(const vector &v) const;
    vector operator*(const float &c) const;
    float operator*(const vector &v) const; //скалярное умножение
    vector operator^(const vector &v) const; //векторное умножение
    vector operator&(const vector &v) const; //поэлементное умножение
    vector operator/(const float &c) const;

    const vector &operator+=(const vector &v);
    const vector &operator-=(const vector &v);
    const vector &operator*=(const float &c);
    const vector &operator^=(const vector &v); //векторное умножение
    const vector &operator&=(const vector &v); //поэлементное умножение
    const vector &operator/=(const float &c);

    float module() const;
    const vector &normalize(const float &c = 1);
};
//------------------------------------------------------------------------------
vector operator*(const float &c, const vector &v);
//------------------------------------------------------------------------------
#endif //vector_h
