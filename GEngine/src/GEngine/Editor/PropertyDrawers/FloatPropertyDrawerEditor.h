//
// Created by guillem on 7/8/25.
//

#ifndef FLOATPROPERTYDRAWEREDITOR_H
#define FLOATPROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"
#include "GEngine/SerializedProperties/Property.h"

namespace GEngine
{
	class FloatPropertyDrawerEditor final : public PropertyDrawerEditor<float>
	{
	public:
		void DrawSpecific(Property<float>* inspect) override;
	};
}

#endif //FLOATPROPERTYDRAWEREDITOR_H
