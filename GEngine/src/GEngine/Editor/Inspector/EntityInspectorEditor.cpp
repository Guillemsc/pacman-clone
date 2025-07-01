//
// Created by guillem on 6/9/25.
//

#include "EntityInspectorEditor.h"

#include <format>
#include <typeindex>

#include "imgui.h"
#include "GEngine/Components/Component.h"
#include "GEngine/Editor/ComponentsInspector/TiledMap2dRendererComponentInspectorEditor.h"
#include "GEngine/Editor/ComponentsInspector/TransformComponentInspectorEditor.h"
#include "GEngine/Editor/Extensions/ImGuiExtensions.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EditorModule.h"

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
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<EditorModule> editor = app->Editor().lock();
		if (!editor) return;

		const std::vector<std::shared_ptr<Component>>& components = inspect->GetComponents();

		for (auto it = components.begin(); it != components.end(); ++it)
		{
			const std::shared_ptr<IComponentInspectorEditor> inspector = GetInspectorEditor(it->get());

			const char* name = (*it)->GetTypeName();

			if (ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (inspector)
				{
					inspector->Draw(*it);
					continue;
				}

				const PropertiesContainer& propertiesContainer = (*it)->GetProperties();
				const std::vector<std::shared_ptr<IProperty>>& properties = propertiesContainer.GetProperties();

				for (auto it = properties.begin(); it != properties.end(); ++it)
				{
					editor->DrawProperty(it->get());
				}
			}
		}
	}

	std::shared_ptr<IComponentInspectorEditor> EntityInspectorEditor::GetInspectorEditor(Component* component)
	{
		const std::type_index typeIndex = typeid(*component);

		const auto it = _inspectorEditors.find(typeIndex);

		if (it == _inspectorEditors.end())
		{
			return nullptr;
		}

		return it->second;
	}
} // GEngineCore