//
// Created by guillem on 6/9/25.
//

#include "EntityInspectorEditor.h"

#include <format>

#include "imgui.h"
#include "GEngine/Components/Component.h"
#include "GEngine/Editor/ComponentsInspector/TiledMap2dRendererComponentInspectorEditor.h"
#include "GEngine/Editor/ComponentsInspector/TransformComponentInspectorEditor.h"
#include "GEngine/Editor/Extensions/ImGuiExtensions.h"
#include "GEngine/Entities/Entity.h"

namespace GEngine
{
	EntityInspectorEditor::EntityInspectorEditor(const std::weak_ptr<GEngineCoreApplication>& app): GEngineObjectInspectorEditor(app)
	{
		RegisterInspector<TransformComponentInspectorEditor, TransformComponent>();
		RegisterInspector<TiledMap2dRendererComponentInspectorEditor, TiledMap2dRendererComponent>();
	}

	void EntityInspectorEditor::DrawSpecific(const std::shared_ptr<Entity> &inspect)
	{
		bool activeSelf = inspect->IsActiveSelf();
		if (ImGui::Checkbox("##Enabled", &activeSelf))
		{
			inspect->SetActive(activeSelf);
		}

		ImGui::SameLine();
		std::string name = inspect->GetName();
		if (ImGuiExtensions::InputText("Name", &name))
		{
			inspect->SetName(name);
		}

		ImGui::SameLine();
		ImGui::Text("[%d]", inspect->GetId());

		DrawComponents(inspect);
	}

	void EntityInspectorEditor::DrawComponents(const std::shared_ptr<Entity> &inspect)
	{
		const std::vector<std::shared_ptr<Component>>& components = inspect->GetComponents();

		for (auto it = components.begin(); it != components.end(); ++it)
		{
			const std::shared_ptr<IComponentInspectorEditor> inspector = GetInspectorEditor((*it)->GetType());

			const char* name = (*it)->GetTypeName();

			if (ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (!inspector)
				{
					ImGui::Text("Cannot be inspected");
					continue;
				}

				inspector->Draw(*it);
			}
		}
	}

	std::shared_ptr<IComponentInspectorEditor> EntityInspectorEditor::GetInspectorEditor(const ComponentType componentType)
	{
		const std::size_t objectIndex = static_cast<std::size_t>(componentType);

		if (_inspectorEditors.size() <= objectIndex)
		{
			return nullptr;
		}

		return _inspectorEditors[objectIndex];
	}
} // GEngineCore