#include "MeshGroup.h"

namespace bmesh {

MeshGroup::MeshGroup() {}

void MeshGroup::addMesh(Mesh const & theMesh) {
	mMeshVec.push_back(theMesh);
}

} // namespace bmesh