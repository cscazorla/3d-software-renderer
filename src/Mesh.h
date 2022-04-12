#ifndef MESH_H
#define MESH_H

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#include <vector>

struct Face {
    int a;
    int b;
    int c;
};

class Mesh {
    private:
        std::vector<Vec3> vertices;
        std::vector<Face> faces;
    public:
        Mesh();
        ~Mesh();

        void AddVertex(Vec3 vertex);
        void AddFace(int a, int b, int c);
        int GetNumberOfFaces();
        int GetNumberOfVertices();
        std::vector<Vec3> GetFaceVertices(int i);
        void LoadObjFileData(const std::string& obj_file);
};

#endif
