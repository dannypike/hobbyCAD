#pragma once

#include <string>
#include <vector>

// Parsed representation of an OpenSCAD cube() call
struct ScadCube {
    double dx = 1.0, dy = 1.0, dz = 1.0;
    bool   center = false;
};

// Parsed model containing all recognised primitives
struct ScadModel {
    std::vector<ScadCube> cubes;
    std::vector<std::string> warnings;   // lines we skipped / couldn't parse

    bool empty() const { return cubes.empty(); }
};

// Parse an OpenSCAD source string.  Only cube() is supported in v1.
ScadModel parseScadSource(const std::string& source);

// Convenience: read file then parse
ScadModel parseScadFile(const std::string& path);
