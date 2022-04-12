#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

Mesh::Mesh() {
    std::cout << "Mesh constructor called!" << std::endl;
}

Mesh::~Mesh() {
    std::cout << "Mesh destructor called!" << std::endl;
}

void Mesh::AddVertex(Vec3 vertex) {
    vertices.push_back(vertex);
}

void Mesh::AddFace(int a, int b, int c) {
    faces.push_back({a, b, c});
}

int Mesh::GetNumberOfFaces() {
    return faces.size();
}

int Mesh::GetNumberOfVertices() {
    return vertices.size();
}

std::vector<Vec3> Mesh::GetFaceVertices(int i) {
    Face face = faces[i];

    Vec3 a = vertices[face.a - 1];
    Vec3 b = vertices[face.b - 1];
    Vec3 c = vertices[face.c - 1];

    std::vector<Vec3> result = {a, b, c};
    return result;
}

void Mesh::LoadObjFileData(const std::string& obj_file) {
    std::ifstream in(obj_file, std::ios::in);
    if (!in)
    {
        std::cerr << "Cannot open " << obj_file << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(in, line))
    {
        // Vertex information
        if (line.substr(0, 2) == "v ") {
            Vec3 vertex;
            std::istringstream v(line.substr(2));
            v >> vertex.x;
            v >> vertex.y;
            v >> vertex.z;
            AddVertex(vertex);
        }
        // Face information
        else if(line.substr(0,2) == "f ") {
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            const char* chh = line.c_str();
            sscanf(
                chh, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );
            AddFace(vertex_indices[0], vertex_indices[1], vertex_indices[2]);
        }
    }
    in.close();
}
