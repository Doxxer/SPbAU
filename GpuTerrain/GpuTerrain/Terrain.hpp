#ifndef GpuTerrain_Terrain_hpp
#define GpuTerrain_Terrain_hpp

#include "Mesh.hpp"

class Terrain : public Mesh {
    float minX;
    float maxX;
    float minZ;
    float maxZ;

public:
    Terrain(float f_minX = 0, float f_maxX = 0, float f_minZ = 0, float f_maxZ = 0) :
        minX(f_minX), maxX(f_maxX), minZ(f_minZ), maxZ(f_maxZ)
    {
    
    }

    void GenerateTerrainData()
    {
        float stepX = 5.0;
        float stepZ = 5.0;

        int numX = int((maxX - minX) / stepX) + 1;

        // Create all vertices
        for (float incrZ = -minZ; incrZ >= -maxZ; incrZ -= stepZ) {
            float incrX = minX;
            for (int i = 0; i < numX; ++i) {
                vertices.push_back(vec3(incrX, 0, incrZ));
                normals.push_back(vec3(0, 1, 0));
                incrX += stepX;
            }
        }

        // Create triangular faces
        for (unsigned int i = numX + 1; i < (unsigned int)vertices.size(); ++i) {
            if (i % numX == 0)
                continue;
            faces.push_back(Triangle(i - 1, (i - 1) - numX, i - numX));
            faces.push_back(Triangle(i - numX, i, i - 1));
        }
    }
};

#endif
