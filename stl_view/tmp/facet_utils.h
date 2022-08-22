//---------------------------------------------------------------------------
#ifndef facet_utils_h
#define facet_utils_h
//---------------------------------------------------------------------------
#include <vector>
#include <windows.h>
#include <GL\gl.h>
#include <list>
//---------------------------------------------------------------------------
#include "vector.h"
//---------------------------------------------------------------------------
#define RAD_IN_DEG 0.017453292519943295769
//---------------------------------------------------------------------------
struct facet
{
    std::vector<vector> n;
    std::vector<vector> v;
};
//---------------------------------------------------------------------------
struct edge
{
    vector a;
    vector b;
    edge(void) {}
    edge(const vector &a, const vector &b): a(a), b(b) {}
};
//---------------------------------------------------------------------------
float get_sizeof_facets(std::list<facet> * const facets);
void create_facets_array(float ** const normals, float ** const vertexes, std::list<facet> * const facets);
void render_facets_array(float * const normals, float * const vertexes, const int size, int n);
//---------------------------------------------------------------------------
void get_edges
(
    std::list<facet> * const facets,
    std::list<edge> * const edges
);
float get_sizeof_edges(std::list<edge> * const edges);
void create_edges_array(float ** const vertexes, std::list<edge> * const edges);
void render_edges_array(float * const vertexes, const int size);
//---------------------------------------------------------------------------
void move_facets(const vector &d, std::list<facet> * const facets, float *vertexes);
void move_edges(const vector &d, std::list<edge> * const edges, float *vertexes);
//---------------------------------------------------------------------------
#endif //facet_utils_h
