//
// Created by guillem on 12/4/25.
//

#ifndef BOOLPROPERTYDRAWEREDITOR_H
#define BOOLPROPERTYDRAWEREDITOR_H

#include "PropertyDrawerEditor.h"

namespace GEngine
{
	class BoolPropertyDrawerEditor final : public PropertyDrawerEditor<bool>
	{
	public:
		void DrawSpecific(Property<bool>* inspect) override;
	};
}

#endif //BOOLPROPERTYDRAWEREDITOR_H
