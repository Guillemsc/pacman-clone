//
// Created by guillem on 6/9/25.
//

#include "EntityInspectorEditor.h"

#include <format>
#include <typeindex>

#include "imgui.h"
#include "GEngine/Components/Component.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Editor/ComponentsInspector/TiledMap2dRendererComponentInspectorEditor.h"
#include "GEngine/Editor/ComponentsInspector/TransformComponentInspectorEditor.h"
#include "GEngine/Editor/ComponentsInspector/UiTextRendererComponentInspectorEditor.h"
#include "GEngine/Editor/Extensions/ImGuiExtensions.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Modules/RenderingModule.h"

namespace GEngine
{
	EntityInspectorEditor::EntityInspectorEditor(GEngineCoreModules* modules)
		: GEngineObjectInspectorEditor(modules)
	{
		RegisterInspector<TransformComponentInspectorEditor, TransformComponent>();
		RegisterInspector<TiledMap2dRendererComponentInspectorEditor, TiledMap2dRendererComponent>();
		RegisterInspector<UiTextRendererComponentInspectorEditor, UiTextRendererComponent>();
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
		ImGui::Text("[Id: %d]", inspect->GetId());

		if (inspect->IsActiveInHierarchy())
		{
			ImGui::Text("Rendering index: %d", inspect->GetRenderingPositionInHierarchy());
		}

		DrawComponents(inspect);
	}

	void EntityInspectorEditor::DrawComponents(const std::shared_ptr<Entity> &inspect)
	{
		const std::vector<std::shared_ptr<Component>>& components = inspect->GetComponents();

		for (int i = 0; i < components.size(); ++i)
		{
			std::shared_ptr<Component> component = components[i];

			component->OnDrawSelectedGuizmo();

			const std::shared_ptr<IComponentInspectorEditor> inspector = GetInspectorEditor(component.get());

			const std::string_view& name = component->GetTypeName();

			ImGui::PushID(i);

			if (ImGui::CollapsingHeader(name.data(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (inspector)
				{
					inspector->Draw(component);
				}
				else
				{
					const PropertiesContainer& propertiesContainer = component->GetProperties();
					const std::vector<std::shared_ptr<IProperty>>& properties = propertiesContainer.GetProperties();

					for (auto it = properties.begin(); it != properties.end(); ++it)
					{
						_modules->editor->DrawProperty(it->get());
					}
				}
			}

			ImGui::PopID();
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