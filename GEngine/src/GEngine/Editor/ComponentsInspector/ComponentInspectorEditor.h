//
// Created by guillem on 6/9/25.
//

#ifndef COMPONENTINSPECTOR_H
#define COMPONENTINSPECTOR_H

#include <memory>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class Component;

	class IComponentInspectorEditor
	{
	public:
		virtual ~IComponentInspectorEditor() = default;

		virtual void Draw(const std::shared_ptr<Component>& inspect) = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template <class T>
	class ComponentInspectorEditor : public IComponentInspectorEditor
	{
	public:
		ComponentInspectorEditor(GEngineCoreModules* modules);

		void Draw(const std::shared_ptr<Component>& inspect) override;

	protected:
		virtual void DrawSpecific(const std::shared_ptr<T>& inspect) = 0;

	protected:
		GEngineCoreModules* const _modules;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	ComponentInspectorEditor<T>::ComponentInspectorEditor(GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	template<class T>
	void ComponentInspectorEditor<T>::Draw(const std::shared_ptr<Component> &inspect)
	{
		std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(inspect);
		if (!derived) return;

		DrawSpecific(derived);
	}
}

#endif //COMPONENTINSPECTOR_H
