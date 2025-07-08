//
// Created by guillem on 7/8/25.
//

#ifndef VEC4PROPERTYDRAWEREDITOR_H
#define VEC4PROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"
#include "glm/vec4.hpp"

namespace GEngine
{
	class Vec4PropertyDrawerEditor final : public PropertyDrawerEditor<glm::vec4>
	{
	public:
		void DrawSpecific(Property<glm::vec4>* inspect) override;
	};
}

#endif //VEC4PROPERTYDRAWEREDITOR_H
