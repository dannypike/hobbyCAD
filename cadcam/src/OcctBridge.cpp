#include "OcctBridge.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopLoc_Location.hxx>
#include <Poly_Triangulation.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

#include <map>

// ---------------------------------------------------------------------------
// Build a TopoDS_Shape for one ScadCube
// ---------------------------------------------------------------------------
static TopoDS_Shape makeCubeShape(const ScadCube& c) {
    if (c.center) {
        gp_Pnt corner(-c.dx / 2.0, -c.dy / 2.0, -c.dz / 2.0);
        return BRepPrimAPI_MakeBox(corner, c.dx, c.dy, c.dz).Shape();
    } else {
        return BRepPrimAPI_MakeBox(c.dx, c.dy, c.dz).Shape();
    }
}

// ---------------------------------------------------------------------------
// Extract triangulated faces from a shape into SceneMesh
// ---------------------------------------------------------------------------
static void extractFaces(const TopoDS_Shape& shape, SceneMesh& mesh) {
    const double linearDeflection = 0.1;
    BRepMesh_IncrementalMesh mesher(shape, linearDeflection);
    mesher.Perform();

    uint32_t vertexOffset = static_cast<uint32_t>(mesh.vertices.size());

    for (TopExp_Explorer faceExp(shape, TopAbs_FACE); faceExp.More(); faceExp.Next()) {
        TopoDS_Face face = TopoDS::Face(faceExp.Current());
        TopLoc_Location loc;
        Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(face, loc);
        if (tri.IsNull()) continue;

        const gp_Trsf& trsf = loc.Transformation();
        bool reversed = (face.Orientation() == TopAbs_REVERSED);

        uint32_t baseIdx = static_cast<uint32_t>(mesh.vertices.size());

        // Vertices
        for (int i = 1; i <= tri->NbNodes(); ++i) {
            gp_Pnt p = tri->Node(i).Transformed(trsf);
            MeshVertex v{};
            v.px = static_cast<float>(p.X());
            v.py = static_cast<float>(p.Y());
            v.pz = static_cast<float>(p.Z());
            // Normals will be computed per-triangle below if not available
            v.nx = v.ny = v.nz = 0.0f;
            mesh.vertices.push_back(v);
        }

        // Triangles
        for (int i = 1; i <= tri->NbTriangles(); ++i) {
            int n1, n2, n3;
            tri->Triangle(i).Get(n1, n2, n3);
            if (reversed) std::swap(n2, n3);

            uint32_t i1 = baseIdx + static_cast<uint32_t>(n1 - 1);
            uint32_t i2 = baseIdx + static_cast<uint32_t>(n2 - 1);
            uint32_t i3 = baseIdx + static_cast<uint32_t>(n3 - 1);

            mesh.indices.push_back(i1);
            mesh.indices.push_back(i2);
            mesh.indices.push_back(i3);

            // Compute flat face normal and accumulate onto vertices
            auto& v1 = mesh.vertices[i1];
            auto& v2 = mesh.vertices[i2];
            auto& v3 = mesh.vertices[i3];

            float ax = v2.px - v1.px, ay = v2.py - v1.py, az = v2.pz - v1.pz;
            float bx = v3.px - v1.px, by = v3.py - v1.py, bz = v3.pz - v1.pz;
            float nx = ay * bz - az * by;
            float ny = az * bx - ax * bz;
            float nz = ax * by - ay * bx;

            v1.nx += nx; v1.ny += ny; v1.nz += nz;
            v2.nx += nx; v2.ny += ny; v2.nz += nz;
            v3.nx += nx; v3.ny += ny; v3.nz += nz;
        }
    }

    // Normalise accumulated normals
    for (size_t i = vertexOffset; i < mesh.vertices.size(); ++i) {
        auto& v = mesh.vertices[i];
        float len = std::sqrt(v.nx * v.nx + v.ny * v.ny + v.nz * v.nz);
        if (len > 1e-8f) {
            v.nx /= len; v.ny /= len; v.nz /= len;
        }
    }
}

// ---------------------------------------------------------------------------
// Extract wireframe edges from a shape into SceneMesh
// ---------------------------------------------------------------------------
static void extractEdges(const TopoDS_Shape& shape, SceneMesh& mesh) {
    for (TopExp_Explorer edgeExp(shape, TopAbs_EDGE); edgeExp.More(); edgeExp.Next()) {
        TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());
        try {
            BRepAdaptor_Curve curve(edge);
            GCPnts_TangentialDeflection discretizer(curve, 0.1, 0.1);
            for (int i = 1; i < discretizer.NbPoints(); ++i) {
                gp_Pnt p1 = discretizer.Value(i);
                gp_Pnt p2 = discretizer.Value(i + 1);
                mesh.edgeVerts.push_back(static_cast<float>(p1.X()));
                mesh.edgeVerts.push_back(static_cast<float>(p1.Y()));
                mesh.edgeVerts.push_back(static_cast<float>(p1.Z()));
                mesh.edgeVerts.push_back(static_cast<float>(p2.X()));
                mesh.edgeVerts.push_back(static_cast<float>(p2.Y()));
                mesh.edgeVerts.push_back(static_cast<float>(p2.Z()));
            }
        } catch (...) {
            // Degenerate edge – skip
        }
    }
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

SceneMesh buildMeshFromScad(const ScadModel& model) {
    SceneMesh mesh;

    for (const auto& cube : model.cubes) {
        TopoDS_Shape shape = makeCubeShape(cube);
        extractFaces(shape, mesh);
        extractEdges(shape, mesh);
    }

    return mesh;
}
