#ifndef GpuTerrain_Mesh_hpp
#define GpuTerrain_Mesh_hpp

#include <glm/glm.hpp>
#include <vector>

using glm::vec3;
using std::vector;

struct Triangle {
    unsigned int x;
    unsigned int y;
    unsigned int z;

    Triangle(unsigned int i_x, unsigned int i_y, unsigned int i_z) : x(i_x), y(i_y), z(i_z)
    {
    }
};

class Mesh {
public:
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<Triangle> faces;

    Mesh()
    {
    }

    virtual ~Mesh()
    {
        vertices.clear();
        normals.clear();
        faces.clear();
    }
};

#endif
