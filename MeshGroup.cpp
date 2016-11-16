#include "math.h"
#include "MeshGroup.h"

namespace bmesh {

MeshGroup::MeshGroup() {}

void MeshGroup::addMesh(MeshRef const & theMesh) {
	mMeshVec.push_back(theMesh);
}

MeshRef MeshGroup::createMesh(Primitive thePrim=Primitive::Triangles) {
	auto theMesh = std::make_shared<Mesh>(thePrim);
	mMeshVec.push_back(theMesh);
	return theMesh;
}

} // namespace bmesh