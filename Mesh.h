#pragma once

#include "math.h"
#include "Vertex.h"

namespace bmesh {

class Mesh;
typedef std::unique_ptr<Mesh> MeshBox;
typedef std::shared_ptr<Mesh> MeshRef;

class Mesh {
public:
	Mesh(Primitive primType=Primitive::Triangles);

	void setTextureId(uint tid) { mTexId0 = tid; }
	void setShaderId(uint sid) { mShaderId = sid; }

	Primitive getPrimitive() { return mPrimitive; }
	uint getTextureId() { return mTexId0; }
	uint getShaderId() { return mShaderId; }
	inline uint getNumVertices() { return (uint) mVertexVec.size(); }
	inline uint getNumIndices() { return (uint) mIndexVec.size(); }
	uint getNumPrimitiveIndices() { return static_cast<uint>(mPrimitive); }

	Vertex const * vertexData() { return mVertexVec.data(); }
	uint const * indexData() { return mIndexVec.data(); }
	std::vector<Vertex> const & getVertices() { return mVertexVec; }
	std::vector<uint> const & getIndices() { return mIndexVec; }

	void addVertex(Vertex const & v);
	inline void addIndex(uint i) { mIndexVec.push_back(i); };
	void addIndexedVertex(Vertex const & v);
	void addLineIndexes(uint i0, uint i1);
	void addTriangleIndexes(uint i0, uint i1, uint i2);

	void addLine(Vertex const & v1, Vertex const & v2);
	void addTriangle(Vertex const & v1, Vertex const & v2, Vertex const & v3);
	void addSimplePlane(vec3 lowerLeft, vec3 uVector, vec3 vVector);
	void addPlane(vec3 lowerLeft, vec3 uVector, vec3 vVector, uint subdivisions);
	void addBox(vec3 center, vec3 xdir, vec3 ydir, vec3 zdir);
	void addSphere(vec3 center, float radius, int hemiSubdivisions);

	static MeshRef create() { return std::make_shared<Mesh>(); }
	static MeshRef create(Primitive primType) { return std::make_shared<Mesh>(primType); }
	static MeshBox box() { return MeshBox(new Mesh()); }

	static size_t getIndexSize() { return sizeof(uint); }
	static size_t getVertexSize() { return sizeof(Vertex); }

	Primitive mPrimitive = Primitive::Triangles;
	uint mShaderId;
	uint mTexId0;

	std::vector<uint> mIndexVec;
	std::vector<Vertex> mVertexVec;
};

} // namespace bmesh