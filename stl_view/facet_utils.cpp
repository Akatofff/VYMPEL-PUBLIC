//---------------------------------------------------------------------------
#include "facet_utils.h"
//---------------------------------------------------------------------------
#include <fstream>
#include <math.h>
#include <map>
//---------------------------------------------------------------------------
facet_obj::facet_obj(void):
    compiled(true),
    vertexes(0),
    normals(0)
{
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glEndList();
}
//---------------------------------------------------------------------------
facet_obj::~facet_obj(void)
{
    delete [] vertexes;
    delete [] normals;
    
    glDeleteLists(list, 1);
}
//---------------------------------------------------------------------------
float facet_obj::get_size(void)
{
    float res = -1;

    if (facets.size())
    {
        vector min = facets.front().v[0];
        vector max = min;

        for
        (
            std::list<facet>::iterator i = facets.begin();
            i != facets.end();
            i++
        )
        {
            for (int j = 0; j < i->v.size(); j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (i->v[j][k] < min[k]) min[k] = i->v[j][k];
                    if (i->v[j][k] > max[k]) max[k] = i->v[j][k];
                }
            }
        }

        res = (max - min).module();
    }

    return res;
}
//---------------------------------------------------------------------------
void facet_obj::compile(void)
{
    delete [] vertexes;
    vertexes = 0;

    delete [] normals;
    normals = 0;

    glNewList(list, GL_COMPILE);
    glEndList();

    min_v_size = max_v_size = 0;

    if (facets.size())
    {
        min_v_size = max_v_size = facets.front().v.size();

        for
        (
            std::list<facet>::iterator i = facets.begin();
            i != facets.end();
            i++
        )
        {
            if (i->v.size() < min_v_size) min_v_size = i->v.size();
            if (i->v.size() > max_v_size) max_v_size = i->v.size();
        }

        if (min_v_size == max_v_size && (min_v_size == 3 || min_v_size == 4))
        {
            vertexes = new float[facets.size() * min_v_size * 3 * sizeof(float)];
            float *p_v = vertexes;

            normals = new float[facets.size() * min_v_size * 3 * sizeof(float)];
            float *p_n = normals;

            for
            (
                std::list<facet>::iterator i = facets.begin();
                i != facets.end();
                i++
            )
            {
                for (int j = 0; j < i->v.size(); j++)
                {
                    *p_n++ = i->n[j].x;
                    *p_n++ = i->n[j].y;
                    *p_n++ = i->n[j].z;

                    *p_v++ = i->v[j].x;
                    *p_v++ = i->v[j].y;
                    *p_v++ = i->v[j].z;
                }
            }
        }
        else
        {
            glNewList(list, GL_COMPILE);
            compiled = false;
            render();
            compiled = true;
            glEndList();
        }
    }
}
//---------------------------------------------------------------------------
void facet_obj::render(void)
{
    if (vertexes)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glNormalPointer(GL_FLOAT, 0, normals);
        glVertexPointer(3, GL_FLOAT, 0, vertexes);
        glDrawArrays(min_v_size == 3? GL_TRIANGLES : GL_QUADS, 0, facets.size() * min_v_size);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    else if (compiled)
    {
        glCallList(list);
    }
    else
    {
        for
        (
            std::list<facet>::iterator i = facets.begin();
            i != facets.end();
            i++
        )
        {
            glBegin(GL_POLYGON);
            for (int j = 0; j < i->v.size(); j++)
            {
                glNormal3f(i->n[j].x, i->n[j].y, i->n[j].z);
                glVertex3f(i->v[j].x, i->v[j].y, i->v[j].z);
            }
            glEnd();
        }
    }
}
//---------------------------------------------------------------------------
void facet_obj::move(const vector &d)
{
    for
    (
        std::list<facet>::iterator i = facets.begin();
        i != facets.end();
        i++
    )
    {
        for (int j = 0; j < i->v.size(); j++)
        {
            i->v[j] += d;
        }
    }

    if (vertexes)
    {
        for
        (
            std::list<facet>::iterator i = facets.begin();
            i != facets.end();
            i++
        )
        {
            for (int j = 0; j < i->v.size(); j++)
            {
                *vertexes++ += d.x;
                *vertexes++ += d.y;
                *vertexes++ += d.z;
            }
        }
    }
    else
    {
        compile();
    }
}

