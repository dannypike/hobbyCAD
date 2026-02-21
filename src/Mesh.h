#pragma once

#include <vector>
#include <cstdint>

// A single vertex with position and normal
struct MeshVertex {
    float px, py, pz;   // position
    float nx, ny, nz;   // normal
};

// Renderable mesh: triangulated faces + wireframe edges
struct SceneMesh {
    std::vector<MeshVertex> vertices;
    std::vector<uint32_t>   indices;     // triangle indices

    std::vector<float>      edgeVerts;   // edge line segments: x,y,z pairs

    void clear() {
        vertices.clear();
        indices.clear();
        edgeVerts.clear();
    }

    bool empty() const { return vertices.empty(); }
};
