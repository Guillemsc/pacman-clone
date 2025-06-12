//
// Created by guillem on 6/9/25.
//

#include "TransformComponentInspectorEditor.h"

#include <format>

#include "imgui.h"

namespace GEngineCore
{
	void TransformComponentInspectorEditor::DrawSpecific(const std::shared_ptr<TransformComponent> &inspect)
	{
		ImGui::Text("Transform");

		glm::vec3 position = inspect->GetLocalPosition();
		if (ImGui::DragFloat3("Position", &position.x, 0.1f))
		{
			inspect->SetLocalPosition(position);
		}

		glm::vec3 rotation = inspect->GetLocalRotationEulerDegrees();
		if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f))
		{
			inspect->SetLocalRotationEulerDegrees(rotation);
		}

		glm::vec3 scale = inspect->GetLocalScale();
		if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0))
		{
			inspect->SetLocalScale(scale);
		}

		ImGui::Separator();

		glm::vec3 worldPosition = inspect->GetPosition();
		ImGui::Text(std::format("World Position: X:{:.2f} Y:{:.2f} Z:{:.2f}", worldPosition.x, worldPosition.y, worldPosition.z).c_str());

		glm::vec3 worldRotation = inspect->GetRotationEulerDegrees();
		ImGui::Text(std::format("World Rotation: X:{:.2f} Y:{:.2f} Z:{:.2f}", worldRotation.x, worldRotation.y, worldRotation.z).c_str());

		glm::vec3 worldScale = inspect->GetScale();
		ImGui::Text(std::format("World Scale: X:{:.2f} Y:{:.2f} Z:{:.2f}", worldScale.x, worldScale.y, worldScale.z).c_str());
	}
} // GEngineCore