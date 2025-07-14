//
// Created by guillem on 7/12/25.
//

#include "Color01PropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void Color01PropertyDrawerEditor::DrawSpecific(Property<Color01> *inspect)
	{
		Color01 value = inspect->GetValue();
		if (ImGui::ColorEdit4(inspect->GetName().c_str(), &value.r, 0.1f))
		{
			inspect->SetValue(value);
		}
	}
}
