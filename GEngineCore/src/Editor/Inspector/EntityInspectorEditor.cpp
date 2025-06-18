//
// Created by guillem on 6/9/25.
//

#include "EntityInspectorEditor.h"

#include <format>

#include "imgui.h"
#include "Components/Component.h"
#include "Editor/ComponentsInspector/TransformComponentInspectorEditor.h"
#include "Editor/Extensions/ImGuiExtensions.h"
#include "Entities/Entity.h"

namespace GEngineCore
{
	EntityInspectorEditor::EntityInspectorEditor()
	{
		RegisterInspector<TransformComponentInspectorEditor, TransformComponent>();
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