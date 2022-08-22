//---------------------------------------------------------------------------
#include "obj_utils.h"
//---------------------------------------------------------------------------
#include <fstream>
//---------------------------------------------------------------------------
void read_triangles_from_obj(const char *file_name, std::list<facet> * const facets)
{
    std::vector<vector> v;
    std::vector<vector> n;

    facets->clear();

    std::ifstream is(file_name);

    while (true)
    {
        std::string key;
        is >> key;

        if (key == "f")
        {
            facets->push_back();

            int v_idx;
            int t_idx = -1;
            int n_idx = -1;

            while (true)
            {
                is >> v_idx;
                if (v_idx < 0) v_idx += v.size() + 1;
                facets->back().v.push_back(v[v_idx - 1]);
                if (is.peek() == '/')
                {
                    is.ignore();
                    if (is.peek() != '/') is >> t_idx;
                }
                if (is.peek() == '/')
                {
                    is.ignore();
                    is >> n_idx;
                    if (n_idx < 0) n_idx += n.size() + 1;
                    facets->back().n.push_back(n[n_idx - 1]);
                }
                if (is.peek() == '\n')
                {
                    is.ignore();
                    break;
                }
            }

            if (n_idx == -1 && facets->back().v.size() >= 3)
            {
                facets->back().n.push_back(-(facets->back().v[0] - facets->back().v[1]) ^ (facets->back().v[2] - facets->back().v[1]));
                facets->back().n.back().normalize();
                for (int j = 1; j < facets->back().v.size(); j++)
                    facets->back().n.push_back(facets->back().n.back());
            }
        }
        else if (key == "v")
        {
            v.push_back();
            is >> v.back().x >> v.back().y >> v.back().z;
        }
        else if (key == "vt")
        {}
        else if (key == "vn")
        {
            n.push_back();
            is >> n.back().x >> n.back().y >> n.back().z;
        }

        if (is.peek() == EOF) break;
    }

    is.close();
}

