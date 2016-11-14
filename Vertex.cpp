#include "Vertex.h"

namespace bmesh {

Vertex Vertex::interpolate(Vertex const & v1, Vertex const & v2, float tval) {
	return Vertex()
		.position(mix(v1.mPosition, v2.mPosition, tval))
		.normal(normalize(mix(v1.mNormal, v2.mNormal, tval)))
		.color(normalize(mix(v1.mColor, v2.mColor, tval)))
		.tex(mix(v1.mTexCoord0, v2.mTexCoord0, tval));
}

Vertex Vertex::interpolate(Vertex const & v1, Vertex const & v2, vec3 tvals) {
	return Vertex()
		.position(mix(v1.mPosition, v2.mPosition, tvals))
		.normal(normalize(mix(v1.mNormal, v2.mNormal, tvals)))
		.color(normalize(mix(v1.mColor, v2.mColor, tvals)))
		.tex(mix(v1.mTexCoord0, v2.mTexCoord0, vec2(tvals.x, tvals.y)));
}

} // namespace bmesh