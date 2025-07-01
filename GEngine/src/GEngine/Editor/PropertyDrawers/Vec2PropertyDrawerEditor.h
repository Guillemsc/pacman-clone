//
// Created by guillem on 7/1/25.
//

#ifndef VEC2PROPERTYDRAWEREDITOR_H
#define VEC2PROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class Vec2PropertyDrawerEditor final : public PropertyDrawerEditor<glm::vec2>
	{
	public:
		void DrawSpecific(Property<glm::vec2>* inspect) override;
	};
}

#endif //VEC2PROPERTYDRAWEREDITOR_H
