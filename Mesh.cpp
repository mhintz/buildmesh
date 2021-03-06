#include "Mesh.h"

namespace bmesh {

Mesh::Mesh(Primitive primType) : mPrimitive(primType) {}

void Mesh::addVertex(Vertex const & v) {
	mVertexVec.push_back(v);
}

inline void Mesh::addIndexedVertex(Vertex const & v) {
	this->addIndex(this->getNumVertices());
	this->addVertex(v);
}

void Mesh::addLineIndexes(uint i0, uint i1) {
	this->addIndex(i0);
	this->addIndex(i1);
}

void Mesh::addTriangleIndexes(uint i0, uint i1, uint i2) {
	this->addIndex(i0);
	this->addIndex(i1);
	this->addIndex(i2);
}

void Mesh::addLine(Vertex const & v1, Vertex const & v2) {
	addIndexedVertex(v1);
	addIndexedVertex(v2);
}

void Mesh::addTriangle(Vertex const & v1, Vertex const & v2, Vertex const & v3) {
	addIndexedVertex(v1);
	addIndexedVertex(v2);
	addIndexedVertex(v3);
}

void Mesh::addSimplePlane(vec3 lowerLeft, vec3 uVector, vec3 vVector) {
	vec3 planeNormal = normalize(cross(uVector, vVector));
	uint baseIndex = this->getNumVertices();

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
			uint vertIndex = this->getNumVertices();
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

void Mesh::addSphere(vec3 center, float radius, int hemiSubdivisions=24) {
	int greatCircleSubdivisions = 2 * hemiSubdivisions;
	float angleDelta = glm::pi<float>() / hemiSubdivisions;

	// Naive implementation has lots of degenerate triangles at top and bottom
	for (int latitude = 0; latitude <= hemiSubdivisions; latitude++) {
		for (int longitude = 0; longitude <= greatCircleSubdivisions; longitude++) {
			uint vertexNumber = this->getNumVertices();

			float latAngle = latitude * angleDelta;
			float lonAngle = longitude * angleDelta;

			vec3 posVector = normalize(getPointOnSphere(latAngle, lonAngle));
			vec3 vertexPos = center + radius * posVector;

			Vertex theVert = Vertex()
				.position(vertexPos)
				.normal(posVector)
				.tex(vec2(lonAngle / glm::two_pi<float>(), 1.f - latAngle / glm::pi<float>()));

			this->addVertex(theVert);

			if (latitude != 0 && longitude != 0) {
				// upper right tri
				this->addIndex(vertexNumber);
				this->addIndex(vertexNumber - (greatCircleSubdivisions + 1));
				this->addIndex(vertexNumber - (greatCircleSubdivisions + 1) - 1);
				// lower left tri
				this->addIndex(vertexNumber);
				this->addIndex(vertexNumber - (greatCircleSubdivisions + 1) - 1);
				this->addIndex(vertexNumber - 1);
			}
		}
	}
}

} // namespace bmesh