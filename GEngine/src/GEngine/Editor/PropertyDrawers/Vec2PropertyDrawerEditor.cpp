//
// Created by guillem on 7/1/25.
//

#include "Vec2PropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void Vec2PropertyDrawerEditor::DrawSpecific(Property<glm::vec2> *inspect)
	{
		glm::vec2 value = inspect->GetValue();
		if (ImGui::DragFloat2(inspect->GetName().c_str(), &value.x, 0.1f))
		{
			inspect->SetValue(value);
		}
	}
} // GEngine