#pragma once

#include <string>
#include <vector>
#include <memory>

// ---------------------------------------------------------------------------
// Primitives
// ---------------------------------------------------------------------------

struct ScadCube {
    double dx = 1.0, dy = 1.0, dz = 1.0;
    bool   center = false;
};

// ---------------------------------------------------------------------------
// Scene-graph node: either a primitive or a transform with children
// ---------------------------------------------------------------------------

enum class ScadNodeType { Cube, Translate, Rotate };

struct ScadNode {
    ScadNodeType type;

    // Primitive payload (valid when type == Cube)
    ScadCube cube;

    // Transform payload (valid when type == Translate or Rotate)
    double tx = 0, ty = 0, tz = 0;   // translate vector / rotate angles (degrees)
    std::vector<std::shared_ptr<ScadNode>> children;
};

// ---------------------------------------------------------------------------
// Top-level parsed model
// ---------------------------------------------------------------------------

struct ScadModel {
    std::vector<std::shared_ptr<ScadNode>> nodes;
    std::vector<std::string> warnings;

    bool empty() const { return nodes.empty(); }
};

// Parse an OpenSCAD source string.
ScadModel parseScadSource(const std::string& source);

// Convenience: read file then parse
ScadModel parseScadFile(const std::string& path);
