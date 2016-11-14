#pragma once

#include "math.h"
#include "Vertex.h"

namespace bmesh {

class Mesh;
typedef std::unique_ptr<Mesh> MeshBox;
typedef std::shared_ptr<Mesh> MeshRef;

class Mesh {
public:
	Mesh() {}
	Mesh(Primitive primType) : mPrimitive(primType) {}

	uint getNumVertices() { return (uint) mVertexVec.size(); }
	uint getNumIndices() { return (uint) mIndexVec.size(); }
	Primitive getPrimitive() { return mPrimitive; }
	uint getNumPrimitiveIndices() { return static_cast<uint>(mPrimitive); }

	Vertex const * vertexData() { return mVertexVec.data(); }
	uint const * indexData() { return mIndexVec.data(); }
	std::vector<Vertex> const & getVertices() { return mVertexVec; }
	std::vector<uint> const & getIndices() { return mIndexVec; }

	void addVertex(Vertex const & v);
	void addIndex(uint i);
	void addTriangleIndexes(uint i0, uint i1, uint i2);

	void addLine(Vertex const & v1, Vertex const & v2);
	void addTriangle(Vertex const & v1, Vertex const & v2, Vertex const & v3);
	void addSimplePlane(vec3 lowerLeft, vec3 uVector, vec3 vVector);
	void addPlane(vec3 lowerLeft, vec3 uVector, vec3 vVector, uint subdivisions);
	void addBox(vec3 center, vec3 xdir, vec3 ydir, vec3 zdir);

	static MeshRef create() { return std::make_shared<Mesh>(); }
	static MeshBox box() { return MeshBox(new Mesh()); }

	static void assignTangentFrames(std::vector<Vertex> * vertices, std::vector<uint> const & indices, Primitive primType);

	static size_t getIndexSize() { return sizeof(uint); }
	static size_t getVertexSize() { return sizeof(Vertex); }

	std::vector<Vertex> mVertexVec;
	std::vector<uint> mIndexVec;
	Primitive mPrimitive = Primitive::Triangles;
	uint mShaderId;
	uint mTexId0;
	uint mTexId1;
	uint mTexId2;
	uint mTexId3;
};

} // namespace bmesh