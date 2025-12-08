//
// Created by guillem on 6/9/25.
//

#ifndef ENTITYINSPECTOREDITOR_H
#define ENTITYINSPECTOREDITOR_H

#include <unordered_map>
#include <vector>
#include <typeindex>

#include "GEngineObjectInspectorEditor.h"
#include "GEngine/Editor/ComponentsInspector/ComponentInspectorEditor.h"

namespace GEngine
{
	class IComponentInspectorEditor;
	class Entity;

	class EntityInspectorEditor final : public GEngineObjectInspectorEditor<Entity>
	{
	public:
		explicit EntityInspectorEditor(GEngineCoreModules* modules);

		template<class TEditor, class TObject>
		void RegisterInspector();

	protected:
		void DrawSpecific(const std::shared_ptr<Entity>& inspect) override;

	private:
		void DrawComponents(const std::shared_ptr<Entity> &inspect);
		std::shared_ptr<IComponentInspectorEditor> GetInspectorEditor(Component* component);

	private:
		std::unordered_map<std::type_index, std::shared_ptr<IComponentInspectorEditor>> _inspectorEditors;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TEditor, class TComponent>
	void EntityInspectorEditor::RegisterInspector()
	{
		static_assert(std::is_base_of_v<ComponentInspectorEditor<TComponent>, TEditor>, "TEditor is not derived from ComponentInspectorEditor");
		static_assert(std::is_base_of_v<Component, TComponent>, "TComponent is not derived from Component");

		const std::type_index typeIndex = typeid(TComponent);

		_inspectorEditors[typeIndex] = std::make_shared<TEditor>(_modules);
	}
}

#endif //ENTITYINSPECTOREDITOR_H
