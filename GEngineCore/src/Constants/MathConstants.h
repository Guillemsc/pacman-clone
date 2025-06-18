//
// Created by guillem on 6/16/25.
//

#ifndef MATHCONSTANTS_H
#define MATHCONSTANTS_H
#include "glm/vec3.hpp"

namespace GEngineCore {

class MathConstants
{
public:
	constexpr static glm::vec3 RIGHT = glm::vec3(1, 0, 0); // + X
	constexpr static glm::vec3 UP = glm::vec3(0, 1,  0);  // +Y
	constexpr static glm::vec3 FORWARD = glm::vec3(0, 0, -1);  // -Z in right-handed OpenGL
};

} // GEngineCore

#endif //MATHCONSTANTS_H
