#pragma once

#include "math.h"
#include "Mesh.h"

namespace bmesh {

class MeshGroup;
typedef std::unique_ptr<MeshGroup> MeshGroupBox;
typedef std::shared_ptr<MeshGroup> MeshGroupRef;

class MeshGroup {
public:
	MeshGroup();

	void addMesh(MeshRef const & theMesh);
	MeshRef createMesh(Primitive thePrim);

	static MeshGroupRef create() { return MeshGroupRef(new MeshGroup()); }
	static MeshGroupBox box() { return MeshGroupBox(new MeshGroup()); }

	std::vector<MeshRef> mMeshVec;
};

} // namespace bmesh