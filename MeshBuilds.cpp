#include "MeshBuilds.h"

namespace bmesh {

MeshRef makeGraticule(vec3 center, float radius) {
	MeshRef theMesh = Mesh::create(Primitive::Lines);

	int subdivisions = 24;
	float aperturesize = glm::pi<float>() / (subdivisions + 4);
	float vertChg = (glm::pi<float>() - 2 * aperturesize) / subdivisions;
	float horizChg = glm::two_pi<float>() / subdivisions;

	for (int latitude = 0; latitude <= subdivisions; latitude++) {
		float latAngle = aperturesize + latitude * vertChg;
		for (int longitude = 0; longitude <= subdivisions; longitude++) {
			uint vertexNumber = theMesh->getNumVertices();
			vec3 posVector = normalize(getPointOnSphere(latAngle, longitude * horizChg));
			vec3 vertexPos = center + radius * posVector;

			vec3 color;
			float tval = latAngle / glm::pi<float>();
			color = mix(vec3(1, 0, 1), vec3(0, 1, 0), glm::smoothstep(0.0f, 0.50f, tval));
			color = mix(color, vec3(1, 1, 0), glm::smoothstep(0.50f, 1.0f, tval));

			theMesh->addVertex(Vertex().position(vertexPos).color(color));

			if (longitude != 0) {
				// Connect to previous
				theMesh->addLineIndexes(vertexNumber, vertexNumber - 1);
			}

			if (latitude != 0) {
				// Connect to above. Gotta add one here, since there are (subdivisions + 1) vertices per ring
				theMesh->addLineIndexes(vertexNumber, vertexNumber - (subdivisions + 1));
			}
		}
	}

	return theMesh;
}

void assignTangentFrames(std::vector<Vertex> * vertices, std::vector<uint> const & indices, Primitive primType) {
	// TODO
}

} // namespace bmesh