//---------------------------------------------------------------------------
#include "edges_utils.h"
//---------------------------------------------------------------------------
#include <fstream>
//---------------------------------------------------------------------------
void read_edges_bin(const char *file_name, std::list<edge> * const edges)
{
    edges->clear();

    std::ifstream is(file_name, std::ios::in | std::ios::binary);

    while (true)
    {
        edges->push_back();

        is.read((char *)&edges->back().a.x, sizeof(float));
        is.read((char *)&edges->back().a.y, sizeof(float));
        is.read((char *)&edges->back().a.z, sizeof(float));

        is.read((char *)&edges->back().b.x, sizeof(float));
        is.read((char *)&edges->back().b.y, sizeof(float));
        is.read((char *)&edges->back().b.z, sizeof(float));

        if (is.peek() == EOF) break;
    }

    is.close();
}

void write_edges_bin(const char *file_name, std::list<edge> * const edges)
{
    std::ofstream os(file_name, std::ios::out | std::ios::binary);

    for
    (
        std::list<edge>::iterator i = edges->begin();
        i != edges->end();
        i++
    )
    {
        os.write((char *)&i->a.x, sizeof(float));
        os.write((char *)&i->a.y, sizeof(float));
        os.write((char *)&i->a.z, sizeof(float));

        os.write((char *)&i->b.x, sizeof(float));
        os.write((char *)&i->b.y, sizeof(float));
        os.write((char *)&i->b.z, sizeof(float));
    }

    os.close();
}

