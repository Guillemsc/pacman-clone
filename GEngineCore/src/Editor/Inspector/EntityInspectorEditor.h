//
// Created by guillem on 6/9/25.
//

#ifndef ENTITYINSPECTOREDITOR_H
#define ENTITYINSPECTOREDITOR_H

#include <vector>

#include "GEngineObjectInspectorEditor.h"
#include "Components/ComponentType.h"
#include "Editor/ComponentsInspector/ComponentInspectorEditor.h"

namespace GEngineCore
{
	class IComponentInspectorEditor;
	class Entity;

	class EntityInspectorEditor : public GEngineObjectInspectorEditor<Entity>
	{
	public:
		EntityInspectorEditor();

	protected:
		void DrawSpecific(const std::shared_ptr<Entity>& inspect) override;

	private:
		void DrawComponents(const std::shared_ptr<Entity> &inspect);
		std::shared_ptr<IComponentInspectorEditor> GetInspectorEditor(ComponentType componentType);

		template<class TEditor, class TObject>
		void RegisterInspector();

	private:
		std::vector<std::shared_ptr<IComponentInspectorEditor>> _componentInspectorEditors;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TEditor, class TComponent>
	void EntityInspectorEditor::RegisterInspector()
	{
		static_assert(std::is_base_of_v<ComponentInspectorEditor<TComponent>, TEditor>, "TEditor is not derived from ComponentInspectorEditor");
		static_assert(std::is_base_of_v<Component, TComponent>, "TComponent is not derived from Component");

		const ComponentType componentType = TComponent::GetTypeStatic();
		const std::size_t componentIndex = static_cast<std::size_t>(componentType);

		while (componentIndex + 1 > _componentInspectorEditors.size())
		{
			_componentInspectorEditors.push_back(nullptr);
		}

		_componentInspectorEditors[componentIndex] = std::make_shared<TEditor>();
	}
}

#endif //ENTITYINSPECTOREDITOR_H
