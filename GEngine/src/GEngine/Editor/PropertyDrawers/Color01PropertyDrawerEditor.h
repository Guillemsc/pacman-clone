//
// Created by guillem on 7/12/25.
//

#ifndef COLORPROPERTYDRAWEREDITOR_H
#define COLORPROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"
#include "GEngine/Colors/Color01.h"

namespace GEngine
{
	class Color01PropertyDrawerEditor final : public PropertyDrawerEditor<Color01>
	{
	public:
		void DrawSpecific(Property<Color01>* inspect) override;
	};
}

#endif //COLORPROPERTYDRAWEREDITOR_H
