//------------------------------------------------------------------------------
#ifndef rw_utils_h
#define rw_utils_h
//------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <windows.h>
//------------------------------------------------------------------------------
//разделитель строк '\n'
//------------------------------------------------------------------------------
unsigned long countof_lines(std::istream &is);
unsigned long countof_cells(std::istream &is, const char separator = ';');
void move_to_next_line(std::istream &is);
void ignore_blank_lines(std::istream &is);
//------------------------------------------------------------------------------
bool ignore(std::istream &is, const std::string &s);
void move_to_next_data(std::istream &is, const char separator);
//------------------------------------------------------------------------------
bool read_bin
(
    std::istream &is, std::string * const value,
    const char separator = '\0', const unsigned long max_length = 255
);
bool read_bin
(
    std::istream &is, bool * const value
);
bool read_bin
(
    std::istream &is, char * const value
);
bool read_bin
(
    std::istream &is, unsigned char * const value
);
bool read_bin
(
    std::istream &is, short * const value
);
bool read_bin
(
    std::istream &is, unsigned short * const value
);
bool read_bin
(
    std::istream &is, int * const value
);
bool read_bin
(
    std::istream &is, unsigned int * const value
);
bool read_bin
(
    std::istream &is, long * const value
);
bool read_bin
(
    std::istream &is, unsigned long * const value
);
bool read_bin
(
    std::istream &is, float * const value
);
bool read_bin
(
    std::istream &is, double * const value
);
bool read_bin
(
    std::istream &is, SYSTEMTIME * const value
);
//------------------------------------------------------------------------------
bool write_bin
(
    std::ostream &os, const char *value
);
bool write_bin
(
    std::ostream &os, const std::string &value
);
bool write_bin
(
    std::ostream &os, const bool &value
);
bool write_bin
(
    std::ostream &os, const char &value
);
bool write_bin
(
    std::ostream &os, const unsigned char &value
);
bool write_bin
(
    std::ostream &os, const short &value
);
bool write_bin
(
    std::ostream &os, const unsigned short &value
);
bool write_bin
(
    std::ostream &os, const int &value
);
bool write_bin
(
    std::ostream &os, const unsigned int &value
);
bool write_bin
(
    std::ostream &os, const long &value
);
bool write_bin
(
    std::ostream &os, const unsigned long &value
);
bool write_bin
(
    std::ostream &os, const float &value
);
bool write_bin
(
    std::ostream &os, const double &value
);
bool write_bin
(
    std::ostream &os, const SYSTEMTIME &value
);
//------------------------------------------------------------------------------
//записи вида name=value\n
//------------------------------------------------------------------------------
bool read_with_name
(
    std::istream &is, const std::string &name, std::string * const value,
    const unsigned long max_length = 255
);
bool read_with_name
(
    std::istream &is, const std::string &name, bool * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, char * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, unsigned char * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, short * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, unsigned short * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, int * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, unsigned int * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, long * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, unsigned long * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, float * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, double * const value
);
bool read_with_name
(
    std::istream &is, const std::string &name, SYSTEMTIME * const value
);
//------------------------------------------------------------------------------
//записи вида name=value\n
//------------------------------------------------------------------------------
bool write_with_name
(
    std::ostream &os, const std::string &name, const char *value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const std::string &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const bool &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const char &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const unsigned char &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const short &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const unsigned short &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const int &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const unsigned int &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const long &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const unsigned long &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const float &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const double &value
);
bool write_with_name
(
    std::ostream &os, const std::string &name, const SYSTEMTIME &value
);
//------------------------------------------------------------------------------
#endif //rw_utils_h
