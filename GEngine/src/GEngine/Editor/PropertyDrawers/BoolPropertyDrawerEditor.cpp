//
// Created by guillem on 12/4/25.
//

#include "BoolPropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void BoolPropertyDrawerEditor::DrawSpecific(Property<bool> *inspect)
	{
		bool value = inspect->GetValue();
		if (ImGui::Checkbox(inspect->GetName().c_str(), &value))
		{
			inspect->SetValue(value);
		}
	}
}
