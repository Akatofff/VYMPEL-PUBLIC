//---------------------------------------------------------------------------
#ifndef edges_utils_h
#define edges_utils_h
//---------------------------------------------------------------------------
#include "facet_utils.h"
//---------------------------------------------------------------------------
void read_edges_bin(const char *file_name, std::list<edge> * const edges);
void write_edges_bin(const char *file_name, std::list<edge> * const edges);
//---------------------------------------------------------------------------
#endif //g_utils_h
