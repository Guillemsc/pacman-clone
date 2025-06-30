//
// Created by guillem on 6/29/25.
//

#ifndef VEC3PROPERTYDRAWEREDITOR_H
#define VEC3PROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"
#include "GEngine/SerializedProperties/SerializedProperty.h"
#include "glm/vec3.hpp"

namespace GEngine
{
	class Vec3PropertyDrawerEditor final : public PropertyDrawerEditor<glm::vec3>
	{
	public:
		void DrawSpecific(SerializedProperty<glm::vec3>* inspect) override;
	};
}

#endif //VEC3PROPERTYDRAWEREDITOR_H
