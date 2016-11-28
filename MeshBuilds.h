#pragma once

#include "math.h"
#include "Vertex.h"
#include "Mesh.h"

namespace bmesh {

bmesh::MeshRef makeGraticule(vec3 center, float radius);

void assignTangentFrames(std::vector<Vertex> * vertices, std::vector<uint> const & indices, Primitive primType);

} // namespace bmesh