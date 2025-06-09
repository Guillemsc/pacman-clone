//
// Created by guillem on 6/9/25.
//

#include "TransformComponentInspectorEditor.h"

#include "imgui.h"

namespace GEngineCore
{
	void TransformComponentInspectorEditor::DrawSpecific(const std::shared_ptr<TransformComponent> &inspect)
	{
		ImGui::Text("Transform");

		Vector3 position = inspect->GetLocalPosition();
		if (ImGui::DragFloat3("Position", &position.x, 0.1f))
		{
			inspect->SetLocalPosition(position);
		}

		Vector3 rotation = inspect->GetLocalRotationEulerDegrees();
		if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f))
		{
			inspect->SetLocalRotationEulerDegrees(rotation);
		}
	}
} // GEngineCore