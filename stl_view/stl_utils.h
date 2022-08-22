//---------------------------------------------------------------------------
#ifndef stl_utils_h
#define stl_utils_h
//---------------------------------------------------------------------------
#include "facet_utils.h"
//---------------------------------------------------------------------------
void read_facets_stl_txt(const char *file_name, std::list<facet> * const facets);
void read_facets_stl_bin(const char *file_name, std::list<facet> * const facets);
//---------------------------------------------------------------------------
#endif //stl_utils_h
