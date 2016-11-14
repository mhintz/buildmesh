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

class Angle {
public:
	virtual float val() = 0;
};

struct Degrees : public Angle {
	float mDegrees;

	Degrees(float d) : mDegrees(d) {};
	static Degrees fromRadians(float r) { return Degrees(glm::degrees(r)); };
	float val() { return mDegrees; }
};

struct Radians : public Angle {
	float mRadians;

	Radians(float r) : mRadians(r) {};
	static Radians fromDegrees(float d) { return Radians(glm::radians(d)); };
	float val() { return mRadians; }
};

enum class Primitive {
	Lines = 2,
	Triangles = 3
};

} // namespace bmesh
