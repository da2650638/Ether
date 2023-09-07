#pragma once

#include <glm/glm.hpp>

namespace Ether::Math
{
	bool DecomposeTransform(const glm::mat4& transform, /*out*/glm::vec3& translation, /*out*/glm::vec3& rotation, /*out*/glm::vec3& scale);
}