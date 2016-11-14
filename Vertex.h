#pragma once

#include "math.h"

namespace bmesh {

class Vertex;
typedef std::unique_ptr<Vertex> VertexBox;
typedef std::shared_ptr<Vertex> VertexRef;

class Vertex {
public:
	Vertex() {}

	Vertex & position(vec3 const & p) { mPosition = p; return *this; }
	Vertex & normal(vec3 const & n) { mNormal = n; return *this; }
	Vertex & color(vec3 const & c) { mColor = c; return *this; }
	Vertex & tex(vec2 const & t) { mTexCoord0 = t; return *this; }

	static VertexRef create() { return VertexRef(new Vertex()); }
	static VertexBox box() { return VertexBox(new Vertex()); }

	static Vertex interpolate(Vertex const & v1, Vertex const & v2, float tval);
	static Vertex interpolate(Vertex const & v1, Vertex const & v2, vec3 tvals);

	vec3 mPosition;
	vec3 mNormal;
	vec3 mColor;
	vec2 mTexCoord0;
	vec3 mTangent;
	vec3 mBitangent;
};

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

} // namespace bmesh