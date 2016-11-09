#include "Mesh.h"

namespace bmesh {

void Mesh::addVertex(Vertex const & v) {
	mVertexVec.push_back(v);
}

void Mesh::addIndex(uint i) {
	mIndexVec.push_back(i);
}

void Mesh::addTriangleIndexes(uint i0, uint i1, uint i2) {
	mIndexVec.push_back(i0);
	mIndexVec.push_back(i1);
	mIndexVec.push_back(i2);
}

void Mesh::addLine(Vertex const & v1, Vertex const & v2) {
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v1);
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v2);
}

void Mesh::addTriangle(Vertex const & v1, Vertex const & v2, Vertex const & v3) {
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v1);
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v2);
	mIndexVec.push_back(mVertexVec.size());
	mVertexVec.push_back(v3);
}

void Mesh::addSimplePlane(vec3 lowerLeft, vec3 uVector, vec3 vVector) {
	vec3 planeNormal = normalize(cross(uVector, vVector));
	uint baseIndex = mVertexVec.size();

	this->addVertex(Vertex().position(lowerLeft).normal(planeNormal).tex(vec2(0.0, 0.0))); // lower left
	this->addVertex(Vertex().position(lowerLeft + uVector).normal(planeNormal).tex(vec2(1.0, 0.0))); // lower right
	this->addVertex(Vertex().position(lowerLeft + vVector).normal(planeNormal).tex(vec2(0.0, 1.0))); // upper left
	this->addVertex(Vertex().position(lowerLeft + uVector + vVector).normal(planeNormal).tex(vec2(1.0, 1.0))); // upper right

	this->addTriangleIndexes(baseIndex, baseIndex + 1, baseIndex + 2);
	this->addTriangleIndexes(baseIndex + 1, baseIndex + 3, baseIndex + 2);
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
				this->addTriangleIndexes(vertIndex - 1, prevRowVert - 1, prevRowVert);
				this->addTriangleIndexes(vertIndex, vertIndex - 1, prevRowVert);
			}
		}
	}
}

void Mesh::addBox(vec3 center, vec3 xdir, vec3 ydir, vec3 zdir) {
	vec3 xside = xdir * 2.0f;
	vec3 yside = ydir * 2.0f;
	vec3 zside = zdir * 2.0f;

	this->addSimplePlane(center + xdir - ydir + zdir, -xside, -zside); // bottom
	this->addSimplePlane(center - xdir - ydir + zdir, xside, yside); // front
	this->addSimplePlane(center - xdir + ydir + zdir, xside, -zside); // top
	this->addSimplePlane(center - xdir - ydir - zdir, zside, yside); // left
	this->addSimplePlane(center + xdir + ydir - zdir, zside, -yside); // right
	this->addSimplePlane(center + xdir - ydir - zdir, -xside, yside); // back
}

} // namespace bmesh