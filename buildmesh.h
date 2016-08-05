#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace bmesh {

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::quat;

typedef unsigned int uint;

struct Degrees {
	float mDegrees;

	Degrees(float d) : mDegrees(d) {};
	static Degrees fromRadians(float r) { return Degrees(glm::degrees(r)); };
	float val() { return mDegrees; }
};

struct Radians {
	float mRadians;

	Radians(float r) : mRadians(r) {};
	static Radians fromDegrees(float d) { return Radians(glm::radians(d)); };
	float val() { return mRadians; }
};

class Vertex;
typedef std::unique_ptr<Vertex> VertexBox;
typedef std::shared_ptr<Vertex> VertexRef;

// Eventually, I want to get here:
// class Vertex {
// public:
// 	Vertex() {}

// 	Vertex & position(vec3 const & p) { mPosition = p; return *this; }
// 	Vertex & normal(vec3 const & n) { mNormal = n; return *this; }
// 	Vertex & tex(vec2 const & t) { mTexCoord0 = t; return *this; }
// 	Vertex & tex0(vec2 const & t) { mTexCoord0 = t; return *this; }
// 	Vertex & tex1(vec2 const & t) { mTexCoord1 = t; return *this; }
// 	Vertex & tex2(vec2 const & t) { mTexCoord2 = t; return *this; }
// 	Vertex & tex3(vec2 const & t) { mTexCoord3 = t; return *this; }
// 	Vertex & color(vec4 const & c) { mColor = c; return *this; }
// 	Vertex & tangent(vec3 const & t) { mTangent = t; return *this; }
// 	Vertex & bitangent(vec3 const & b) { mBitangent = b; return *this; }

// 	static VertexRef create() { return VertexRef(new Vertex()); }
// 	static VertexBox box() { return VertexBox(new Vertex()); }

// 	vec3 mPosition;
// 	vec3 mNormal;
// 	vec2 mTexCoord0;
// 	vec4 mColor;
// 	vec3 mTangent;
// 	vec3 mBitangent;
// 	vec2 mTexCoord1;
// 	vec2 mTexCoord2;
// 	vec2 mTexCoord3;
// };

// But for now, stick to this:
class Vertex {
public:
	Vertex() {}

	Vertex & position(vec3 const & p) { mPosition = p; return *this; }
	Vertex & normal(vec3 const & n) { mNormal = n; return *this; }
	Vertex & tex(vec2 const & t) { mTexCoord0 = t; return *this; }

	static VertexRef create() { return VertexRef(new Vertex()); }
	static VertexBox box() { return VertexBox(new Vertex()); }

	static Vertex interp(Vertex const & v1, Vertex const & v2, vec3 tvals);

	vec3 mPosition;
	vec3 mNormal;
	vec2 mTexCoord0;
	vec3 mTangent;
	vec3 mBitangent;
};

class Mesh;
typedef std::unique_ptr<Mesh> MeshBox;
typedef std::shared_ptr<Mesh> MeshRef;

class Mesh {
public:
	Mesh() {}

	void addVertex(Vertex const & v);
	void addTriangle(uint i0, uint i1, uint i2);
	void addTriangle(Vertex const & v1, Vertex const & v2, Vertex const & v3);
	void addPlane(vec3 lowerLeft, vec3 uVector, vec3 vVector, uint subdivisions);
	void addBox(vec3 positiveCorner, vec3 negativeCorner);

	static MeshRef create() { return MeshRef(new Mesh()); }
	static MeshBox box() { return MeshBox(new Mesh()); }

	static void assignTangentFrames(std::vector<Vertex> * vertices, std::vector<uint> const & indices);

	std::vector<Vertex> mVertexVec;
	std::vector<uint> mIndexVec;
	uint mShaderId;
	uint mTexId0;
	uint mTexId1;
	uint mTexId2;
	uint mTexId3;
};

class MeshGroup;
typedef std::unique_ptr<MeshGroup> MeshGroupBox;
typedef std::shared_ptr<MeshGroup> MeshGroupRef;

class MeshGroup {
public:
	MeshGroup();

	void addMesh(Mesh const & theMesh) { mMeshVec.push_back(theMesh); }

	static MeshGroupRef create() { return MeshGroupRef(new MeshGroup()); }
	static MeshGroupBox box() { return MeshGroupBox(new MeshGroup()); }

	std::vector<Mesh> mMeshVec;
};

}