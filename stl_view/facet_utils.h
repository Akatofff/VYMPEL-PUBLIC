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
    std::vector<vector> v;
    std::vector<vector> n;
};
struct facet_obj
{
    std::list<facet> facets;

    bool compiled;

    float *vertexes;
    float *normals;

    GLuint list;

    int max_v_size;
    int min_v_size;

    facet_obj(void);
    virtual ~facet_obj(void);

    float get_size(void);

    void compile(void);
    void render(void);
    
    void move(const vector &d);
};
//---------------------------------------------------------------------------
#endif //facet_utils_h
