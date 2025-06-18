//
// Created by guillem on 6/18/25.
//

#ifndef RESOURCESINSPECTOREDITOR_H
#define RESOURCESINSPECTOREDITOR_H

#include <memory>
#include <vector>

#include <Editor/Inspector/GEngineObjectInspectorEditor.h>
#include "Resources/ResourceType.h"
#include "Editor/ResourcesInspector/ResourceInspectorEditor.h"

namespace GEngineCore
{
	class IResourceInspectorEditor;
	class Resource;

	class ResourcesInspectorEditor final : public GEngineObjectInspectorEditor<Resource>
	{
	public:
		ResourcesInspectorEditor();

	protected:
		void DrawSpecific(const std::shared_ptr<Resource>& inspect) override;

	private:
		std::shared_ptr<IResourceInspectorEditor> GetInspectorEditor(ResourceType resourceType);

		template<class TEditor, class TResource>
		void RegisterInspector();

	private:
		std::vector<std::shared_ptr<IResourceInspectorEditor>> _inspectorEditors;
	};

	template<class TEditor, class TResource>
	void ResourcesInspectorEditor::RegisterInspector()
	{
		static_assert(std::is_base_of_v<ResourceInspectorEditor<TResource>, TEditor>, "TEditor is not derived from ResourceInspectorEditor");
		static_assert(std::is_base_of_v<Resource, TResource>, "TComponent is not derived from Resource");

		const ResourceType resourceType = TResource::GetTypeStatic();
		const std::size_t objectIndex = static_cast<std::size_t>(resourceType);

		while (objectIndex + 1 > _inspectorEditors.size())
		{
			_inspectorEditors.push_back(nullptr);
		}

		_inspectorEditors[objectIndex] = std::make_shared<TEditor>();
	}
}

#endif //RESOURCESINSPECTOREDITOR_H
