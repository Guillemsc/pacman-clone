//
// Created by guillem on 7/8/25.
//

#include "Vec4PropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void Vec4PropertyDrawerEditor::DrawSpecific(Property<glm::vec4> *inspect)
	{
		glm::vec4 value = inspect->GetValue();
		if (ImGui::DragFloat4(inspect->GetName().c_str(), &value.x, 0.1f))
		{
			inspect->SetValue(value);
		}
	}
} // GEngine