//
// Created by guillem on 6/29/25.
//

#ifndef PROPERTYDRAWEREDITOR_H
#define PROPERTYDRAWEREDITOR_H

#include <memory>

#include "GEngine/SerializedProperties/Property.h"

namespace GEngine
{
	class IPropertyDrawerEditor
	{
	public:
		virtual ~IPropertyDrawerEditor() = default;

		virtual void Draw(IProperty* inspect) = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template <class T>
	class PropertyDrawerEditor : public IPropertyDrawerEditor
	{
	public:
		void Draw(IProperty* inspect) override;

	protected:
		virtual void DrawSpecific(Property<T>* inspect) = 0;
	};

	template<class T>
	void PropertyDrawerEditor<T>::Draw(IProperty* inspect)
	{
		if (auto casted = dynamic_cast<Property<T>*>(inspect))
		{
			DrawSpecific(casted);
		}
	}
}

#endif //PROPERTYDRAWEREDITOR_H
