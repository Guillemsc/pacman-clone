//
// Created by guillem on 7/26/25.
//

#include "JsonResourceInspectorEditor.h"

#include "imgui.h"
#include "GEngine/Resources/JsonResource.h"

namespace GEngine
{

	JsonResourceInspectorEditor::JsonResourceInspectorEditor(const std::weak_ptr<GEngineCoreApplication> &app)
	: ResourceInspectorEditor(app)
	{
	}

	void JsonResourceInspectorEditor::DrawSpecific(const std::shared_ptr<JsonResource> &inspect)
	{
		const std::string json = inspect->GetJsonString();

		ImGui::Spacing();
		ImGui::CollapsingHeader("Data", ImGuiTreeNodeFlags_Leaf);
		ImGui::Text(json.c_str());
	}
}
