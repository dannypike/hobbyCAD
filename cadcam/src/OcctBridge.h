#pragma once

#include "ScadParser.h"
#include "Mesh.h"

// Convert a parsed OpenSCAD model into a renderable SceneMesh
// using OpenCASCADE for solid modelling and tessellation.
SceneMesh buildMeshFromScad(const ScadModel& model);
