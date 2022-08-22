//---------------------------------------------------------------------------
#include "stl_utils.h"
//---------------------------------------------------------------------------
#include <fstream>
//---------------------------------------------------------------------------
void read_facets_stl_txt(const char *file_name, std::list<facet> * const facets)
{
    facets->clear();

    std::ifstream is(file_name);

    while (true)
    {
        std::string key;
        is >> key;

        if (key == "facet")
        {
            facets->push_back();
            facets->back().n.push_back();
            std::string t;
            is >> t >> facets->back().n.back().x >> facets->back().n.back().y >> facets->back().n.back().z;
            facets->back().n.push_back(facets->back().n.back());
            facets->back().n.push_back(facets->back().n.back());
        }
        else if (key == "vertex")
        {
            facets->back().v.push_back();
            is >> facets->back().v.back().x >> facets->back().v.back().y >> facets->back().v.back().z;
        }

        if (is.peek() == EOF) break;
    }

    is.close();
}

void read_facets_stl_bin(const char *file_name, std::list<facet> * const facets)
{
    #pragma pack(push)
    #pragma pack(1)

    struct
    {
        char comment[80];
        unsigned long n;
    } stl_bin_header = {"", 0};

    struct
    {
        float normal[3];
        float vertex[3][3];
        unsigned short attr;
    } stl_bin_facet;

    #pragma pack(pop)

    facets->clear();

    std::ifstream is(file_name, std::ios::in | std::ios::binary);

    is.read((char *)&stl_bin_header, sizeof(stl_bin_header));

    for (int i = 0; i < stl_bin_header.n; i++)                     
    {
        is.read((char *)&stl_bin_facet, sizeof(stl_bin_facet));

        facets->push_back();

        for (int j = 0; j < 3; j++)
        {
            facets->back().n.push_back();
            memcpy(&facets->back().n.back().x, stl_bin_facet.normal, sizeof(stl_bin_facet.normal));

            facets->back().v.push_back();
            memcpy(&facets->back().v.back().x, stl_bin_facet.vertex[j], sizeof(stl_bin_facet.vertex[j]));
        }
    }

    is.close();
}

