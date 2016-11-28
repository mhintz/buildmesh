#include "MeshBuilds.h"

namespace bmesh {

bmesh::MeshRef makeGraticule(vec3 center, float radius) {
	bmesh::MeshRef theMesh = std::make_shared<bmesh::Mesh>(bmesh::Primitive::Lines);

	int subdivisions = 24;
	float aperturesize = glm::pi<float>() / subdivisions;
	float vertChg = (glm::pi<float>() - 2 * aperturesize) / subdivisions;
	float horizChg = glm::two_pi<float>() / subdivisions;

	for (int latitude = 0; latitude <= subdivisions; latitude++) {
		for (int longitude = 0; longitude <= subdivisions; longitude++) {
			uint vertexNumber = theMesh->getNumVertices();
			float latAngle = aperturesize + latitude * vertChg;
			vec3 posVector = normalize(getPointOnSphere(latAngle, longitude * horizChg));
			vec3 vertexPos = center + radius * posVector;

			vec3 color;
			float tval = latAngle / (subdivisions * vertChg);
			color = mix(vec3(1, 0, 1), vec3(0, 1, 0), glm::smoothstep(0.0f, 0.5f, tval));
			color = mix(color, vec3(1, 1, 0), glm::smoothstep(0.5f, 1.0f, tval));

			theMesh->addVertex(bmesh::Vertex().position(vertexPos).color(color));

			if (longitude != 0) {
				// Connect to previous
				theMesh->addIndex(vertexNumber);
				theMesh->addIndex(vertexNumber - 1);
			}

			if (latitude != 0) {
				// Connect to above
				theMesh->addIndex(vertexNumber);
				// Gotta add one here, since there are (subdivisions + 1) vertices per ring
				theMesh->addIndex(vertexNumber - (subdivisions + 1));
			}
		}
	}

	return theMesh;
}

void assignTangentFrames(std::vector<Vertex> * vertices, std::vector<uint> const & indices, Primitive primType) {
	// TODO
}

} // namespace bmesh