//---------------------------------------------------------------------------
#include "facet_utils.h"
//---------------------------------------------------------------------------
#include <fstream>
#include <math.h>
#include <map>
//---------------------------------------------------------------------------
float get_sizeof_facets(std::list<facet> * const facets)
{
    float res = -1;

    if (facets->size())
    {
        vector min = facets->front().v[0];
        vector max = facets->front().v[0];

        for
        (
            std::list<facet>::iterator i = facets->begin();
            i != facets->end();
            i++
        )
        {
            for (int k = 0; k < i->v.size(); k++)
            {
                if (i->v[k].x < min.x) min.x = i->v[k].x;
                if (i->v[k].y < min.y) min.y = i->v[k].y;
                if (i->v[k].z < min.z) min.z = i->v[k].z;

                if (i->v[k].x > max.x) max.x = i->v[k].x;
                if (i->v[k].y > max.y) max.y = i->v[k].y;
                if (i->v[k].z > max.z) max.z = i->v[k].z;
            }
        }

        res = (max - min).module();
    }

    return res;
}

void create_facets_array(float ** const normals, float ** const vertexes, std::list<facet> * const facets)
{
    delete [] *normals;
    *normals = 0;

    delete [] *vertexes;
    *vertexes = 0;

    if (facets->size())
    {
        *normals = new float[facets->size() * facets->front().v.size() * 3 * sizeof(float)];
        float *p_n = *normals;

        *vertexes = new float[facets->size() * facets->front().v.size() * 3 * sizeof(float)];
        float *p_v = *vertexes;

        for
        (
            std::list<facet>::iterator i = facets->begin();
            i != facets->end();
            i++
        )
        {
            for (int k = 0; k < i->v.size(); k++)
            {
                *p_n++ = i->n[k].x;
                *p_n++ = i->n[k].y;
                *p_n++ = i->n[k].z;

                *p_v++ = i->v[k].x;
                *p_v++ = i->v[k].y;
                *p_v++ = i->v[k].z;
            }
        }
    }
}

void render_facets_array(float * const normals, float * const vertexes, const int size, int n)
{
    if (vertexes && normals)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glNormalPointer(GL_FLOAT, 0, normals);
        glVertexPointer(3, GL_FLOAT, 0, vertexes);
        glDrawArrays(n == 3? GL_TRIANGLES : n == 4? GL_QUADS : GL_LINES, 0, n * size);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}
//---------------------------------------------------------------------------
void get_edges
(
    std::list<facet> * const facets,
    std::list<edge> * const edges
)
{
    edges->clear();
}

float get_sizeof_edges(std::list<edge> * const edges)
{
    float res = -1;

    if (edges->size())
    {
        vector min = edges->front().a;
        vector max = edges->front().a;

        for
        (
            std::list<edge>::iterator i = edges->begin();
            i != edges->end();
            i++
        )
        {
            if (i->a.x < min.x) min.x = i->a.x;
            if (i->a.y < min.y) min.y = i->a.y;
            if (i->a.z < min.z) min.z = i->a.z;

            if (i->a.x > max.x) max.x = i->a.x;
            if (i->a.y > max.y) max.y = i->a.y;
            if (i->a.z > max.z) max.z = i->a.z;

            if (i->b.x < min.x) min.x = i->b.x;
            if (i->b.y < min.y) min.y = i->b.y;
            if (i->b.z < min.z) min.z = i->b.z;

            if (i->b.x > max.x) max.x = i->b.x;
            if (i->b.y > max.y) max.y = i->b.y;
            if (i->b.z > max.z) max.z = i->b.z;
        }

        res = (max - min).module();
    }

    return res;
}

void create_edges_array(float ** const vertexes, std::list<edge> * const edges)
{
    delete [] *vertexes;
    *vertexes = 0;

    if (edges->size())
    {
        *vertexes = new float[edges->size() * 2 * 3 * sizeof(float)];
        float *p_v = *vertexes;

        for
        (
            std::list<edge>::iterator i = edges->begin();
            i != edges->end();
            i++
        )
        {
            *p_v++ = i->a.x;
            *p_v++ = i->a.y;
            *p_v++ = i->a.z;

            *p_v++ = i->b.x;
            *p_v++ = i->b.y;
            *p_v++ = i->b.z;
        }
    }
}

void render_edges_array(float * const vertexes, const int size)
{
    if (vertexes)
    {
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertexes);
        glDrawArrays(GL_LINES, 0, 2 * size);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}
//---------------------------------------------------------------------------
void move_facets(const vector &d, std::list<facet> * const facets, float *vertexes)
{
    for
    (
        std::list<facet>::iterator i = facets->begin();
        i != facets->end();
        i++
    )
    {
        for (int k = 0; k < i->v.size(); k++)
            i->v[k] += d;

        *vertexes++ += d.x;
        *vertexes++ += d.y;
        *vertexes++ += d.z;

        *vertexes++ += d.x;
        *vertexes++ += d.y;
        *vertexes++ += d.z;

        *vertexes++ += d.x;
        *vertexes++ += d.y;
        *vertexes++ += d.z;
    }
}

void move_edges(const vector &d, std::list<edge> * const edges, float *vertexes)
{
    for
    (
        std::list<edge>::iterator i = edges->begin();
        i != edges->end();
        i++
    )
    {
        i->a += d;
        i->b += d;

        *vertexes++ += d.x;
        *vertexes++ += d.y;
        *vertexes++ += d.z;

        *vertexes++ += d.x;
        *vertexes++ += d.y;
        *vertexes++ += d.z;
    }
}

