//
// Created by guillem on 7/1/25.
//

#ifndef INTPROPERTYDRAWEREDITOR_H
#define INTPROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"
#include "GEngine/SerializedProperties/Property.h"

namespace GEngine
{
	class IntPropertyDrawerEditor final : public PropertyDrawerEditor<int>
	{
	public:
		void DrawSpecific(Property<int>* inspect) override;
	};
}

#endif //INTPROPERTYDRAWEREDITOR_H
