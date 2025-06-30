//
// Created by guillem on 6/29/25.
//

#include "Vec3PropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void Vec3PropertyDrawerEditor::DrawSpecific(SerializedProperty<glm::vec3>* inspect)
	{
		glm::vec3 value = inspect->GetValue();
		if (ImGui::DragFloat3(inspect->GetName().c_str(), &value.x, 0.1f))
		{
			inspect->SetValue(value);
		}
	}
}
