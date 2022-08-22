//==============================================================================
#include "rw_utils.h"
//------------------------------------------------------------------------------
#include <stdio.h>
//==============================================================================
unsigned long countof_lines(std::istream &is)
{
    long p = is.tellg();

    unsigned long res = 0;

    while (true)
    {
        int c = is.peek();
        if (c == EOF) break;
        is.ignore();

        if (c == '\n') res++;
    }

    is.seekg(p);

    return res;
}
//------------------------------------------------------------------------------
unsigned long countof_cells(std::istream &is, const char separator)
{
    long p = is.tellg();

    unsigned long res = 0;

    while (true)
    {
        int c = is.peek();
        if (c == EOF) break;
        is.ignore();

        if (c == separator)
        {
            res++;
            continue;
        }

        if (c == '\n')
        {
            res++;
            break;
        }
    }

    is.seekg(p);

    return res;
}
//------------------------------------------------------------------------------
void move_to_next_line(std::istream &is)
{
    while (true)
    {
        int c = is.peek();
        if (c == EOF) break;
        is.ignore();

        if (c == '\n') break;
    }
}
//------------------------------------------------------------------------------
void ignore_blank_lines(std::istream &is)
{
    while (true)
    {
        int c = is.peek();
        if (c == EOF) break;
        if (c != '\n') break;
        is.ignore();
    }
}
//==============================================================================
bool ignore(std::istream &is, const std::string &s)
{
    unsigned i = 0;
    for (; i < s.length(); i++)
    {
        int c = is.peek();
        if (c == EOF) break;
        if (c != s[i]) break;
        is.ignore();
    }
    return i == s.length();
}
//------------------------------------------------------------------------------
void move_to_next_data(std::istream &is, const char separator)
{
    while (true)
    {
        int c = is.peek();
        if (c == EOF) break;
        is.ignore();

        if (c == separator) break;
    }
}
//==============================================================================
bool read_bin
(
    std::istream &is, std::string * const value,
    const char separator, const unsigned long max_length
)
{
    value->clear();

    unsigned long p = 0;

    while (true)
    {
        int c = is.peek();
        if (c == EOF) break;
        is.ignore();

        if (c == separator) break;

        p++;
        if (p > max_length)
        {
            move_to_next_data(is, separator);
            break;
        }

        *value += c;
    }

    return !is.fail();
}
//------------------------------------------------------------------------------
bool read_bin
(
    std::istream &is, bool * const value
)
{
    char c;
    is.read((char *)&c, sizeof(char));
    *value = c;
    return !is.fail();
}
//------------------------------------------------------------------------------
#define DEFINE_READ_FUNCTION(type)\
bool read_bin\
(\
    std::istream &is, type * const value\
)\
{\
    is.read((char *)value, sizeof(type));\
    return !is.fail();\
}
//------------------------------------------------------------------------------
DEFINE_READ_FUNCTION(char)
DEFINE_READ_FUNCTION(unsigned char)
DEFINE_READ_FUNCTION(short)
DEFINE_READ_FUNCTION(unsigned short)
DEFINE_READ_FUNCTION(int)
DEFINE_READ_FUNCTION(unsigned int)
DEFINE_READ_FUNCTION(long)
DEFINE_READ_FUNCTION(unsigned long)
DEFINE_READ_FUNCTION(float)
DEFINE_READ_FUNCTION(double)
//------------------------------------------------------------------------------
bool read_bin
(
    std::istream &is, SYSTEMTIME * const value
)
{
    is.read((char *)&value->wYear, sizeof(WORD));
    is.read((char *)&value->wMonth, sizeof(BYTE));
    is.read((char *)&value->wDay, sizeof(BYTE));
    is.read((char *)&value->wHour, sizeof(BYTE));
    is.read((char *)&value->wMinute, sizeof(BYTE));
    is.read((char *)&value->wSecond, sizeof(BYTE));
    is.read((char *)&value->wMilliseconds, sizeof(WORD));
    return !is.fail();
}
//==============================================================================
bool write_bin
(
    std::ostream &os, const char *value
)
{
    os << value << '\0';
    return !os.fail();
}
//------------------------------------------------------------------------------
bool write_bin
(
    std::ostream &os, const std::string &value
)
{
    os << value << '\0';
    return !os.fail();
}
//------------------------------------------------------------------------------
bool write_bin
(
    std::ostream &os, const bool &value
)
{
    char c = value;
    os.write((char *)&c, sizeof(char));
    return !os.fail();
}
//------------------------------------------------------------------------------
#define DEFINE_WRITE_FUNCTION(type)\
bool write_bin\
(\
    std::ostream &os, const type &value\
)\
{\
    os.write((char *)&value, sizeof(type));\
    return !os.fail();\
}
//------------------------------------------------------------------------------
DEFINE_WRITE_FUNCTION(char)
DEFINE_WRITE_FUNCTION(unsigned char)
DEFINE_WRITE_FUNCTION(short)
DEFINE_WRITE_FUNCTION(unsigned short)
DEFINE_WRITE_FUNCTION(int)
DEFINE_WRITE_FUNCTION(unsigned int)
DEFINE_WRITE_FUNCTION(long)
DEFINE_WRITE_FUNCTION(unsigned long)
DEFINE_WRITE_FUNCTION(float)
DEFINE_WRITE_FUNCTION(double)
//------------------------------------------------------------------------------
bool write_bin
(
    std::ostream &os, const SYSTEMTIME &value
)
{
    os.write((char *)&value.wYear, sizeof(WORD));
    os.write((char *)&value.wMonth, sizeof(BYTE));
    os.write((char *)&value.wDay, sizeof(BYTE));
    os.write((char *)&value.wHour, sizeof(BYTE));
    os.write((char *)&value.wMinute, sizeof(BYTE));
    os.write((char *)&value.wSecond, sizeof(BYTE));
    os.write((char *)&value.wMilliseconds, sizeof(WORD));
    return !os.fail();
}
//==============================================================================
bool read_with_name
(
    std::istream &is, const std::string &name, std::string * const value,
    const unsigned long max_length 
)
{
    ignore_blank_lines(is);
    if (!ignore(is, name + "=")) return false;
    return read_bin(is, value, '\n', max_length);
}
//------------------------------------------------------------------------------
bool read_with_name
(
    std::istream &is, const std::string &name, bool * const value
)
{
    std::string s;
    if (!read_with_name(is, name, &s)) return false;
    *value = s == "true";
    return *value? true : s == "false";
}
//------------------------------------------------------------------------------
#define DEFINE_READ_WITH_NAME_FUNCTION(type, format)\
bool read_with_name\
(\
    std::istream &is, const std::string &name, type * const value\
)\
{\
    ignore_blank_lines(is);\
    if (!ignore(is, name + "=")) return false;\
    std::string buffer;\
    if (!read_bin(is, &buffer, '\n')) return false;\
    buffer += '\n';\
    char c;\
    if (sscanf(buffer.c_str(), format "%c", value, &c) != 2 || c != '\n')\
        return false;\
    return true;\
}
//------------------------------------------------------------------------------
DEFINE_READ_WITH_NAME_FUNCTION(char, "%c")
DEFINE_READ_WITH_NAME_FUNCTION(unsigned char, "%c")
DEFINE_READ_WITH_NAME_FUNCTION(short, "%hd")
DEFINE_READ_WITH_NAME_FUNCTION(unsigned short, "%hu")
DEFINE_READ_WITH_NAME_FUNCTION(int, "%ld")
DEFINE_READ_WITH_NAME_FUNCTION(unsigned int, "%lu")
DEFINE_READ_WITH_NAME_FUNCTION(long, "%ld")
DEFINE_READ_WITH_NAME_FUNCTION(unsigned long, "%lu")
DEFINE_READ_WITH_NAME_FUNCTION(float, "%f")
DEFINE_READ_WITH_NAME_FUNCTION(double, "%lf")
//------------------------------------------------------------------------------
bool read_with_name
(
    std::istream &is, const std::string &name, SYSTEMTIME * const value
)
{
    ignore_blank_lines(is);
    if (!ignore(is, name + "=")) return false;
    std::string buffer;
    if (!read_bin(is, &buffer, '\n')) return false;
    buffer += '\n';
    char c;
    if
    (
        sscanf
        (
            buffer.c_str(),
            "%hu.%hu.%hu %hu:%hu:%hu.%hu" "%c",
            &value->wYear, &value->wMonth, &value->wDay,
            &value->wHour, &value->wMinute, &value->wSecond,
            &value->wMilliseconds,
            &c
        ) != 8 ||
        c != '\n'
    )
        return false;
    value->wDayOfWeek = 0;
    return true;
}
//==============================================================================
bool write_with_name
(
    std::ostream &os, const std::string &name, const char *value
)
{
    os << name << '=' << value << '\n';
    return !os.fail();
}
//------------------------------------------------------------------------------
#define DEFINE_WRITE_WITH_NAME_FUNCTION(type)\
bool write_with_name\
(\
    std::ostream &os, const std::string &name, const type &value\
)\
{\
    os << name << '=' << value << '\n';\
    return !os.fail();\
}
//------------------------------------------------------------------------------
DEFINE_WRITE_WITH_NAME_FUNCTION(std::string)
//------------------------------------------------------------------------------
bool write_with_name
(
    std::ostream &os, const std::string &name, const bool &value
)
{
    std::string s = value? "true" : "false";
    os << name << '=' << s << '\n';
    return !os.fail();
}
//------------------------------------------------------------------------------
DEFINE_WRITE_WITH_NAME_FUNCTION(char)
DEFINE_WRITE_WITH_NAME_FUNCTION(unsigned char)
DEFINE_WRITE_WITH_NAME_FUNCTION(short)
DEFINE_WRITE_WITH_NAME_FUNCTION(unsigned short)
DEFINE_WRITE_WITH_NAME_FUNCTION(int)
DEFINE_WRITE_WITH_NAME_FUNCTION(unsigned int)
DEFINE_WRITE_WITH_NAME_FUNCTION(long)
DEFINE_WRITE_WITH_NAME_FUNCTION(unsigned long)
DEFINE_WRITE_WITH_NAME_FUNCTION(float)
DEFINE_WRITE_WITH_NAME_FUNCTION(double)
//------------------------------------------------------------------------------
bool write_with_name
(
    std::ostream &os, const std::string &name, const SYSTEMTIME &value
)
{
    char buffer[25];
    if
    (
        sprintf
        (
            buffer,
            "%hu.%02hu.%02hu %02hu:%02hu:%02hu.%03hu",
            &value.wYear, &value.wMonth, &value.wDay,
            &value.wHour, &value.wMinute, &value.wSecond,
            &value.wMilliseconds
        ) == EOF
    )
        return false;
    os << name << '=' << buffer << '\n';
    return !os.fail();
}
