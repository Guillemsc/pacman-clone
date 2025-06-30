//
// Created by guillem on 6/29/25.
//

#ifndef PROPERTYDRAWEREDITOR_H
#define PROPERTYDRAWEREDITOR_H

#include <memory>

#include "GEngine/SerializedProperties/SerializedProperty.h"

namespace GEngine
{
	class IPropertyDrawerEditor
	{
	public:
		virtual ~IPropertyDrawerEditor() = default;

		virtual void Draw(ISerializedProperty* inspect) = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template <class T>
	class PropertyDrawerEditor : public IPropertyDrawerEditor
	{
	public:
		void Draw(ISerializedProperty* inspect) override;

	protected:
		virtual void DrawSpecific(SerializedProperty<T>* inspect) = 0;
	};

	template<class T>
	void PropertyDrawerEditor<T>::Draw(ISerializedProperty* inspect)
	{
		if (auto casted = dynamic_cast<SerializedProperty<T>*>(inspect))
		{
			DrawSpecific(casted);
		}
	}
}

#endif //PROPERTYDRAWEREDITOR_H
