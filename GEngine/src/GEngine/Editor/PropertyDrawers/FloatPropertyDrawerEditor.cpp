//
// Created by guillem on 7/8/25.
//

#include "FloatPropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void FloatPropertyDrawerEditor::DrawSpecific(Property<float> *inspect)
	{
		float value = inspect->GetValue();
		if (ImGui::DragFloat(inspect->GetName().c_str(), &value, 0.1f))
		{
			inspect->SetValue(value);
		}
	}
}
