//---------------------------------------------------------------------------
#include "skeleton.h"
//---------------------------------------------------------------------------
#include <math.h>
#include <fstream>
//---------------------------------------------------------------------------
float skeleton_eps = 1e-3;
//---------------------------------------------------------------------------
skeleton::skeleton(void):
    vertex(0),
    normal(0),
    tex(0),
    idx(0),
    u_count(0),
    v_count(0),
    render_lines(true),
    render_facets(false)
{}
skeleton::~skeleton(void)
{
    if (vertex)
    {
        delete [] vertex[0];
        delete [] vertex;
    }

    if (normal)
    {
        delete [] normal[0];
        delete [] normal;
    }

    if (tex)
    {
        delete [] tex[0];
        delete [] tex;
    }

    if (idx)
    {
        delete [] idx[0];
        delete [] idx;
    }
}

void skeleton::render(void)
{
    if (render_facets)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertex[0]);
        glNormalPointer(GL_FLOAT, 0, normal[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, tex[0]);
        if (u_count == 1)
        {
            glDrawArrays(GL_POLYGON, 0, v_count);
        }
        else
        {
            glDrawElements(GL_QUADS, (u_count - 1) * (v_count - 1) * 4, GL_UNSIGNED_SHORT, idx[0]);
        }

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    glDisable(GL_DEPTH_TEST);

    if (render_lines)
    {
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertex[0]);

        if (u_count == 1)
        {
            glDrawArrays(GL_LINE_STRIP, 0, v_count);
        }
        else
        {
            for (int i = 0; i < u_count; i++)
                glDrawArrays(GL_LINE_STRIP, i * v_count, v_count);

            for (int i = 0; i < v_count; i++)
            {
                glVertexPointer(3, GL_FLOAT, v_count * sizeof(f3), &vertex[0][i]);
                glDrawArrays(GL_LINE_STRIP, 0, u_count);
            }
        }
        
        glDisableClientState(GL_VERTEX_ARRAY);
    }
////////////////////////////////////////////////////////////////////////////////
    #ifdef SHOW_NORMALS

    glPushAttrib(GL_TEXTURE_BIT);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);
    for (int i = 0; i < u_count; i++)
    {
        for (int j = 0; j < v_count; j++)
        {
            glVertex3f(vertex[i][j][0], vertex[i][j][1], vertex[i][j][2]);
            glVertex3f(vertex[i][j][0] + normal[i][j][0] * NORMAL_SIZE, vertex[i][j][1] + normal[i][j][1] * NORMAL_SIZE, vertex[i][j][2] + normal[i][j][2] * NORMAL_SIZE);
        }
    }
    glEnd();

    glPopAttrib();
    
    #endif
////////////////////////////////////////////////////////////////////////////////

    glEnable(GL_DEPTH_TEST);
}

/*
нормаль к поверхности заданной параметрически
x = x(u, v)
y = y(u, v)
z = z(u, v)

|  i      j      k      |
|  dx/du  dy/du  dz/du  |
|  dx/dv  dy/dv  dz/dv  |

n = A i + B j + C k

A = dy/du * dz/dv - dz/du * dy/dv
B = dz/du * dx/dv - dx/du * dz/dv
C = dx/du * dy/dv - dy/du * dx/dv
*/

void get_normal
(
    float *x, float *y, float *z,
    float dx_du, float dx_dv,
    float dy_du, float dy_dv,
    float dz_du, float dz_dv
)
{
    *x = dy_du * dz_dv - dz_du * dy_dv;
    *y = dz_du * dx_dv - dx_du * dz_dv;
    *z = dx_du * dy_dv - dy_du * dx_dv;
    float m = sqrt(fabs(*x * *x + *y * *y + *z * *z));
    *x /= m;
    *y /= m;
    *z /= m;
}

void create_ellipsoid
(
    skeleton *s,
    float rx,
    int u_count,
    int v_count,
    float u_1,
    float u_2,
    float v_1,
    float v_2,
    float rry,
    float rrz
)
{
    if (s->vertex) return;

    s->u_count = u_count;
    s->v_count = v_count;

    if (u_1 < skeleton_eps) u_1 = skeleton_eps;
    if (180 - u_2 < skeleton_eps) u_2 = 180 - skeleton_eps;

    if (u_2 - u_1 < skeleton_eps) u_2 = u_1 + skeleton_eps;
    if (v_2 - v_1 < skeleton_eps) v_2 = v_1 + skeleton_eps;

    u_1 *= RAD_IN_DEG;
    u_2 *= RAD_IN_DEG;
    v_1 *= RAD_IN_DEG;
    v_2 *= RAD_IN_DEG;

    float ry = rx * rry;
    float rz = rx * rrz;

    if (rx < skeleton_eps) rx = skeleton_eps;
    if (ry < skeleton_eps) ry = skeleton_eps;
    if (rz < skeleton_eps) rz = skeleton_eps;

    skeleton::f3 *vertex = new skeleton::f3[u_count * v_count];

    s->vertex = new skeleton::f3 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->vertex[i] = vertex;
        vertex += v_count;
    }

    skeleton::f3 *normal = new skeleton::f3[u_count * v_count];

    s->normal = new skeleton::f3 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->normal[i] = normal;
        normal += v_count;
    }

    skeleton::f2 *tex = new skeleton::f2[u_count * v_count];

    s->tex = new skeleton::f2 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->tex[i] = tex;
        tex += v_count;
    }

    float u_2_1 = u_2 - u_1;
    float v_2_1 = v_2 - v_1;
    float du = u_2_1 / (u_count - 1);
    float dv = v_2_1 / (v_count - 1);

    for (int i = 0; i < u_count; i++)
    {
        float u = u_1 + i * du;

        float sin_u = sin(u);
        float cos_u = cos(u);

        for (int j = 0; j < v_count; j++)
        {
            float v = v_1 + j * dv;

            float sin_v = sin(v);
            float cos_v = cos(v);

            s->vertex[i][j][0] = rx * sin_u * cos_v;
            s->vertex[i][j][1] = ry * sin_u * sin_v;
            s->vertex[i][j][2] = rz * cos_u;

            get_normal
            (
                &s->normal[i][j][0], &s->normal[i][j][1], &s->normal[i][j][2],
                rx * cos_u * cos_v, -rx * sin_u * sin_v,
                ry * cos_u * sin_v, ry * sin_u * cos_v,
                -rz * sin_u, 0
            );

            s->tex[i][j][0] = i * du / u_2_1;
            s->tex[i][j][1] = j * dv / v_2_1;
        }
    }

    create_idxes(s);
}

void create_elliptical_cylinder
(
    skeleton *s,
    float rx_1,
    float rx_2,
    int u_count,
    int v_count,
    float u_1,
    float u_2,
    float v_1,
    float v_2,
    float rry_1,
    float rry_2
)
{
    if (s->vertex) return;

    s->u_count = u_count;
    s->v_count = v_count;

    if (v_2 - v_1 < skeleton_eps) v_2 = v_1 + skeleton_eps;

    v_1 *= RAD_IN_DEG;
    v_2 *= RAD_IN_DEG;

    float ry_1 = rx_1 * rry_1;
    float ry_2 = rx_2 * rry_2;

    if (rx_1 < skeleton_eps) rx_1 = skeleton_eps;
    if (rx_2 < skeleton_eps) rx_2 = skeleton_eps;
    if (ry_1 < skeleton_eps) ry_1 = skeleton_eps;
    if (ry_2 < skeleton_eps) ry_2 = skeleton_eps;

    if (u_2 - u_1 < skeleton_eps) u_2 = u_1 + skeleton_eps;

    skeleton::f3 *vertex = new skeleton::f3[u_count * v_count];

    s->vertex = new skeleton::f3 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->vertex[i] = vertex;
        vertex += v_count;
    }

    skeleton::f3 *normal = new skeleton::f3[u_count * v_count];

    s->normal = new skeleton::f3 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->normal[i] = normal;
        normal += v_count;
    }

    skeleton::f2 *tex = new skeleton::f2[u_count * v_count];

    s->tex = new skeleton::f2 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->tex[i] = tex;
        tex += v_count;
    }

    float drx = (rx_2 - rx_1) / (u_count - 1);
    float dry = (ry_2 - ry_1) / (u_count - 1);
    float u_2_1 = u_2 - u_1;
    float v_2_1 = v_2 - v_1;
    float du = u_2_1 / (u_count - 1);
    float dv = v_2_1 / (v_count - 1);
    float kx = drx / du;
    float ky = dry / du;

    for (int i = 0; i < u_count; i++)
    {
        float rx = rx_2 - i * drx;
        float ry = ry_2 - i * dry;
        float u = u_2 - i * du;

        for (int j = 0; j < v_count; j++)
        {
            float v = v_1 + j * dv;

            float sin_v = sin(v);
            float cos_v = cos(v);

            s->vertex[i][j][0] = rx * cos_v;
            s->vertex[i][j][1] = ry * sin_v;
            s->vertex[i][j][2] = u;

            get_normal
            (
                &s->normal[i][j][0], &s->normal[i][j][1], &s->normal[i][j][2],
                -kx * cos_v, -rx * sin_v,
                -ky * sin_v, rx * cos_v,
                -1, 0
            );

            s->tex[i][j][0] = i * du / u_2_1;
            s->tex[i][j][1] = j * dv / v_2_1;
        }
    }

    create_idxes(s);
}

void create_elliptical_torus
(
    skeleton *s,
    float R,
    float rx_1,
    float rx_2,
    int u_count,
    int v_count,
    float u_1,
    float u_2,
    float v_1,
    float v_2,
    float rry_1,
    float rry_2
)
{
    if (s->vertex) return;

    s->u_count = u_count;
    s->v_count = v_count;

    if (u_2 - u_1 < skeleton_eps) u_2 = u_1 + skeleton_eps;
    if (v_2 - v_1 < skeleton_eps) v_2 = v_1 + skeleton_eps;

    v_1 *= RAD_IN_DEG;
    v_2 *= RAD_IN_DEG;
    u_1 *= RAD_IN_DEG;
    u_2 *= RAD_IN_DEG;

    float ry_1 = rx_1 * rry_1;
    float ry_2 = rx_2 * rry_2;

    if (rx_1 < skeleton_eps) rx_1 = skeleton_eps;
    if (rx_2 < skeleton_eps) rx_2 = skeleton_eps;
    if (ry_1 < skeleton_eps) ry_1 = skeleton_eps;
    if (ry_2 < skeleton_eps) ry_2 = skeleton_eps;

    skeleton::f3 *vertex = new skeleton::f3[u_count * v_count];

    s->vertex = new skeleton::f3 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->vertex[i] = vertex;
        vertex += v_count;
    }

    skeleton::f3 *normal = new skeleton::f3[u_count * v_count];

    s->normal = new skeleton::f3 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->normal[i] = normal;
        normal += v_count;
    }

    skeleton::f2 *tex = new skeleton::f2[u_count * v_count];

    s->tex = new skeleton::f2 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->tex[i] = tex;
        tex += v_count;
    }

    float drx = (rx_2 - rx_1) / (u_count - 1);
    float dry = (ry_2 - ry_1) / (u_count - 1);
    float u_2_1 = u_2 - u_1;
    float v_2_1 = v_2 - v_1;
    float du = u_2_1 / (u_count - 1);
    float dv = v_2_1 / (v_count - 1);
    float kx = drx / du;
    float ky = dry / du;

    for (int i = 0; i < u_count; i++)
    {
        float rx = rx_1 + i * drx;
        float ry = ry_1 + i * dry;
        float u = u_1 + i * du;

        float sin_u = sin(u);
        float cos_u = cos(u);

        for (int j = 0; j < v_count; j++)
        {
            float v = v_1 + j * dv;

            float sin_v = sin(v);
            float cos_v = cos(v);

            s->vertex[i][j][0] = (R + rx * cos_v) * cos_u;
            s->vertex[i][j][1] = (R + rx * cos_v) * sin_u;
            s->vertex[i][j][2] = ry * sin_v;

            get_normal
            (
                &s->normal[i][j][0], &s->normal[i][j][1], &s->normal[i][j][2],
                kx * cos_v * cos_u - (R + rx * cos_v) * sin_u, -rx * sin_v * cos_u,
                kx * cos_v * sin_u + (R + rx * cos_v) * cos_u, -rx * sin_v * sin_u,
                ky * sin_v, ry * cos_v
            );

            s->tex[i][j][0] = i * du / u_2_1;
            s->tex[i][j][1] = j * dv / v_2_1;
        }
    }

    create_idxes(s);
}

void create_box
(
    skeleton *s,
    float dx,
    float dy,
    float dz
)
{
    if (s->vertex) return;

    s->u_count = 2;
    s->v_count = 5;

    skeleton::f3 *vertex = new skeleton::f3[10];

    s->vertex = new skeleton::f3 *[2];
    for (int i = 0; i < 2; i++)
    {
        s->vertex[i] = vertex;
        vertex += 5;
    }

    skeleton::f3 *normal = new skeleton::f3[10];

    s->normal = new skeleton::f3 *[2];
    for (int i = 0; i < 2; i++)
    {
        s->normal[i] = normal;
        normal += 5;
    }

    skeleton::f2 *tex = new skeleton::f2[10];

    s->tex = new skeleton::f2 *[2];
    for (int i = 0; i < 2; i++)
    {
        s->tex[i] = tex;
        tex += 5;
    }
////////////////////////////////////////////////////////////////////////////////
    s->vertex[0][0][0] = 0;
    s->vertex[0][0][1] = 0;
    s->vertex[0][0][2] = dz;

    s->vertex[0][1][0] = dx;
    s->vertex[0][1][1] = 0;
    s->vertex[0][1][2] = dz;

    s->vertex[0][2][0] = dx;
    s->vertex[0][2][1] = dy;
    s->vertex[0][2][2] = dz;

    s->vertex[0][3][0] = 0;
    s->vertex[0][3][1] = dy;
    s->vertex[0][3][2] = dz;

    s->vertex[0][4][0] = 0;
    s->vertex[0][4][1] = 0;
    s->vertex[0][4][2] = dz;
////////////////////////////////////////////////////////////////////////////////
    s->normal[0][0][0] = -0.7071;
    s->normal[0][0][1] = -0.7071;
    s->normal[0][0][2] = 0;

    s->normal[0][1][0] = 0.7071;
    s->normal[0][1][1] = -0.7071;
    s->normal[0][1][2] = 0;

    s->normal[0][2][0] = 0.7071;
    s->normal[0][2][1] = 0.7071;
    s->normal[0][2][2] = 0;

    s->normal[0][3][0] = -0.7071;
    s->normal[0][3][1] = 0.7071;
    s->normal[0][3][2] = 0;

    s->normal[0][4][0] = -0.7071;
    s->normal[0][4][1] = -0.7071;
    s->normal[0][4][2] = 0;
////////////////////////////////////////////////////////////////////////////////
    s->tex[0][0][0] = 0;
    s->tex[0][0][1] = 0;

    s->tex[0][1][0] = 0;
    s->tex[0][1][1] = 0.25;

    s->tex[0][2][0] = 0;
    s->tex[0][2][1] = 0.5;

    s->tex[0][3][0] = 0;
    s->tex[0][3][1] = 0.75;

    s->tex[0][4][0] = 0;
    s->tex[0][4][1] = 1;
////////////////////////////////////////////////////////////////////////////////
    for (int j = 0; j < 5; j++)
    {
        s->vertex[1][j][0] = s->vertex[0][j][0];
        s->vertex[1][j][1] = s->vertex[0][j][1];
        s->vertex[1][j][2] = 0;

        s->normal[1][j][0] = s->normal[0][j][0];
        s->normal[1][j][1] = s->normal[0][j][1];
        s->normal[1][j][2] = 0;

        s->tex[1][j][0] = 1;
        s->tex[1][j][1] = s->tex[0][j][1];
    }

    create_idxes(s);
}

void create_idxes(skeleton *s)
{
    if (s->idx || s->u_count == 1) return;

    int u_count = s->u_count - 1;
    int v_count = s->v_count - 1;

    skeleton::us4 *idx = new skeleton::us4[u_count * v_count];

    s->idx = new skeleton::us4 *[u_count];
    for (int i = 0; i < u_count; i++)
    {
        s->idx[i] = idx;
        idx += v_count;
    }

    idx = s->idx[0];

    for (int i = 1; i < s->u_count; i++)
    {
        for (int j = 1; j < s->v_count; j++)
        {
            (*idx)[0] = i * s->v_count + j - 1;
            (*idx)[1] = i * s->v_count + j;
            (*idx)[2] = (i - 1) * s->v_count + j;
            (*idx)[3] = (i - 1) * s->v_count + j - 1;
            idx++;
        }
    }
}

void create_normals
(
    skeleton *s,
    int n_avg
)
{
    if (s->normal || s->u_count == 1) return;

    skeleton::f3 *normal = new skeleton::f3[s->u_count * s->v_count];

    s->normal = new skeleton::f3 *[s->u_count];
    for (int i = 0; i < s->u_count; i++)
    {
        s->normal[i] = normal;
        normal += s->v_count;
    }

    //начальное значение сумм нормалей

    for (int i = 0; i < s->u_count; i++)
    {
        for (int j = 0; j < s->v_count; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                s->normal[i][j][k] = 0;
            }
        }
    }

    for (int i = 1; i < s->u_count; i++)
    {
        for (int j = 1; j < s->v_count; j++)
        {
            //вершины грани

            skeleton::f3 *p_0 = &s->vertex[i][j - 1];
            skeleton::f3 *p_1 = &s->vertex[i][j];
            skeleton::f3 *p_2 = &s->vertex[i - 1][j];
            skeleton::f3 *p_3 = &s->vertex[i - 1][j - 1];

            //единичные ребра грани

            skeleton::f3 v_1_0 = {(*p_1)[0] - (*p_0)[0], (*p_1)[1] - (*p_0)[1], (*p_1)[2] - (*p_0)[2]};
            float m_v_1_0 = sqrt(fabs(v_1_0[0] * v_1_0[0] + v_1_0[1] * v_1_0[1] + v_1_0[2] * v_1_0[2]));
            v_1_0[0] /= m_v_1_0;
            v_1_0[1] /= m_v_1_0;
            v_1_0[2] /= m_v_1_0;

            skeleton::f3 v_3_0 = {(*p_3)[0] - (*p_0)[0], (*p_3)[1] - (*p_0)[1], (*p_3)[2] - (*p_0)[2]};
            float m_v_3_0 = sqrt(fabs(v_3_0[0] * v_3_0[0] + v_3_0[1] * v_3_0[1] + v_3_0[2] * v_3_0[2]));
            v_3_0[0] /= m_v_3_0;
            v_3_0[1] /= m_v_3_0;
            v_3_0[2] /= m_v_3_0;

            skeleton::f3 v_3_2 = {(*p_3)[0] - (*p_2)[0], (*p_3)[1] - (*p_2)[1], (*p_3)[2] - (*p_2)[2]};
            float m_v_3_2 = sqrt(fabs(v_3_2[0] * v_3_2[0] + v_3_2[1] * v_3_2[1] + v_3_2[2] * v_3_2[2]));
            v_3_2[0] /= m_v_3_2;
            v_3_2[1] /= m_v_3_2;
            v_3_2[2] /= m_v_3_2;

            skeleton::f3 v_1_2 = {(*p_1)[0] - (*p_2)[0], (*p_1)[1] - (*p_2)[1], (*p_1)[2] - (*p_2)[2]};
            float m_v_1_2 = sqrt(fabs(v_1_2[0] * v_1_2[0] + v_1_2[1] * v_1_2[1] + v_1_2[2] * v_1_2[2]));
            v_1_2[0] /= m_v_1_2;
            v_1_2[1] /= m_v_1_2;
            v_1_2[2] /= m_v_1_2;

            //единичная нормаль, как векторное произведение ребер грани

            skeleton::f3 n;

            if (m_v_1_0 < skeleton_eps || m_v_3_0 < skeleton_eps)
            {
                n[0] = v_3_2[1] * v_1_2[2] - v_3_2[2] * v_1_2[1];
                n[1] = v_3_2[2] * v_1_2[0] - v_3_2[0] * v_1_2[2];
                n[2] = v_3_2[0] * v_1_2[1] - v_3_2[1] * v_1_2[0];
            }
            else
            {
                n[0] = v_1_0[1] * v_3_0[2] - v_1_0[2] * v_3_0[1];
                n[1] = v_1_0[2] * v_3_0[0] - v_1_0[0] * v_3_0[2];
                n[2] = v_1_0[0] * v_3_0[1] - v_1_0[1] * v_3_0[0];
            }

            float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
            n[0] /= m;
            n[1] /= m;
            n[2] /= m;

            //сумма нормалей

            for (int k = 0; k < 3; k++)
            {
                s->normal[i][j - 1][k] += n[k];
                s->normal[i][j][k] += n[k];
                s->normal[i - 1][j][k] += n[k];
                s->normal[i - 1][j - 1][k] += n[k];
            }
        }
    }

    //нормирование сумм нормалей; фактически - усреднение

    for (int i = 0; i < s->u_count; i++)
    {
        for (int j = 0; j < s->v_count; j++)
        {
            float m = sqrt(fabs(s->normal[i][j][0] * s->normal[i][j][0] + s->normal[i][j][1] * s->normal[i][j][1] + s->normal[i][j][2] * s->normal[i][j][2]));
            s->normal[i][j][0] /= m;
            s->normal[i][j][1] /= m;
            s->normal[i][j][2] /= m;
        }
    }

    //дополнительное усреднение обусловленное наличием швов

    if (n_avg & u_1_2_n_avg)
    {
        for (int j = 0; j < s->v_count; j++)
        {
            skeleton::f3 n = {s->normal[s->u_count - 1][j][0] + s->normal[0][j][0], s->normal[s->u_count - 1][j][1] + s->normal[0][j][1], s->normal[s->u_count - 1][j][2] + s->normal[0][j][2]};
            float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
            n[0] /= m;
            n[1] /= m;
            n[2] /= m;

            s->normal[s->u_count - 1][j][0] = n[0];
            s->normal[s->u_count - 1][j][1] = n[1];
            s->normal[s->u_count - 1][j][2] = n[2];

            s->normal[0][j][0] = n[0];
            s->normal[0][j][1] = n[1];
            s->normal[0][j][2] = n[2];
        }
    }
    if (n_avg & v_1_2_n_avg)
    {
        for (int i = 0; i < s->u_count; i++)
        {
            skeleton::f3 n = {s->normal[i][s->v_count - 1][0] + s->normal[i][0][0], s->normal[i][s->v_count - 1][1] + s->normal[i][0][1], s->normal[i][s->v_count - 1][2] + s->normal[i][0][2]};
            float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
            n[0] /= m;
            n[1] /= m;
            n[2] /= m;

            s->normal[i][s->v_count - 1][0] = n[0];
            s->normal[i][s->v_count - 1][1] = n[1];
            s->normal[i][s->v_count - 1][2] = n[2];

            s->normal[i][0][0] = n[0];
            s->normal[i][0][1] = n[1];
            s->normal[i][0][2] = n[2];
        }
    }
    if (n_avg & u_1_n_avg)
    {
        skeleton::f3 n = {0, 0, 0};

        for (int j = 0; j < s->v_count; j++)
        {
            n[0] += s->normal[0][j][0];
            n[1] += s->normal[0][j][1];
            n[2] += s->normal[0][j][2];
        }

        float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
        n[0] /= m;
        n[1] /= m;
        n[2] /= m;

        for (int j = 0; j < s->v_count; j++)
        {
            s->normal[0][j][0] = n[0];
            s->normal[0][j][1] = n[1];
            s->normal[0][j][2] = n[2];
        }
    }
    if (n_avg & u_2_n_avg)
    {
        skeleton::f3 n = {0, 0, 0};

        for (int j = 0; j < s->v_count; j++)
        {
            n[0] += s->normal[s->u_count - 1][j][0];
            n[1] += s->normal[s->u_count - 1][j][1];
            n[2] += s->normal[s->u_count - 1][j][2];
        }

        float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
        n[0] /= m;
        n[1] /= m;
        n[2] /= m;

        for (int j = 0; j < s->v_count; j++)
        {
            s->normal[s->u_count - 1][j][0] = n[0];
            s->normal[s->u_count - 1][j][1] = n[1];
            s->normal[s->u_count - 1][j][2] = n[2];
        }
    }
    if (n_avg & v_1_n_avg)
    {
        skeleton::f3 n = {0, 0, 0};

        for (int i = 0; i < s->u_count; i++)
        {
            n[0] += s->normal[i][0][0];
            n[1] += s->normal[i][0][1];
            n[2] += s->normal[i][0][2];
        }

        float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
        n[0] /= m;
        n[1] /= m;
        n[2] /= m;

        for (int i = 0; i < s->u_count; i++)
        {
            s->normal[i][0][0] = n[0];
            s->normal[i][0][1] = n[1];
            s->normal[i][0][2] = n[2];
        }
    }
    if (n_avg & v_2_n_avg)
    {
        skeleton::f3 n = {0, 0, 0};

        for (int i = 0; i < s->u_count; i++)
        {
            n[0] += s->normal[i][s->v_count - 1][0];
            n[1] += s->normal[i][s->v_count - 1][1];
            n[2] += s->normal[i][s->v_count - 1][2];
        }

        float m = sqrt(fabs(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
        n[0] /= m;
        n[1] /= m;
        n[2] /= m;

        for (int i = 0; i < s->u_count; i++)
        {
            s->normal[i][s->v_count - 1][0] = n[0];
            s->normal[i][s->v_count - 1][1] = n[1];
            s->normal[i][s->v_count - 1][2] = n[2];
        }
    }
}

