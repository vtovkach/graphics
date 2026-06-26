#include "mesh.hpp"

bool mesh::LoadFromObjFile(std::string filePath)
{
    std::ifstream file(filePath);
    if(!file.is_open())
        return false;

    
    std::vector<vec3d> verts; 
    while(!file.eof())
    {
        char line[128]; 
        file.getline(line, 128);

        std::stringstream s; 
        s << line; 

        char junk; 

        if(line[0] == 'v')
        {
            vec3d v; 
            s >> junk >> v.x >> v.y >> v.z;
            verts.push_back(v);
        }

        if(line[0] == 'f')
        {
            int f[3];
            s >> junk >> f[0] >> f[1] >> f[2];
            tris.push_back({verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]});
        }
    }
    return true; 
}