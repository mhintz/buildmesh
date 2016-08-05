#include "buildmesh.h"

using namespace bmesh;

Vertex Vertex::interp(Vertex const & v1, Vertex const & v2, vec3 tvals) {
	return Vertex()
		.position(mix(v1.mPosition, v2.mPosition, tvals))
		.normal(normalize(mix(v1.mNormal, v2.mNormal, tvals)))
		.tex(mix(v1.mTexCoord0, v2.mTexCoord0, vec2(tvals.x, tvals.y)));
}

void Mesh::addVertex(Vertex const & v) {
	mVertexVec.push_back(v);
}

void Mesh::addTriangle(uint i0, uint i1, uint i2) {
	mIndexVec.push_back(i0);
	mIndexVec.push_back(i1);
	mIndexVec.push_back(i2);
}

void Mesh::addTriangle(Vertex const & v1, Vertex const & v2, Vertex const & v3) {
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v1);
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v2);
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v3);
}

void Mesh::addPlane(vec3 lowerLeft, vec3 uVector, vec3 vVector, uint subdivisions) {
	vec3 planeNormal = normalize(cross(uVector, vVector));

	vec3 uInc = uVector / (float) subdivisions;
	vec3 vInc = vVector / (float) subdivisions;
	vec2 texUInc = vec2(1.0 / subdivisions, 0.0);
	vec2 texVInc = vec2(0.0, 1.0 / subdivisions);
	for (uint vCnt = 0; vCnt <= subdivisions; vCnt++) {
		float vMult = (float) vCnt;
		for (uint uCnt = 0; uCnt <= subdivisions; uCnt++) {
			uint vertIndex = mVertexVec.size();
			float uMult = (float) uCnt;

			Vertex theVert = Vertex()
				.position(lowerLeft + uMult * uInc + vMult * vInc)
				.normal(planeNormal)
				.tex(uMult * texUInc + vMult * texVInc);
			this->addVertex(theVert);

			// We don't add triangles for the leading edge vertices of both u and v dimensions
			if (uCnt != 0 && vCnt != 0) {
				uint prevRowVert = vertIndex - (subdivisions + 1);
				this->addTriangle(vertIndex - 1, prevRowVert - 1, prevRowVert);
				this->addTriangle(vertIndex, vertIndex - 1, prevRowVert);
			}
		}
	}
}