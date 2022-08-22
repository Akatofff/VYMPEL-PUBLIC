//------------------------------------------------------------------------------
#ifndef RW_MACROS_H
#define RW_MACROS_H
//------------------------------------------------------------------------------
#include "rw_utils.h"
//------------------------------------------------------------------------------
//#define RW_BIN //для двоичных rw-операций
//------------------------------------------------------------------------------
//необходим поток is типа std::istream
#define READ_BIN(name)\
if (!read_bin(is, &name)) return false;

//необходим поток os типа std::ostream
#define WRITE_BIN(name)\
if (!write_bin(os, name)) return false;
//------------------------------------------------------------------------------
//необходим поток is типа std::istream
#define READ_WITH_NAME(name)\
if (!read_with_name(is, #name, &name)) return false;

//необходим поток os типа std::ostream
#define WRITE_WITH_NAME(name)\
if (!write_with_name(os, #name, name)) return false;
//------------------------------------------------------------------------------
#ifdef RW_BIN
    #define READ READ_BIN
    #define WRITE WRITE_BIN
#else
    #define READ READ_WITH_NAME
    #define WRITE WRITE_WITH_NAME
#endif
//------------------------------------------------------------------------------
//необходим поток is типа std::istream
#define READ_BIN_RES(name)\
read_bin(is, &name)

//необходим поток os типа std::ostream
#define WRITE_BIN_RES(name)\
write_bin(os, name)
//------------------------------------------------------------------------------
//необходим поток is типа std::istream
#define READ_WITH_NAME_RES(name)\
read_with_name(is, #name, &name)

//необходим поток os типа std::ostream
#define WRITE_WITH_NAME_RES(name)\
write_with_name(os, #name, name)
//------------------------------------------------------------------------------
#ifdef RW_BIN
    #define READ_RES READ_BIN_RES
    #define WRITE_RES WRITE_BIN_RES
#else
    #define READ_RES READ_WITH_NAME_RES
    #define WRITE_RES WRITE_WITH_NAME_RES
#endif
//------------------------------------------------------------------------------
#define WRITE_NAME_RGB(name)\
WRITE(name##_r)\
WRITE(name##_g)\
WRITE(name##_b)

#define WRITE_NAME_XYZ(name)\
WRITE(name##_x)\
WRITE(name##_y)\
WRITE(name##_z)

#define READ_NAME_RGB(name)\
float name##_r;\
READ(name##_r)\
float name##_g;\
READ(name##_g)\
float name##_b;\
READ(name##_b)

#define READ_NAME_XYZ(name)\
float name##_x;\
READ(name##_x)\
float name##_y;\
READ(name##_y)\
float name##_z;\
READ(name##_z)

#define ASSIGN(name)\
::name = name;

#define ASSIGN_NAME_RGB(name)\
::name##_r = name##_r;\
::name##_g = name##_g;\
::name##_b = name##_b;

#define ASSIGN_NAME_XYZ(name)\
::name##_x = name##_x;\
::name##_y = name##_y;\
::name##_z = name##_z;

#define ASSIGN_TO_THIS(name)\
this->name = name;

#define ASSIGN_NAME_RGB_TO_THIS(name)\
this->name##_r = name##_r;\
this->name##_g = name##_g;\
this->name##_b = name##_b;

#define ASSIGN_NAME_XYZ_TO_THIS(name)\
this->name##_x = name##_x;\
this->name##_y = name##_y;\
this->name##_z = name##_z;

#define READ_STR(name)\
std::string name;\
READ(name)

#define READ_BOOL(name)\
bool name;\
READ(name)

#define READ_INT(name)\
int name;\
READ(name)

#define READ_UINT(name)\
unsigned name;\
READ(name)

#define READ_FLOAT(name)\
float name;\
READ(name)
//------------------------------------------------------------------------------
#endif //RW_MACROS_H
